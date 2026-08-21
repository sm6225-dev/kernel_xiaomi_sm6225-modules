// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2019-2020, The Linux Foundation. All rights reserved.
 */

#include "msm_vidc_debug.h"
#include "hfi_common.h"

#define VIDC_CPU_BASE_OFFS_AR50_LT		0x000A0000
#define VIDEO_GCC_BASE_OFFS_AR50_LT		0x00000000
#define VIDEO_CC_BASE_OFFS_AR50_LT		0x00100000

#define VIDC_CPU_CS_BASE_OFFS_AR50_LT		(VIDC_CPU_BASE_OFFS_AR50_LT)
#define VIDC_CPU_IC_BASE_OFFS_AR50_LT		(VIDC_CPU_BASE_OFFS_AR50_LT)

#define VIDC_CPU_CS_A2HSOFTINTCLR_AR50_LT	(VIDC_CPU_CS_BASE_OFFS_AR50_LT + 0x1C)
#define VIDC_CPU_CS_VMIMSG_AR50_LTi		(VIDC_CPU_CS_BASE_OFFS_AR50_LT + 0x34)
#define VIDC_CPU_CS_VMIMSGAG0_AR50_LT		(VIDC_CPU_CS_BASE_OFFS_AR50_LT + 0x38)
#define VIDC_CPU_CS_VMIMSGAG1_AR50_LT		(VIDC_CPU_CS_BASE_OFFS_AR50_LT + 0x3C)
#define VIDC_CPU_CS_VMIMSGAG2_AR50_LT		(VIDC_CPU_CS_BASE_OFFS_AR50_LT + 0x40)
#define VIDC_CPU_CS_VMIMSGAG3_AR50_LT		(VIDC_CPU_CS_BASE_OFFS_AR50_LT + 0x44)
#define VIDC_CPU_CS_SCIACMD_AR50_LT		(VIDC_CPU_CS_BASE_OFFS_AR50_LT + 0x48)

/* HFI_CTRL_STATUS */
#define VIDC_CPU_CS_SCIACMDARG0_AR50_LT		(VIDC_CPU_CS_BASE_OFFS_AR50_LT + 0x4C)
#define VIDC_CPU_CS_SCIACMDARG0_BMSK_AR50_LT	0xff
#define VIDC_CPU_CS_SCIACMDARG0_SHFT_AR50_LT	0x0
#define VIDC_CPU_CS_SCIACMDARG0_HFI_CTRL_ERROR_STATUS_BMSK_AR50_LT	0xfe
#define VIDC_CPU_CS_SCIACMDARG0_HFI_CTRL_ERROR_STATUS_SHFT_AR50_LT	0x1
#define VIDC_CPU_CS_SCIACMDARG0_HFI_CTRL_INIT_STATUS_BMSK_AR50_LT	0x1
#define VIDC_CPU_CS_SCIACMDARG0_HFI_CTRL_INIT_STATUS_SHFT_AR50_LT	0x0
#define VIDC_CPU_CS_SCIACMDARG0_HFI_CTRL_PC_READY_AR50_LT           	0x100
#define VIDC_CPU_CS_SCIACMDARG0_HFI_CTRL_INIT_IDLE_MSG_BMSK_AR50_LT     0x40000000

/* HFI_QTBL_INFO */
#define VIDC_CPU_CS_SCIACMDARG1_AR50_LT		(VIDC_CPU_CS_BASE_OFFS_AR50_LT + 0x50)

/* HFI_QTBL_ADDR */
#define VIDC_CPU_CS_SCIACMDARG2_AR50_LT		(VIDC_CPU_CS_BASE_OFFS_AR50_LT + 0x54)

/* HFI_VERSION_INFO */
#define VIDC_CPU_CS_SCIACMDARG3_AR50_LT		(VIDC_CPU_CS_BASE_OFFS_AR50_LT + 0x58)

/* VIDC_SFR_ADDR */
#define VIDC_CPU_CS_SCIBCMD_AR50_LT		(VIDC_CPU_CS_BASE_OFFS_AR50_LT + 0x5C)

/* VIDC_MMAP_ADDR */
#define VIDC_CPU_CS_SCIBCMDARG0_AR50_LT		(VIDC_CPU_CS_BASE_OFFS_AR50_LT + 0x60)

/* VIDC_UC_REGION_ADDR */
#define VIDC_CPU_CS_SCIBARG1_AR50_LT		(VIDC_CPU_CS_BASE_OFFS_AR50_LT + 0x64)

/* VIDC_UC_REGION_ADDR */
#define VIDC_CPU_CS_SCIBARG2_AR50_LT		(VIDC_CPU_CS_BASE_OFFS_AR50_LT + 0x68)

#define VIDC_CPU_IC_SOFTINT_EN_AR50_LT	(VIDC_CPU_IC_BASE_OFFS_AR50_LT + 0x148)
#define VIDC_CPU_IC_SOFTINT_AR50_LT		(VIDC_CPU_IC_BASE_OFFS_AR50_LT + 0x150)
#define VIDC_CPU_IC_SOFTINT_H2A_BMSK_AR50_LT	0x1
#define VIDC_CPU_IC_SOFTINT_H2A_SHFT_AR50_LT	0

/*
 * --------------------------------------------------------------------------
 * MODULE: vidc_wrapper
 * --------------------------------------------------------------------------
 */
#define VIDC_WRAPPER_BASE_OFFS_AR50_LT		0x000B0000

#define VIDC_WRAPPER_HW_VERSION_AR50_LT		(VIDC_WRAPPER_BASE_OFFS_AR50_LT + 0x00)
#define VIDC_WRAPPER_HW_VERSION_MAJOR_VERSION_MASK_AR50_LT  0x78000000
#define VIDC_WRAPPER_HW_VERSION_MAJOR_VERSION_SHIFT_AR50_LT 28
#define VIDC_WRAPPER_HW_VERSION_MINOR_VERSION_MASK_AR50_LT  0xFFF0000
#define VIDC_WRAPPER_HW_VERSION_MINOR_VERSION_SHIFT_AR50_LT 16
#define VIDC_WRAPPER_HW_VERSION_STEP_VERSION_MASK_AR50_LT   0xFFFF

#define VIDC_WRAPPER_CLOCK_CONFIG_AR50_LT	(VIDC_WRAPPER_BASE_OFFS_AR50_LT + 0x04)

#define VIDC_WRAPPER_INTR_STATUS_AR50_LT	(VIDC_WRAPPER_BASE_OFFS_AR50_LT + 0x0C)
#define VIDC_WRAPPER_INTR_STATUS_A2HWD_BMSK_AR50_LT	0x10
#define VIDC_WRAPPER_INTR_STATUS_A2HWD_SHFT_AR50_LT	0x4
#define VIDC_WRAPPER_INTR_STATUS_A2H_BMSK_AR50_LT	0x4
#define VIDC_WRAPPER_INTR_STATUS_A2H_SHFT_AR50_LT	0x2

#define VIDC_WRAPPER_INTR_MASK_AR50_LT		(VIDC_WRAPPER_BASE_OFFS_AR50_LT + 0x10)
#define VIDC_WRAPPER_INTR_MASK_A2HWD_BMSK_AR50_LT	0x10
#define VIDC_WRAPPER_INTR_MASK_A2HWD_SHFT_AR50_LT	0x4
#define VIDC_WRAPPER_INTR_MASK_A2HVCODEC_BMSK_AR50_LT	0x8
#define VIDC_WRAPPER_INTR_MASK_A2HCPU_BMSK_AR50_LT	0x4
#define VIDC_WRAPPER_INTR_MASK_A2HCPU_SHFT_AR50_LT	0x2

#define VIDC_WRAPPER_INTR_CLEAR_AR50_LT		(VIDC_WRAPPER_BASE_OFFS_AR50_LT + 0x14)
#define VIDC_WRAPPER_INTR_CLEAR_A2HWD_BMSK_AR50_LT	0x10
#define VIDC_WRAPPER_INTR_CLEAR_A2HWD_SHFT_AR50_LT	0x4
#define VIDC_WRAPPER_INTR_CLEAR_A2H_BMSK_AR50_LT	0x4
#define VIDC_WRAPPER_INTR_CLEAR_A2H_SHFT_AR50_LT	0x2

/*
 * --------------------------------------------------------------------------
 * MODULE: tz_wrapper
 * --------------------------------------------------------------------------
 */
#define VIDC_WRAPPER_TZ_BASE_OFFS	0x000C0000
#define VIDC_WRAPPER_TZ_CPU_CLOCK_CONFIG	(VIDC_WRAPPER_TZ_BASE_OFFS)
#define VIDC_WRAPPER_TZ_CPU_STATUS	(VIDC_WRAPPER_TZ_BASE_OFFS + 0x10)

#define VIDC_CTRL_INIT_AR50_LT			VIDC_CPU_CS_SCIACMD_AR50_LT

#define VIDC_CTRL_STATUS_AR50_LT		VIDC_CPU_CS_SCIACMDARG0_AR50_LT
#define VIDC_CTRL_ERROR_STATUS__M_AR50_LT \
		VIDC_CPU_CS_SCIACMDARG0_HFI_CTRL_ERROR_STATUS_BMSK_AR50_LT
#define VIDC_CTRL_INIT_IDLE_MSG_BMSK_AR50_LT \
		VIDC_CPU_CS_SCIACMDARG0_HFI_CTRL_INIT_IDLE_MSG_BMSK_AR50_LT
#define VIDC_CTRL_STATUS_PC_READY_AR50_LT \
		VIDC_CPU_CS_SCIACMDARG0_HFI_CTRL_PC_READY_AR50_LT

#define VIDC_QTBL_INFO_AR50_LT			VIDC_CPU_CS_SCIACMDARG1_AR50_LT
#define VIDC_QTBL_ADDR_AR50_LT			VIDC_CPU_CS_SCIACMDARG2_AR50_LT
#define VIDC_VERSION_INFO_AR50_LT		VIDC_CPU_CS_SCIACMDARG3_AR50_LT

#define VIDC_SFR_ADDR_AR50_LT			VIDC_CPU_CS_SCIBCMD_AR50_LT
#define VIDC_MMAP_ADDR_AR50_LT			VIDC_CPU_CS_SCIBCMDARG0_AR50_LT
#define VIDC_UC_REGION_ADDR_AR50_LT		VIDC_CPU_CS_SCIBARG1_AR50_LT
#define VIDC_UC_REGION_SIZE_AR50_LT		VIDC_CPU_CS_SCIBARG2_AR50_LT

void __interrupt_init_ar50_lt(struct venus_hfi_device *device, u32 sid)
{
	u32 mask_val = 0;

	/* Clear any pending interrupts before unmasking */
	__write_register(device, VIDC_WRAPPER_INTR_CLEAR_AR50_LT, 0xFFFFFFFF, sid);
	__write_register(device, VIDC_CPU_CS_A2HSOFTINTCLR_AR50_LT, 1, sid);

	mask_val = __read_register(device, VIDC_WRAPPER_INTR_MASK_AR50_LT, sid);
	mask_val &= ~(VIDC_WRAPPER_INTR_MASK_A2HWD_BMSK_AR50_LT |
			VIDC_WRAPPER_INTR_MASK_A2HCPU_BMSK_AR50_LT |
			VIDC_WRAPPER_INTR_MASK_A2HVCODEC_BMSK_AR50_LT);
	__write_register(device, VIDC_WRAPPER_INTR_MASK_AR50_LT, mask_val, sid);
}

void __setup_ucregion_memory_map_ar50_lt(struct venus_hfi_device *device, u32 sid)
{
	__write_register(device, VIDC_UC_REGION_ADDR_AR50_LT,
			(u32)device->iface_q_table.align_device_addr, sid);
	__write_register(device, VIDC_UC_REGION_SIZE_AR50_LT, SHARED_QSIZE, sid);
	__write_register(device, VIDC_QTBL_ADDR_AR50_LT,
			(u32)device->iface_q_table.align_device_addr, sid);
	__write_register(device, VIDC_QTBL_INFO_AR50_LT, 0x01, sid);
	__write_register(device, VIDC_VERSION_INFO_AR50_LT, 0x01, sid);
	if (device->sfr.align_device_addr)
		__write_register(device, VIDC_SFR_ADDR_AR50_LT,
				(u32)device->sfr.align_device_addr, sid);
	if (device->qdss.align_device_addr)
		__write_register(device, VIDC_MMAP_ADDR_AR50_LT,
				(u32)device->qdss.align_device_addr, sid);
	/* update queues vaddr for debug purpose */
	__write_register(device, VIDC_CPU_CS_BASE_OFFS_AR50_LT + 0x24,
		(u32)((uintptr_t)device->iface_q_table.align_virtual_addr & UINT_MAX), sid);
	__write_register(device, VIDC_CPU_CS_BASE_OFFS_AR50_LT + 0x28,
		(u32)((uintptr_t)device->iface_q_table.align_virtual_addr >> 32), sid);
	/* Enable softints and disable power gating */
	__write_register(device, VIDC_CPU_IC_BASE_OFFS_AR50_LT + 0x10, 0x1, sid);
	__write_register(device, VIDC_CPU_IC_SOFTINT_EN_AR50_LT, 0x1, sid);
	__write_register(device, VIDC_CPU_CS_BASE_OFFS_AR50_LT + 0x168, 0x0, sid);
}

void __power_off_ar50_lt(struct venus_hfi_device *device)
{
	if (!device->power_enabled)
		return;

	if (!(device->intr_status & VIDC_WRAPPER_INTR_STATUS_A2HWD_BMSK_AR50_LT))
		disable_irq_nosync(device->hal_data->irq);
	device->intr_status = 0;

	__disable_unprepare_clks(device);
	if (__disable_regulators(device))
		d_vpr_e("Failed to disable regulators\n");

	if (__unvote_buses(device, DEFAULT_SID))
		d_vpr_e("Failed to unvote for buses\n");
	device->power_enabled = false;
}

int __prepare_pc_ar50_lt(struct venus_hfi_device *device)
{
	int rc = 0;
	u32 wfi_status = 0, idle_status = 0, pc_ready = 0;
	u32 ctrl_status = 0;
	u32 count = 0, max_tries = 10;

	ctrl_status = __read_register(device, VIDC_CTRL_STATUS_AR50_LT, DEFAULT_SID);
	pc_ready = ctrl_status & VIDC_CTRL_STATUS_PC_READY_AR50_LT;
	idle_status = ctrl_status & BIT(30);

	if (pc_ready) {
		d_vpr_h("Already in pc_ready state\n");
		return 0;
	}

	wfi_status = BIT(0) & __read_register(device, VIDC_WRAPPER_TZ_CPU_STATUS,
							DEFAULT_SID);
	if (!wfi_status || !idle_status) {
		d_vpr_e("Skipping PC, wfi status not set\n");
		goto skip_power_off;
	}

	rc = __prepare_pc(device);
	if (rc) {
		d_vpr_e("Failed __prepare_pc %d\n", rc);
		goto skip_power_off;
	}

	while (count < max_tries) {
		wfi_status = BIT(0) & __read_register(device,
				VIDC_WRAPPER_TZ_CPU_STATUS, DEFAULT_SID);
		ctrl_status = __read_register(device,
				VIDC_CTRL_STATUS_AR50_LT, DEFAULT_SID);
		if (wfi_status && (ctrl_status & VIDC_CTRL_STATUS_PC_READY_AR50_LT))
			break;
		usleep_range(150, 250);
		count++;
	}

	if (count == max_tries) {
		d_vpr_e("Skip PC. Core is not in right state\n");
		goto skip_power_off;
	}

	return rc;

skip_power_off:
	d_vpr_e("Skip PC, wfi=%#x, idle=%#x, pcr=%#x, ctrl=%#x)\n",
		wfi_status, idle_status, pc_ready, ctrl_status);
	return -EAGAIN;
}

void __raise_interrupt_ar50_lt(struct venus_hfi_device *device, u32 sid)
{
	u32 val = (1 << VIDC_CPU_IC_SOFTINT_H2A_SHFT_AR50_LT);
	d_vpr_h("%s: writing %#x to SOFTINT (reg %#x) and %#x to CS (reg %#x)\n",
		__func__, val, VIDC_CPU_IC_SOFTINT_AR50_LT, (1 << 15), VIDC_CPU_CS_BASE_OFFS_AR50_LT + 0x18);
	__write_register(device, VIDC_CPU_IC_SOFTINT_AR50_LT, val, sid);
	__write_register(device, VIDC_CPU_CS_BASE_OFFS_AR50_LT + 0x18, 1 << 15, sid);
}

void __core_clear_interrupt_ar50_lt(struct venus_hfi_device *device)
{
	u32 intr_status = 0, mask = 0;

	if (!device) {
		d_vpr_e("%s: NULL device\n", __func__);
		return;
	}

	intr_status = __read_register(device, VIDC_WRAPPER_INTR_STATUS_AR50_LT, DEFAULT_SID);
	mask = (VIDC_WRAPPER_INTR_STATUS_A2H_BMSK_AR50_LT |
		VIDC_WRAPPER_INTR_STATUS_A2HWD_BMSK_AR50_LT |
		VIDC_CTRL_INIT_IDLE_MSG_BMSK_AR50_LT);

	d_vpr_h("%s: intr_status=%#x\n", __func__, intr_status);
	if (intr_status & mask) {
		device->intr_status |= intr_status;
		device->reg_count++;
		d_vpr_h(
			"INTERRUPT for device: %pK: times: %d interrupt_status: %d\n",
			device, device->reg_count, intr_status);
	} else {
		device->spur_count++;
	}

	__write_register(device, VIDC_CPU_CS_A2HSOFTINTCLR_AR50_LT, 1, DEFAULT_SID);
	__write_register(device, VIDC_WRAPPER_INTR_CLEAR_AR50_LT, intr_status, DEFAULT_SID);
}

int __boot_firmware_ar50_lt(struct venus_hfi_device *device, u32 sid)
{
	int rc = 0;
	u32 ctrl_init_val = 0, ctrl_status = 0, count = 0, max_tries = 1000;

	ctrl_init_val = BIT(0);

	/* Enable softints before booting */
	__write_register(device, VIDC_CPU_IC_BASE_OFFS_AR50_LT + 0x10, 0x1, sid);
	__write_register(device, VIDC_CPU_IC_SOFTINT_EN_AR50_LT, 0x1, sid);
	__write_register(device, VIDC_CPU_CS_BASE_OFFS_AR50_LT + 0x168, 0x0, sid);

	__write_register(device, VIDC_CTRL_INIT_AR50_LT, ctrl_init_val, sid);
	while (!ctrl_status && count < max_tries) {
		ctrl_status = __read_register(device, VIDC_CTRL_STATUS_AR50_LT, sid);
		if ((ctrl_status & VIDC_CTRL_ERROR_STATUS__M_AR50_LT) == 0x4) {
			s_vpr_e(sid, "invalid setting for UC_REGION\n");
			break;
		}
		usleep_range(50, 100);
		count++;
	}

	d_vpr_h("%s: ctrl_status=%#x after %d tries\n", __func__, ctrl_status, count);

	if (count >= max_tries) {
		s_vpr_e(sid, "Error booting up vidc firmware\n");
		rc = -ETIME;
	}

	/* Re-affirm interrupt and softint enables after boot */
	__write_register(device, VIDC_CPU_IC_BASE_OFFS_AR50_LT + 0x10, 0x1, sid);
	__write_register(device, VIDC_CPU_IC_SOFTINT_EN_AR50_LT, 0x1, sid);
	__write_register(device, VIDC_CPU_CS_BASE_OFFS_AR50_LT + 0x168, 0x0, sid);
	return rc;
}

void __noc_error_info_ar50_lt(struct venus_hfi_device *device)
{
	struct vidc_iface_q_info *cmd_q, *msg_q, *dbg_q;
	struct hfi_queue_header *cmd_hdr, *msg_hdr, *dbg_hdr;
	struct hfi_queue_table_header *q_tbl;
	u32 r48, r4c, r50, r54, r58, r5c, r60, r64, r68, r148, r150, r168;
	u32 intr_status, intr_mask;

	if (!device)
		return;

	r48 = __read_register(device, VIDC_CPU_CS_SCIACMD_AR50_LT, DEFAULT_SID);
	r4c = __read_register(device, VIDC_CTRL_STATUS_AR50_LT, DEFAULT_SID);
	r50 = __read_register(device, VIDC_QTBL_INFO_AR50_LT, DEFAULT_SID);
	r54 = __read_register(device, VIDC_QTBL_ADDR_AR50_LT, DEFAULT_SID);
	r58 = __read_register(device, VIDC_VERSION_INFO_AR50_LT, DEFAULT_SID);
	r5c = __read_register(device, VIDC_SFR_ADDR_AR50_LT, DEFAULT_SID);
	r60 = __read_register(device, VIDC_MMAP_ADDR_AR50_LT, DEFAULT_SID);
	r64 = __read_register(device, VIDC_UC_REGION_ADDR_AR50_LT, DEFAULT_SID);
	r68 = __read_register(device, VIDC_UC_REGION_SIZE_AR50_LT, DEFAULT_SID);
	r148 = __read_register(device, VIDC_CPU_IC_SOFTINT_EN_AR50_LT, DEFAULT_SID);
	r150 = __read_register(device, VIDC_CPU_IC_SOFTINT_AR50_LT, DEFAULT_SID);
	r168 = __read_register(device, VIDC_CPU_CS_BASE_OFFS_AR50_LT + 0x168, DEFAULT_SID);
	intr_status = __read_register(device, VIDC_WRAPPER_INTR_STATUS_AR50_LT, DEFAULT_SID);
	intr_mask = __read_register(device, VIDC_WRAPPER_INTR_MASK_AR50_LT, DEFAULT_SID);

	d_vpr_e("REGS: [48]=%#x [4c]=%#x [50]=%#x [54]=%#x [58]=%#x [5c]=%#x\n",
		r48, r4c, r50, r54, r58, r5c);
	d_vpr_e("REGS: [60]=%#x [64]=%#x [68]=%#x [148]=%#x [150]=%#x [168]=%#x intr_st=%#x intr_mask=%#x\n",
		r60, r64, r68, r148, r150, r168, intr_status, intr_mask);

	q_tbl = (struct hfi_queue_table_header *)device->iface_q_table.align_virtual_addr;
	if (q_tbl) {
		d_vpr_e("QTBL: dev_addr=%#x virt=%pK ver=%u size=%u hdr0_off=%u hdr_sz=%u num_q=%u active_q=%u\n",
			(u32)device->iface_q_table.align_device_addr, q_tbl,
			q_tbl->qtbl_version, q_tbl->qtbl_size, q_tbl->qtbl_qhdr0_offset,
			q_tbl->qtbl_qhdr_size, q_tbl->qtbl_num_q, q_tbl->qtbl_num_active_q);
	}

	cmd_q = &device->iface_queues[VIDC_IFACEQ_CMDQ_IDX];
	msg_q = &device->iface_queues[VIDC_IFACEQ_MSGQ_IDX];
	dbg_q = &device->iface_queues[VIDC_IFACEQ_DBGQ_IDX];

	cmd_hdr = cmd_q ? (struct hfi_queue_header *)cmd_q->q_hdr : NULL;
	msg_hdr = msg_q ? (struct hfi_queue_header *)msg_q->q_hdr : NULL;
	dbg_hdr = dbg_q ? (struct hfi_queue_header *)dbg_q->q_hdr : NULL;

	if (cmd_hdr)
		d_vpr_e("CMD_Q: start=%#x sz=%u status=%#x rd=%u wr=%u rx_req=%u tx_req=%u type=%#x\n",
			cmd_hdr->qhdr_start_addr, cmd_hdr->qhdr_q_size, cmd_hdr->qhdr_status,
			cmd_hdr->qhdr_read_idx, cmd_hdr->qhdr_write_idx,
			cmd_hdr->qhdr_rx_req, cmd_hdr->qhdr_tx_req, cmd_hdr->qhdr_type);
	if (msg_hdr)
		d_vpr_e("MSG_Q: start=%#x sz=%u status=%#x rd=%u wr=%u rx_req=%u tx_req=%u type=%#x\n",
			msg_hdr->qhdr_start_addr, msg_hdr->qhdr_q_size, msg_hdr->qhdr_status,
			msg_hdr->qhdr_read_idx, msg_hdr->qhdr_write_idx,
			msg_hdr->qhdr_rx_req, msg_hdr->qhdr_tx_req, msg_hdr->qhdr_type);
	if (dbg_hdr)
		d_vpr_e("DBG_Q: start=%#x sz=%u status=%#x rd=%u wr=%u rx_req=%u tx_req=%u type=%#x\n",
			dbg_hdr->qhdr_start_addr, dbg_hdr->qhdr_q_size, dbg_hdr->qhdr_status,
			dbg_hdr->qhdr_read_idx, dbg_hdr->qhdr_write_idx,
			dbg_hdr->qhdr_rx_req, dbg_hdr->qhdr_tx_req, dbg_hdr->qhdr_type);

	print_sfr_message(device);
	__flush_debug_queue(device, device->raw_packet);
}
