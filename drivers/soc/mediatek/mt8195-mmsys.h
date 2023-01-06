/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef __SOC_MEDIATEK_MT8195_MMSYS_H
#define __SOC_MEDIATEK_MT8195_MMSYS_H

#define MT8195_VDO0_OVL_MOUT_EN					0xf14
#define MT8195_MOUT_DISP_OVL0_TO_DISP_RDMA0			BIT(0)
#define MT8195_MOUT_DISP_OVL0_TO_DISP_WDMA0			BIT(1)
#define MT8195_MOUT_DISP_OVL0_TO_DISP_OVL1			BIT(2)
#define MT8195_MOUT_DISP_OVL1_TO_DISP_RDMA1			BIT(4)
#define MT8195_MOUT_DISP_OVL1_TO_DISP_WDMA1			BIT(5)
#define MT8195_MOUT_DISP_OVL1_TO_DISP_OVL0			BIT(6)

#define MT8195_VDO0_SEL_IN					0xf34
#define MT8195_SEL_IN_VPP_MERGE_FROM_MASK			GENMASK(1, 0)
#define MT8195_SEL_IN_VPP_MERGE_FROM_DSC_WRAP0_OUT		(0 << 0)
#define MT8195_SEL_IN_VPP_MERGE_FROM_DISP_DITHER1		(1 << 0)
#define MT8195_SEL_IN_VPP_MERGE_FROM_VDO1_VIRTUAL0		(2 << 0)
#define MT8195_SEL_IN_DSC_WRAP0_IN_FROM_MASK			GENMASK(4, 4)
#define MT8195_SEL_IN_DSC_WRAP0_IN_FROM_DISP_DITHER0		(0 << 4)
#define MT8195_SEL_IN_DSC_WRAP0_IN_FROM_VPP_MERGE		(1 << 4)
#define MT8195_SEL_IN_DSC_WRAP1_IN_FROM_MASK			GENMASK(5, 5)
#define MT8195_SEL_IN_DSC_WRAP1_IN_FROM_DISP_DITHER1		(0 << 5)
#define MT8195_SEL_IN_DSC_WRAP1_IN_FROM_VPP_MERGE		(1 << 5)
#define MT8195_SEL_IN_SINA_VIRTUAL0_FROM_MASK			GENMASK(8, 8)
#define MT8195_SEL_IN_SINA_VIRTUAL0_FROM_VPP_MERGE		(0 << 8)
#define MT8195_SEL_IN_SINA_VIRTUAL0_FROM_DSC_WRAP1_OUT		(1 << 8)
#define MT8195_SEL_IN_SINB_VIRTUAL0_FROM_MASK			GENMASK(9, 9)
#define MT8195_SEL_IN_SINB_VIRTUAL0_FROM_DSC_WRAP0_OUT		(0 << 9)
#define MT8195_SEL_IN_DP_INTF0_FROM_MASK			GENMASK(13, 12)
#define MT8195_SEL_IN_DP_INTF0_FROM_DSC_WRAP1_OUT		(0 << 0)
#define MT8195_SEL_IN_DP_INTF0_FROM_VPP_MERGE			(1 << 12)
#define MT8195_SEL_IN_DP_INTF0_FROM_VDO1_VIRTUAL0		(2 << 12)
#define MT8195_SEL_IN_DSI0_FROM_MASK				GENMASK(16, 16)
#define MT8195_SEL_IN_DSI0_FROM_DSC_WRAP0_OUT			(0 << 16)
#define MT8195_SEL_IN_DSI0_FROM_DISP_DITHER0			(1 << 16)
#define MT8195_SEL_IN_DSI1_FROM_MASK				GENMASK(17, 17)
#define MT8195_SEL_IN_DSI1_FROM_DSC_WRAP1_OUT			(0 << 17)
#define MT8195_SEL_IN_DSI1_FROM_VPP_MERGE			(1 << 17)
#define MT8195_SEL_IN_DISP_WDMA1_FROM_MASK			GENMASK(20, 20)
#define MT8195_SEL_IN_DISP_WDMA1_FROM_DISP_OVL1			(0 << 20)
#define MT8195_SEL_IN_DISP_WDMA1_FROM_VPP_MERGE			(1 << 20)
#define MT8195_SEL_IN_DSC_WRAP1_FROM_MASK			GENMASK(21, 21)
#define MT8195_SEL_IN_DSC_WRAP1_OUT_FROM_DSC_WRAP1_IN		(0 << 21)
#define MT8195_SEL_IN_DSC_WRAP1_OUT_FROM_DISP_DITHER1		(1 << 21)
#define MT8195_SEL_IN_DISP_WDMA0_FROM_MASK			GENMASK(22, 22)
#define MT8195_SEL_IN_DISP_WDMA0_FROM_DISP_OVL0			(0 << 22)

#define MT8195_VDO0_SEL_OUT					0xf38
#define MT8195_SOUT_DISP_DITHER0_TO_MASK			BIT(0)
#define MT8195_SOUT_DISP_DITHER0_TO_DSC_WRAP0_IN		(0 << 0)
#define MT8195_SOUT_DISP_DITHER0_TO_DSI0			(1 << 0)
#define MT8195_SOUT_DISP_DITHER1_TO_MASK			GENMASK(2, 1)
#define MT8195_SOUT_DISP_DITHER1_TO_DSC_WRAP1_IN		(0 << 1)
#define MT8195_SOUT_DISP_DITHER1_TO_VPP_MERGE			(1 << 1)
#define MT8195_SOUT_DISP_DITHER1_TO_DSC_WRAP1_OUT		(2 << 1)
#define MT8195_SOUT_VDO1_VIRTUAL0_TO_MASK			GENMASK(4, 4)
#define MT8195_SOUT_VDO1_VIRTUAL0_TO_VPP_MERGE			(0 << 4)
#define MT8195_SOUT_VDO1_VIRTUAL0_TO_DP_INTF0			(1 << 4)
#define MT8195_SOUT_VPP_MERGE_TO_MASK				GENMASK(10, 8)
#define MT8195_SOUT_VPP_MERGE_TO_DSI1				(0 << 8)
#define MT8195_SOUT_VPP_MERGE_TO_DP_INTF0			(1 << 8)
#define MT8195_SOUT_VPP_MERGE_TO_SINA_VIRTUAL0			(2 << 8)
#define MT8195_SOUT_VPP_MERGE_TO_DISP_WDMA1			(3 << 8)
#define MT8195_SOUT_VPP_MERGE_TO_DSC_WRAP0_IN			(4 << 8)
#define MT8195_SOUT_VPP_MERGE_TO_DSC_WRAP1_IN_MASK		GENMASK(11, 11)
#define MT8195_SOUT_VPP_MERGE_TO_DSC_WRAP1_IN			(0 << 11)
#define MT8195_SOUT_DSC_WRAP0_OUT_TO_MASK			GENMASK(13, 12)
#define MT8195_SOUT_DSC_WRAP0_OUT_TO_DSI0			(0 << 12)
#define MT8195_SOUT_DSC_WRAP0_OUT_TO_SINB_VIRTUAL0		(1 << 12)
#define MT8195_SOUT_DSC_WRAP0_OUT_TO_VPP_MERGE			(2 << 12)
#define MT8195_SOUT_DSC_WRAP1_OUT_TO_MASK			GENMASK(17, 16)
#define MT8195_SOUT_DSC_WRAP1_OUT_TO_DSI1			(0 << 16)
#define MT8195_SOUT_DSC_WRAP1_OUT_TO_DP_INTF0			(1 << 16)
#define MT8195_SOUT_DSC_WRAP1_OUT_TO_SINA_VIRTUAL0		(2 << 16)
#define MT8195_SOUT_DSC_WRAP1_OUT_TO_VPP_MERGE			(3 << 16)

static const struct mtk_mmsys_routes mmsys_mt8195_routing_table[] = {
	{
		DDP_COMPONENT_OVL0, DDP_COMPONENT_RDMA0,
		MT8195_VDO0_OVL_MOUT_EN, MT8195_MOUT_DISP_OVL0_TO_DISP_RDMA0,
		MT8195_MOUT_DISP_OVL0_TO_DISP_RDMA0
	}, {
		DDP_COMPONENT_OVL0, DDP_COMPONENT_WDMA0,
		MT8195_VDO0_OVL_MOUT_EN, MT8195_MOUT_DISP_OVL0_TO_DISP_WDMA0,
		MT8195_MOUT_DISP_OVL0_TO_DISP_WDMA0
	}, {
		DDP_COMPONENT_OVL0, DDP_COMPONENT_OVL1,
		MT8195_VDO0_OVL_MOUT_EN, MT8195_MOUT_DISP_OVL0_TO_DISP_OVL1,
		MT8195_MOUT_DISP_OVL0_TO_DISP_OVL1
	}, {
		DDP_COMPONENT_OVL1, DDP_COMPONENT_RDMA1,
		MT8195_VDO0_OVL_MOUT_EN, MT8195_MOUT_DISP_OVL1_TO_DISP_RDMA1,
		MT8195_MOUT_DISP_OVL1_TO_DISP_RDMA1
	}, {
		DDP_COMPONENT_OVL1, DDP_COMPONENT_WDMA1,
		MT8195_VDO0_OVL_MOUT_EN, MT8195_MOUT_DISP_OVL1_TO_DISP_WDMA1,
		MT8195_MOUT_DISP_OVL1_TO_DISP_WDMA1
	}, {
		DDP_COMPONENT_OVL1, DDP_COMPONENT_OVL0,
		MT8195_VDO0_OVL_MOUT_EN, MT8195_MOUT_DISP_OVL1_TO_DISP_OVL0,
		MT8195_MOUT_DISP_OVL1_TO_DISP_OVL0
	}, {
		DDP_COMPONENT_DSC0, DDP_COMPONENT_MERGE0,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_VPP_MERGE_FROM_MASK,
		MT8195_SEL_IN_VPP_MERGE_FROM_DSC_WRAP0_OUT
	}, {
		DDP_COMPONENT_DITHER1, DDP_COMPONENT_MERGE0,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_VPP_MERGE_FROM_MASK,
		MT8195_SEL_IN_VPP_MERGE_FROM_DISP_DITHER1
	}, {
		DDP_COMPONENT_MERGE5, DDP_COMPONENT_MERGE0,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_VPP_MERGE_FROM_MASK,
		MT8195_SEL_IN_VPP_MERGE_FROM_VDO1_VIRTUAL0
	}, {
		DDP_COMPONENT_DITHER0, DDP_COMPONENT_DSC0,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_DSC_WRAP0_IN_FROM_MASK,
		MT8195_SEL_IN_DSC_WRAP0_IN_FROM_DISP_DITHER0
	}, {
		DDP_COMPONENT_MERGE0, DDP_COMPONENT_DSC0,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_DSC_WRAP0_IN_FROM_MASK,
		MT8195_SEL_IN_DSC_WRAP0_IN_FROM_VPP_MERGE
	}, {
		DDP_COMPONENT_DITHER1, DDP_COMPONENT_DSC1,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_DSC_WRAP1_IN_FROM_MASK,
		MT8195_SEL_IN_DSC_WRAP1_IN_FROM_DISP_DITHER1
	}, {
		DDP_COMPONENT_MERGE0, DDP_COMPONENT_DSC1,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_DSC_WRAP1_IN_FROM_MASK,
		MT8195_SEL_IN_DSC_WRAP1_IN_FROM_VPP_MERGE
	}, {
		DDP_COMPONENT_MERGE0, DDP_COMPONENT_DP_INTF1,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_SINA_VIRTUAL0_FROM_MASK,
		MT8195_SEL_IN_SINA_VIRTUAL0_FROM_VPP_MERGE
	}, {
		DDP_COMPONENT_MERGE0, DDP_COMPONENT_DPI0,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_SINA_VIRTUAL0_FROM_MASK,
		MT8195_SEL_IN_SINA_VIRTUAL0_FROM_VPP_MERGE
	}, {
		DDP_COMPONENT_MERGE0, DDP_COMPONENT_DPI1,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_SINA_VIRTUAL0_FROM_MASK,
		MT8195_SEL_IN_SINA_VIRTUAL0_FROM_VPP_MERGE
	}, {
		DDP_COMPONENT_DSC1, DDP_COMPONENT_DP_INTF1,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_SINA_VIRTUAL0_FROM_MASK,
		MT8195_SEL_IN_SINA_VIRTUAL0_FROM_DSC_WRAP1_OUT
	}, {
		DDP_COMPONENT_DSC1, DDP_COMPONENT_DPI0,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_SINA_VIRTUAL0_FROM_MASK,
		MT8195_SEL_IN_SINA_VIRTUAL0_FROM_DSC_WRAP1_OUT
	}, {
		DDP_COMPONENT_DSC1, DDP_COMPONENT_DPI1,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_SINA_VIRTUAL0_FROM_MASK,
		MT8195_SEL_IN_SINA_VIRTUAL0_FROM_DSC_WRAP1_OUT
	}, {
		DDP_COMPONENT_DSC0, DDP_COMPONENT_DP_INTF1,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_SINB_VIRTUAL0_FROM_MASK,
		MT8195_SEL_IN_SINB_VIRTUAL0_FROM_DSC_WRAP0_OUT
	}, {
		DDP_COMPONENT_DSC0, DDP_COMPONENT_DPI0,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_SINB_VIRTUAL0_FROM_MASK,
		MT8195_SEL_IN_SINB_VIRTUAL0_FROM_DSC_WRAP0_OUT
	}, {
		DDP_COMPONENT_DSC0, DDP_COMPONENT_DPI1,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_SINB_VIRTUAL0_FROM_MASK,
		MT8195_SEL_IN_SINB_VIRTUAL0_FROM_DSC_WRAP0_OUT
	}, {
		DDP_COMPONENT_DSC1, DDP_COMPONENT_DP_INTF0,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_DP_INTF0_FROM_MASK,
		MT8195_SEL_IN_DP_INTF0_FROM_DSC_WRAP1_OUT
	}, {
		DDP_COMPONENT_MERGE0, DDP_COMPONENT_DP_INTF0,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_DP_INTF0_FROM_MASK,
		MT8195_SEL_IN_DP_INTF0_FROM_VPP_MERGE
	}, {
		DDP_COMPONENT_MERGE5, DDP_COMPONENT_DP_INTF0,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_DP_INTF0_FROM_MASK,
		MT8195_SEL_IN_DP_INTF0_FROM_VDO1_VIRTUAL0
	}, {
		DDP_COMPONENT_DSC0, DDP_COMPONENT_DSI0,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_DSI0_FROM_MASK,
		MT8195_SEL_IN_DSI0_FROM_DSC_WRAP0_OUT
	}, {
		DDP_COMPONENT_DITHER0, DDP_COMPONENT_DSI0,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_DSI0_FROM_MASK,
		MT8195_SEL_IN_DSI0_FROM_DISP_DITHER0
	}, {
		DDP_COMPONENT_DSC1, DDP_COMPONENT_DSI1,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_DSI1_FROM_MASK,
		MT8195_SEL_IN_DSI1_FROM_DSC_WRAP1_OUT
	}, {
		DDP_COMPONENT_MERGE0, DDP_COMPONENT_DSI1,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_DSI1_FROM_MASK,
		MT8195_SEL_IN_DSI1_FROM_VPP_MERGE
	}, {
		DDP_COMPONENT_OVL1, DDP_COMPONENT_WDMA1,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_DISP_WDMA1_FROM_MASK,
		MT8195_SEL_IN_DISP_WDMA1_FROM_DISP_OVL1
	}, {
		DDP_COMPONENT_MERGE0, DDP_COMPONENT_WDMA1,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_DISP_WDMA1_FROM_MASK,
		MT8195_SEL_IN_DISP_WDMA1_FROM_VPP_MERGE
	}, {
		DDP_COMPONENT_DSC1, DDP_COMPONENT_DSI1,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_DSC_WRAP1_FROM_MASK,
		MT8195_SEL_IN_DSC_WRAP1_OUT_FROM_DSC_WRAP1_IN
	}, {
		DDP_COMPONENT_DSC1, DDP_COMPONENT_DP_INTF0,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_DSC_WRAP1_FROM_MASK,
		MT8195_SEL_IN_DSC_WRAP1_OUT_FROM_DSC_WRAP1_IN
	}, {
		DDP_COMPONENT_DSC1, DDP_COMPONENT_DP_INTF1,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_DSC_WRAP1_FROM_MASK,
		MT8195_SEL_IN_DSC_WRAP1_OUT_FROM_DSC_WRAP1_IN
	}, {
		DDP_COMPONENT_DSC1, DDP_COMPONENT_DPI0,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_DSC_WRAP1_FROM_MASK,
		MT8195_SEL_IN_DSC_WRAP1_OUT_FROM_DSC_WRAP1_IN
	}, {
		DDP_COMPONENT_DSC1, DDP_COMPONENT_DPI1,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_DSC_WRAP1_FROM_MASK,
		MT8195_SEL_IN_DSC_WRAP1_OUT_FROM_DSC_WRAP1_IN
	}, {
		DDP_COMPONENT_DSC1, DDP_COMPONENT_MERGE0,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_DSC_WRAP1_FROM_MASK,
		MT8195_SEL_IN_DSC_WRAP1_OUT_FROM_DSC_WRAP1_IN
	}, {
		DDP_COMPONENT_DITHER1, DDP_COMPONENT_DSI1,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_DSC_WRAP1_FROM_MASK,
		MT8195_SEL_IN_DSC_WRAP1_OUT_FROM_DISP_DITHER1
	}, {
		DDP_COMPONENT_DITHER1, DDP_COMPONENT_DP_INTF0,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_DSC_WRAP1_FROM_MASK,
		MT8195_SEL_IN_DSC_WRAP1_OUT_FROM_DISP_DITHER1
	}, {
		DDP_COMPONENT_DITHER1, DDP_COMPONENT_DPI0,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_DSC_WRAP1_FROM_MASK,
		MT8195_SEL_IN_DSC_WRAP1_OUT_FROM_DISP_DITHER1
	}, {
		DDP_COMPONENT_DITHER1, DDP_COMPONENT_DPI1,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_DSC_WRAP1_FROM_MASK,
		MT8195_SEL_IN_DSC_WRAP1_OUT_FROM_DISP_DITHER1
	}, {
		DDP_COMPONENT_OVL0, DDP_COMPONENT_WDMA0,
		MT8195_VDO0_SEL_IN, MT8195_SEL_IN_DISP_WDMA0_FROM_MASK,
		MT8195_SEL_IN_DISP_WDMA0_FROM_DISP_OVL0
	}, {
		DDP_COMPONENT_DITHER0, DDP_COMPONENT_DSC0,
		MT8195_VDO0_SEL_OUT, MT8195_SOUT_DISP_DITHER0_TO_MASK,
		MT8195_SOUT_DISP_DITHER0_TO_DSC_WRAP0_IN
	}, {
		DDP_COMPONENT_DITHER0, DDP_COMPONENT_DSI0,
		MT8195_VDO0_SEL_OUT, MT8195_SOUT_DISP_DITHER0_TO_MASK,
		MT8195_SOUT_DISP_DITHER0_TO_DSI0
	}, {
		DDP_COMPONENT_DITHER1, DDP_COMPONENT_DSC1,
		MT8195_VDO0_SEL_OUT, MT8195_SOUT_DISP_DITHER1_TO_MASK,
		MT8195_SOUT_DISP_DITHER1_TO_DSC_WRAP1_IN
	}, {
		DDP_COMPONENT_DITHER1, DDP_COMPONENT_MERGE0,
		MT8195_VDO0_SEL_OUT, MT8195_SOUT_DISP_DITHER1_TO_MASK,
		MT8195_SOUT_DISP_DITHER1_TO_VPP_MERGE
	}, {
		DDP_COMPONENT_DITHER1, DDP_COMPONENT_DSI1,
		MT8195_VDO0_SEL_OUT, MT8195_SOUT_DISP_DITHER1_TO_MASK,
		MT8195_SOUT_DISP_DITHER1_TO_DSC_WRAP1_OUT
	}, {
		DDP_COMPONENT_DITHER1, DDP_COMPONENT_DP_INTF0,
		MT8195_VDO0_SEL_OUT, MT8195_SOUT_DISP_DITHER1_TO_MASK,
		MT8195_SOUT_DISP_DITHER1_TO_DSC_WRAP1_OUT
	}, {
		DDP_COMPONENT_DITHER1, DDP_COMPONENT_DP_INTF1,
		MT8195_VDO0_SEL_OUT, MT8195_SOUT_DISP_DITHER1_TO_MASK,
		MT8195_SOUT_DISP_DITHER1_TO_DSC_WRAP1_OUT
	}, {
		DDP_COMPONENT_DITHER1, DDP_COMPONENT_DPI0,
		MT8195_VDO0_SEL_OUT, MT8195_SOUT_DISP_DITHER1_TO_MASK,
		MT8195_SOUT_DISP_DITHER1_TO_DSC_WRAP1_OUT
	}, {
		DDP_COMPONENT_DITHER1, DDP_COMPONENT_DPI1,
		MT8195_VDO0_SEL_OUT, MT8195_SOUT_DISP_DITHER1_TO_MASK,
		MT8195_SOUT_DISP_DITHER1_TO_DSC_WRAP1_OUT
	}, {
		DDP_COMPONENT_MERGE5, DDP_COMPONENT_MERGE0,
		MT8195_VDO0_SEL_OUT, MT8195_SOUT_VDO1_VIRTUAL0_TO_MASK,
		MT8195_SOUT_VDO1_VIRTUAL0_TO_VPP_MERGE
	}, {
		DDP_COMPONENT_MERGE5, DDP_COMPONENT_DP_INTF0,
		MT8195_VDO0_SEL_OUT, MT8195_SOUT_VDO1_VIRTUAL0_TO_MASK,
		MT8195_SOUT_VDO1_VIRTUAL0_TO_DP_INTF0
	}, {
		DDP_COMPONENT_MERGE0, DDP_COMPONENT_DSI1,
		MT8195_VDO0_SEL_OUT, MT8195_SOUT_VPP_MERGE_TO_MASK,
		MT8195_SOUT_VPP_MERGE_TO_DSI1
	}, {
		DDP_COMPONENT_MERGE0, DDP_COMPONENT_DP_INTF0,
		MT8195_VDO0_SEL_OUT, MT8195_SOUT_VPP_MERGE_TO_MASK,
		MT8195_SOUT_VPP_MERGE_TO_DP_INTF0
	}, {
		DDP_COMPONENT_MERGE0, DDP_COMPONENT_DP_INTF1,
		MT8195_VDO0_SEL_OUT, MT8195_SOUT_VPP_MERGE_TO_MASK,
		MT8195_SOUT_VPP_MERGE_TO_SINA_VIRTUAL0
	}, {
		DDP_COMPONENT_MERGE0, DDP_COMPONENT_DPI0,
		MT8195_VDO0_SEL_OUT, MT8195_SOUT_VPP_MERGE_TO_MASK,
		MT8195_SOUT_VPP_MERGE_TO_SINA_VIRTUAL0
	}, {
		DDP_COMPONENT_MERGE0, DDP_COMPONENT_DPI1,
		MT8195_VDO0_SEL_OUT, MT8195_SOUT_VPP_MERGE_TO_MASK,
		MT8195_SOUT_VPP_MERGE_TO_SINA_VIRTUAL0
	}, {
		DDP_COMPONENT_MERGE0, DDP_COMPONENT_WDMA1,
		MT8195_VDO0_SEL_OUT, MT8195_SOUT_VPP_MERGE_TO_MASK,
		MT8195_SOUT_VPP_MERGE_TO_DISP_WDMA1
	}, {
		DDP_COMPONENT_MERGE0, DDP_COMPONENT_DSC0,
		MT8195_VDO0_SEL_OUT, MT8195_SOUT_VPP_MERGE_TO_MASK,
		MT8195_SOUT_VPP_MERGE_TO_DSC_WRAP0_IN
	}, {
		DDP_COMPONENT_MERGE0, DDP_COMPONENT_DSC1,
		MT8195_VDO0_SEL_OUT, MT8195_SOUT_VPP_MERGE_TO_DSC_WRAP1_IN_MASK,
		MT8195_SOUT_VPP_MERGE_TO_DSC_WRAP1_IN
	}, {
		DDP_COMPONENT_DSC0, DDP_COMPONENT_DSI0,
		MT8195_VDO0_SEL_OUT, MT8195_SOUT_DSC_WRAP0_OUT_TO_MASK,
		MT8195_SOUT_DSC_WRAP0_OUT_TO_DSI0
	}, {
		DDP_COMPONENT_DSC0, DDP_COMPONENT_DP_INTF1,
		MT8195_VDO0_SEL_OUT, MT8195_SOUT_DSC_WRAP0_OUT_TO_MASK,
		MT8195_SOUT_DSC_WRAP0_OUT_TO_SINB_VIRTUAL0
	}, {
		DDP_COMPONENT_DSC0, DDP_COMPONENT_DPI0,
		MT8195_VDO0_SEL_OUT, MT8195_SOUT_DSC_WRAP0_OUT_TO_MASK,
		MT8195_SOUT_DSC_WRAP0_OUT_TO_SINB_VIRTUAL0
	}, {
		DDP_COMPONENT_DSC0, DDP_COMPONENT_DPI1,
		MT8195_VDO0_SEL_OUT, MT8195_SOUT_DSC_WRAP0_OUT_TO_MASK,
		MT8195_SOUT_DSC_WRAP0_OUT_TO_SINB_VIRTUAL0
	}, {
		DDP_COMPONENT_DSC0, DDP_COMPONENT_MERGE0,
		MT8195_VDO0_SEL_OUT, MT8195_SOUT_DSC_WRAP0_OUT_TO_MASK,
		MT8195_SOUT_DSC_WRAP0_OUT_TO_VPP_MERGE
	}, {
		DDP_COMPONENT_DSC1, DDP_COMPONENT_DSI1,
		MT8195_VDO0_SEL_OUT, MT8195_SOUT_DSC_WRAP1_OUT_TO_MASK,
		MT8195_SOUT_DSC_WRAP1_OUT_TO_DSI1
	}, {
		DDP_COMPONENT_DSC1, DDP_COMPONENT_DP_INTF0,
		MT8195_VDO0_SEL_OUT, MT8195_SOUT_DSC_WRAP1_OUT_TO_MASK,
		MT8195_SOUT_DSC_WRAP1_OUT_TO_DP_INTF0
	}, {
		DDP_COMPONENT_DSC1, DDP_COMPONENT_DP_INTF1,
		MT8195_VDO0_SEL_OUT, MT8195_SOUT_DSC_WRAP1_OUT_TO_MASK,
		MT8195_SOUT_DSC_WRAP1_OUT_TO_SINA_VIRTUAL0
	}, {
		DDP_COMPONENT_DSC1, DDP_COMPONENT_DPI0,
		MT8195_VDO0_SEL_OUT, MT8195_SOUT_DSC_WRAP1_OUT_TO_MASK,
		MT8195_SOUT_DSC_WRAP1_OUT_TO_SINA_VIRTUAL0
	}, {
		DDP_COMPONENT_DSC1, DDP_COMPONENT_DPI1,
		MT8195_VDO0_SEL_OUT, MT8195_SOUT_DSC_WRAP1_OUT_TO_MASK,
		MT8195_SOUT_DSC_WRAP1_OUT_TO_SINA_VIRTUAL0
	}, {
		DDP_COMPONENT_DSC1, DDP_COMPONENT_MERGE0,
		MT8195_VDO0_SEL_OUT, MT8195_SOUT_DSC_WRAP1_OUT_TO_MASK,
		MT8195_SOUT_DSC_WRAP1_OUT_TO_VPP_MERGE
	}
};

#endif /* __SOC_MEDIATEK_MT8195_MMSYS_H */
