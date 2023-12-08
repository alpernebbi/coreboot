/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <cbmem.h>
#include <ramdetect.h>
#include <symbols.h>
#include <console/console.h>
#include <fw_cfg.h>

uintptr_t cbmem_top_chipset(void)
{
	printk(BIOS_DEBUG, "in cbmem_top_chipset()\n");

	unsigned char sig[FW_CFG_SIG_SIZE + 1];
	fw_cfg_get(FW_CFG_SIGNATURE, sig, 4);
	printk(BIOS_DEBUG, "fw_cfg signature: %s\n", sig);

	fw_cfg_get(FW_CFG_ID, sig, 4);
	printk(BIOS_DEBUG, "fw_cfg id: %x %x %x %x\n", sig[0], sig[1], sig[2], sig[3]);

	fw_cfg_get(FW_CFG_RAM_SIZE, sig, 4);
	printk(BIOS_DEBUG, "fw_cfg ram_size: %x %x %x %x\n", sig[0], sig[1], sig[2], sig[3]);

	uintptr_t top;
	printk(BIOS_DEBUG, "calling fw_cfg_tolud()\n");
	top = fw_cfg_tolud();
	printk(BIOS_DEBUG, "fw_cfg_tolud() = %#lx\n", top);

	printk(BIOS_DEBUG, "probing ram\n");
	top = (uintptr_t)_dram + (probe_ramsize((uintptr_t)_dram, CONFIG_DRAM_SIZE_MB) * MiB);
	printk(BIOS_DEBUG, "cbmem_top_chipset = %#lx\n", top);

	/* printk(BIOS_DEBUG, "smbios manufacturer: %s\n", smbios_mainboard_manufacturer()); */
	/* printk(BIOS_DEBUG, "smbios product_name: %s\n", smbios_mainboard_product_name()); */
	/* printk(BIOS_DEBUG, "smbios version: %s\n", smbios_mainboard_version()); */
	/* printk(BIOS_DEBUG, "smbios serial_number: %s\n", smbios_mainboard_serial_number()); */

	return top;
}
