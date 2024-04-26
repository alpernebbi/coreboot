/* SPDX-License-Identifier: GPL-2.0-only */

#include <arch/io.h>
/* #include <arch/barrier.h> */
#include <console/console.h>
#include <device/device.h>
#include <device/mmio.h>
#include <device/pci.h>
#include <device/pci_ids.h>
#include <device/pci_ops.h>
#include <drivers/emulation/qemu/fw_cfg.h>
#include <drivers/emulation/qemu/fw_cfg_if.h>
#include <drivers/emulation/qemu/ramfb.h>
#include <framebuffer_info.h>
#include <pc80/vga.h>
#include <pc80/vga_io.h>
#include <stdint.h>

static int width  = CONFIG_DRIVERS_EMULATION_QEMU_XRES;
static int height = CONFIG_DRIVERS_EMULATION_QEMU_YRES;
static uint32_t ramfb[CONFIG_DRIVERS_EMULATION_QEMU_XRES * CONFIG_DRIVERS_EMULATION_QEMU_YRES * 4];

void fw_cfg_ramfb_init(void)
{
	FWCfgFile ramfb_file;
	/* void *ramfb; */

	if (fw_cfg_check_file(&ramfb_file, "etc/ramfb") < 0) {
		printk(BIOS_DEBUG, "QEMU: ramfb: No etc/ramfb file in fw_cfg.\n");
		return;
	}

	/* ramfb = malloc(width * height * 4); */
	/* if (ramfb == NULL) { */
	/* 	printk(BIOS_ERR, "QEMU: ramfb: Couldn't allocate memory for ramfb.\n"); */
	/* 	return; */
	/* } */
	/* ramfb = (void *)0xa04700000000; */
	/* ramfb = (void *)0x4010000000; */

	FwCfgRamfb ramfb_cfg = {
		.addr = cpu_to_be64((uintptr_t)ramfb),
		.fourcc = cpu_to_be32(DRM_FORMAT_XRGB8888),
		.flags = 0x0,
		.width = cpu_to_be32(width),
		.height = cpu_to_be32(height),
		.stride = 0x0,
	};

	/* rmb(); */
	/* wmb(); */

	fw_cfg_dma(FW_CFG_DMA_CTL_WRITE | FW_CFG_DMA_CTL_SELECT | (ramfb_file.select << 16),
		   &ramfb_cfg, sizeof(ramfb_cfg));

	fb_add_framebuffer_info((uintptr_t)ramfb, width, height, 4 * width, 32);

	/* rmb(); */
	/* wmb(); */

	memset(ramfb, 0xaa, 0xaa);
}
