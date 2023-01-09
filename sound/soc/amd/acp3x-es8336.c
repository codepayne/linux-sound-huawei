// SPDX-License-Identifier: GPL-2.0+
//
// Machine driver for AMD ACP Audio engine using DA7219 & MAX98357 codec.
//
//Copyright 2016 Advanced Micro Devices, Inc.

#include <sound/core.h>
#include <sound/soc.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/soc-dapm.h>
#include <sound/jack.h>
#include <linux/clk.h>
#include <linux/gpio.h>
#include <linux/gpio/consumer.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/io.h>
#include <linux/acpi.h>
#include <linux/dmi.h>

#include "raven/acp3x.h"

#define DRV_NAME        "amd-acp3x-essx8336"
#define SND_CARD_NAME   DRV_NAME
#define DUAL_CHANNEL	2

struct acp3x_es8336_private {
	/* struct acp3x_platform_info machine must always be
	 * the first entry in the structure,
	 * the acp3x-i2s driver casts the card private data to
	 * struct acp3x_platform_info
	 */
	struct acp3x_platform_info machine;
	struct device *codec_dev;
	struct gpio_desc *gpio_speakers;
	struct gpio_desc *gpio_headphone;
	bool speaker_en;
};

static const unsigned int channels[] = {
	DUAL_CHANNEL,
};

static const unsigned int rates[] = {
	48000,
};

static const struct snd_pcm_hw_constraint_list constraints_rates = {
	.count = ARRAY_SIZE(rates),
	.list  = rates,
	.mask = 0,
};

static const struct snd_pcm_hw_constraint_list constraints_channels = {
	.count = ARRAY_SIZE(channels),
	.list = channels,
	.mask = 0,
};
#define ES8336_MCLK_FREQ (48000 * 256)

static int acp3x_es8336_codec_startup(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime;
	struct snd_soc_pcm_runtime *rtd;
	struct acp3x_platform_info *machine;
	struct acp3x_es8336_private *priv;
	struct snd_soc_dai *codec_dai;
	int ret;

	runtime = substream->runtime;
	rtd = asoc_substream_to_rtd(substream);
	priv = snd_soc_card_get_drvdata(rtd->card);
	machine = &priv->machine;
	codec_dai = asoc_rtd_to_codec(rtd, 0);

	ret = snd_soc_dai_set_sysclk(codec_dai, 0, ES8336_MCLK_FREQ, SND_SOC_CLOCK_OUT);
	if (ret < 0) {
		dev_err(rtd->dev, "can't set codec sysclk: %d\n", ret);
		return ret;
	}

	ret =  snd_soc_dai_set_fmt(codec_dai, SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
	                           | SND_SOC_DAIFMT_CBP_CFP);
	if (ret < 0) {
		dev_err(rtd->dev, "failed to set DAI fmt: %d\n", ret);
		return ret;
	}
	/* Report to userspace ALSA that we don't support suspending and resuming pcm streams,
	 * this means that during suspends and resumes of the PC, pulseaudio will not try to resume
	 * the substream, but will drop the connection and establish a new one.
	 * This is needed because sometimes after resume pulseaudio is unable to resume the stream
	 * and no sound can be heard. As a workaround for this issue, pulseaudio needs to be restarted.
	 */
	runtime->hw.info &= ~(SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_RESUME);

	runtime->hw.channels_max = DUAL_CHANNEL;
	snd_pcm_hw_constraint_list(runtime, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
	                           &constraints_channels);
	snd_pcm_hw_constraint_list(runtime, 0, SNDRV_PCM_HW_PARAM_RATE,
	                           &constraints_rates);
	runtime->hw.formats = SNDRV_PCM_FMTBIT_S32_LE;
	machine->play_i2s_instance = I2S_SP_INSTANCE;

	return 0;
}

static int acp3x_es8336_speaker_power_event(struct snd_soc_dapm_widget *w,
                                            struct snd_kcontrol *kcontrol, int event);

static struct snd_soc_jack es8336_jack;

static struct snd_soc_jack_pin es8336_jack_pins[] = {
	{
		.pin	= "Headphone",
		.mask	= SND_JACK_HEADPHONE,
	},
	{
		.pin	= "Headset Mic",
		.mask	= SND_JACK_MICROPHONE,
	 },
};

static const struct snd_soc_dapm_widget acp3x_es8336_widgets[] = {
	SND_SOC_DAPM_SPK("Speaker", NULL),
	SND_SOC_DAPM_HP("Headphone", NULL),
	SND_SOC_DAPM_MIC("Headset Mic", NULL),
	SND_SOC_DAPM_MIC("Internal Mic", NULL),

	SND_SOC_DAPM_SUPPLY("Speaker Power", SND_SOC_NOPM, 0, 0,
	                    acp3x_es8336_speaker_power_event,
	                    SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
};

static const struct snd_soc_dapm_route acp3x_es8336_audio_map[] = {
	{"Headphone", NULL, "HPOL"},
	{"Headphone", NULL, "HPOR"},

	/*
	 * There is no separate speaker output instead the speakers are muxed to
	 * the HP outputs. The mux is controlled Speaker and/or headphone switch.
	 */
	{"Speaker", NULL, "HPOL"},
	{"Speaker", NULL, "HPOR"},
	{"MIC2", NULL, "Headset Mic"},
	{"Speaker", NULL, "Speaker Power"},
};


static const struct snd_kcontrol_new acp3x_es8336_controls[] = {
	SOC_DAPM_PIN_SWITCH("Speaker"),
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
};

static const struct acpi_gpio_params enable_gpio0 = { 0, 0, true };
static const struct acpi_gpio_params enable_gpio1 = { 1, 0, true };

/* This one works for me */
static const struct acpi_gpio_mapping acpi_speakers_enable_gpio0[] = {
	{ "speakers-enable-gpios", &enable_gpio0, 1, ACPI_GPIO_QUIRK_ONLY_GPIOIO },
	{ }
};

static const struct acpi_gpio_mapping acpi_speakers_enable_gpio1[] = {
	{ "speakers-enable-gpios", &enable_gpio1, 1, ACPI_GPIO_QUIRK_ONLY_GPIOIO },
};

/* Lets try this one */
static const struct acpi_gpio_mapping acpi_enable_both_gpios[] = {
	{ "speakers-enable-gpios", &enable_gpio0, 1, ACPI_GPIO_QUIRK_ONLY_GPIOIO },
	{ "headphone-enable-gpios", &enable_gpio1, 1, ACPI_GPIO_QUIRK_ONLY_GPIOIO },
	{ }
};

static const struct acpi_gpio_mapping acpi_enable_both_gpios_rev_order[] = {
	{ "speakers-enable-gpios", &enable_gpio1, 1, ACPI_GPIO_QUIRK_ONLY_GPIOIO },
	{ "headphone-enable-gpios", &enable_gpio0, 1, ACPI_GPIO_QUIRK_ONLY_GPIOIO },
	{ }
};
/*
  static int acp3x_es8336_speaker_power_event(struct snd_soc_dapm_widget *w,
  struct snd_kcontrol *kcontrol, int event)
  {
  struct acp3x_es8336_private *priv = snd_soc_card_get_drvdata(w->dapm->card);

  if (priv->speaker_en == !SND_SOC_DAPM_EVENT_ON(event))
  return 0;

  priv->speaker_en = !SND_SOC_DAPM_EVENT_ON(event);

  if (SND_SOC_DAPM_EVENT_ON(event))
  msleep(70);

  gpiod_set_value_cansleep(priv->gpio_speakers, priv->speaker_en);

  return 0;
  }
*/
static int acp3x_es8336_speaker_power_event(struct snd_soc_dapm_widget *w,
                                            struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_card *card = w->dapm->card;
	struct acp3x_es8336_private *priv = snd_soc_card_get_drvdata(card);

	dev_info(card->dev, "entered speaker power event = %d\n", event);
	if (priv->speaker_en == !SND_SOC_DAPM_EVENT_ON(event)) {
		dev_info(card->dev, "speaker power event 1\n");
		return 0;
	}

	priv->speaker_en = !SND_SOC_DAPM_EVENT_ON(event);

	if (SND_SOC_DAPM_EVENT_ON(event)) {
		dev_info(card->dev, "speaker power event 2\n");
		msleep(70);
	}

	gpiod_set_value_cansleep(priv->gpio_speakers, priv->speaker_en);

	if (SND_SOC_DAPM_EVENT_ON(event)) {
		dev_info(card->dev, "speaker power event 3\n");
		msleep(70);
	}

	gpiod_set_value_cansleep(priv->gpio_headphone, priv->speaker_en);
	dev_info(card->dev, "speaker power event 4\n");
	return 0;
}

/*
  static int acp3x_es8336_hw_params(struct snd_pcm_substream *substream,
  struct snd_pcm_hw_params *params)
  {
  struct snd_soc_pcm_runtime *rtd = asoc_substream_to_rtd(substream);
  struct snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
  struct snd_mask *fmt = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);

  printk(KERN_INFO"mysound1: entered card set hw params\n");

  //snd_mask_none(fmt);
  //snd_mask_set_format(fmt, SNDRV_PCM_FORMAT_S32_LE);

  return 0;
  }
*/

static int acp3x_es8336_init(struct snd_soc_pcm_runtime *runtime)
{
	struct snd_soc_component *codec = asoc_rtd_to_codec(runtime, 0)->component;
	struct snd_soc_card *card = runtime->card;
	struct acp3x_es8336_private *priv = snd_soc_card_get_drvdata(card);
	int ret;

	ret = snd_soc_card_jack_new_pins(card, "Headset",
	                                 SND_JACK_HEADSET | SND_JACK_BTN_0,
	                                 &es8336_jack, es8336_jack_pins,
	                                 ARRAY_SIZE(es8336_jack_pins));
	if (ret) {
		dev_err(card->dev, "jack creation failed %d\n", ret);
		return ret;
	}

	snd_jack_set_key(es8336_jack.jack, SND_JACK_BTN_0, KEY_PLAYPAUSE);

	snd_soc_component_set_jack(codec, &es8336_jack, NULL);

	ret = devm_acpi_dev_add_driver_gpios(codec->dev, acpi_enable_both_gpios);
	if (ret)
		dev_warn(codec->dev, "failed to add speaker gpio\n");

	priv->codec_dev = codec->dev;
	priv->gpio_speakers = gpiod_get_optional(codec->dev, "speakers-enable", GPIOD_OUT_LOW);
	if (IS_ERR(priv->gpio_speakers)) {
		dev_err(codec->dev, "could not get speakers-enable GPIO\n");
		return PTR_ERR(priv->gpio_speakers);
	}

	dev_info(codec->dev, "enabling headphone GPIO\n");
	priv->gpio_headphone = gpiod_get_optional(codec->dev, "headphone-enable", GPIOD_OUT_LOW);
	if (IS_ERR(priv->gpio_headphone)) {
		dev_err(codec->dev, "could not get headphone-enable GPIO\n");
		return PTR_ERR(priv->gpio_headphone);
	}

	return 0;
}

static struct snd_soc_ops acp3x_es8336_ops = {
	//	.hw_params = acp3x_es8336_hw_params,
	.startup = acp3x_es8336_codec_startup,
};


SND_SOC_DAILINK_DEF(acp3x_i2s,
                    DAILINK_COMP_ARRAY(COMP_CPU("acp3x_i2s_playcap.0")));
SND_SOC_DAILINK_DEF(codec,
                    DAILINK_COMP_ARRAY(COMP_CODEC("i2c-ESSX8336:00", "ES8316 HiFi")));
SND_SOC_DAILINK_DEF(platform,
                    DAILINK_COMP_ARRAY(COMP_PLATFORM("acp3x_rv_i2s_dma.0")));

static struct snd_soc_dai_link acp3x_dai_es8336[] = {
	{
		.name = "amd-acp3x-es8336-dai",
		.stream_name = "ES8336 HiFi Play",
		.stop_dma_first = 1,
		.dpcm_capture = 1,
		.dpcm_playback = 1,
		.init = acp3x_es8336_init,
		.ops = &acp3x_es8336_ops,
		SND_SOC_DAILINK_REG(acp3x_i2s, codec, platform),
	},
};

static struct snd_soc_card acp3x_es8336 = {
	.name = SND_CARD_NAME,
	.owner = THIS_MODULE,
	.dai_link = acp3x_dai_es8336,
	.num_links = ARRAY_SIZE(acp3x_dai_es8336),
	.dapm_widgets = acp3x_es8336_widgets,
	.num_dapm_widgets = ARRAY_SIZE(acp3x_es8336_widgets),
	.dapm_routes = acp3x_es8336_audio_map,
	.num_dapm_routes = ARRAY_SIZE(acp3x_es8336_audio_map),
	.controls = acp3x_es8336_controls,
	.num_controls = ARRAY_SIZE(acp3x_es8336_controls),
};

static const struct dmi_system_id acp3x_es8336_dmi_table[] = {
	{
		.matches = {
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "HUAWEI"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "KLVL-WXXW"),
			DMI_EXACT_MATCH(DMI_PRODUCT_VERSION, "M1010"),
		},
		.driver_data = &acp3x_es8336,
	},
	{
		.matches = {
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "HUAWEI"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "KLVL-WXX9"),
			DMI_EXACT_MATCH(DMI_PRODUCT_VERSION, "M1010"),
		},
		.driver_data = &acp3x_es8336,
	},
	{
		.matches = {
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "HUAWEI"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "BOM-WXX9"),
			DMI_EXACT_MATCH(DMI_PRODUCT_VERSION, "M1010"),
		},
		.driver_data = &acp3x_es8336,
	},
		{
		.matches = {
			DMI_EXACT_MATCH(DMI_BOARD_VENDOR, "HUAWEI"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "HVY-WXX9"),
			DMI_EXACT_MATCH(DMI_PRODUCT_VERSION, "M1040"),
		},
		.driver_data = &acp3x_es8336,
	},
	{}
};


static int acp3x_probe(struct platform_device *pdev)
{
	int ret = -ENODEV;
	struct device *dev = &pdev->dev;
	const struct dmi_system_id *dmi_id;

	dmi_id = dmi_first_match(acp3x_es8336_dmi_table);
	if (dmi_id && dmi_id->driver_data) {
		struct acp3x_es8336_private *priv;
		struct snd_soc_card *card;

		dev_info(dev, "matched DMI table with this system, trying to register sound card\n");

		priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
		if (!priv) {
			dev_err(dev, "can't alloc priv structure\n");
			return -ENOMEM;
		}

		card = (struct snd_soc_card *)dmi_id->driver_data;

		card->dev = &pdev->dev;
		platform_set_drvdata(pdev, card);
		snd_soc_card_set_drvdata(card, priv);
		ret = devm_snd_soc_register_card(&pdev->dev, card);
		if (ret) {
			dev_err(dev, "failed to register sound card, ret = %d\n", ret);
			return dev_err_probe(&pdev->dev, ret,
			                     "devm_snd_soc_register_card(%s) failed\n",
			                     card->name);
		} else {
			dev_info(dev, "successfully registered the sound card\n");
		}
	}
	else {
		dev_warn(dev, "this system has a ES8336 codec defined in ACPI, "
		         "but the driver doesn't have this system registered in DMI table\n");
	}
	return ret;
}


static int acp3x_remove(struct platform_device *pdev)
{
	struct snd_soc_card *card = platform_get_drvdata(pdev);
	struct acp3x_es8336_private *priv = snd_soc_card_get_drvdata(card);
	struct device *dev = &pdev->dev;

	gpiod_put(priv->gpio_speakers);

	dev_info(dev, "removing sound card\n");
	return 0;
}

/*
  static const struct platform_device_id board_ids[] = {
  {
  .name = "acp3x-essx8336",
  },
  { }
  };
*/
//MODULE_DEVICE_TABLE(platform, board_ids);



static const struct acpi_device_id acp3x_audio_acpi_match[] = {
	{"ESSX8336", 0},
	{},
};
MODULE_DEVICE_TABLE(acpi, acp3x_audio_acpi_match);


static struct platform_driver acp3x_audio = {
	.driver = {
		.name = DRV_NAME,
		.owner = THIS_MODULE,
		//.acpi_match_table = ACPI_PTR(acp3x_audio_acpi_match),
		.pm = &snd_soc_pm_ops,
	},
	.probe = acp3x_probe,
	.remove = acp3x_remove,
	//.id_table = board_ids,
};

static struct platform_device *acp3x_es8336_snd_device;

static int __init acp3x_es8336_module_init(void)
{
	int ret = -ENODEV;

	msleep(5000);
	ret = platform_driver_register(&acp3x_audio);
	if (ret < 0) {
		printk(KERN_ERR DRV_NAME": can't register platform driver\n");
		return ret;
	}

	acp3x_es8336_snd_device = platform_device_register_simple(DRV_NAME, 0, NULL, 0);
	if (IS_ERR(acp3x_es8336_snd_device)) {
		printk(KERN_ERR DRV_NAME": couldn't register platform device\n");
		platform_driver_unregister(&acp3x_audio);
		return PTR_ERR(acp3x_es8336_snd_device);
	}

	if (!platform_get_drvdata(acp3x_es8336_snd_device)) {
		printk(KERN_ERR DRV_NAME": probe of hw failed\n");
		platform_device_unregister(acp3x_es8336_snd_device);
		platform_driver_unregister(&acp3x_audio);
		return -ENODEV;
	}
	printk(KERN_INFO DRV_NAME": platform device registered successfully\n");

	return ret;
}
module_init(acp3x_es8336_module_init);

static void __exit acp3x_es8336_module_exit(void)
{
	printk(KERN_INFO DRV_NAME": module unloading\n");
	platform_device_unregister(acp3x_es8336_snd_device);
	platform_driver_unregister(&acp3x_audio);
}
module_exit(acp3x_es8336_module_exit);

MODULE_AUTHOR("posteuca@mutex.one");
MODULE_DESCRIPTION("ACP3x rev 1 ES8336 audio support");
MODULE_LICENSE("GPL v2");
//MODULE_ALIAS("dmi:bvnHUAWEI:*:*:*:*:*:pnKLVL-WXXW:pvrM1010:rvnHUAWEI:rnKLVL-WXXW-PCB:rvrM1010:*:*:*:skuC100:*")
//MODULE_ALIAS("platform:acp3x-essx8336");
