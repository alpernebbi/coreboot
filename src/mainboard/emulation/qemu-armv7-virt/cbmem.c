/* SPDX-License-Identifier: GPL-2.0-only */

#include <cbmem.h>
#include <symbols.h>
#include <ramdetect.h>
#include <device_tree.h>

uintptr_t cbmem_top_chipset(void)
{
	uintptr_t top;

	top = fdt_get_memory_top((void *)_dram);
	if (top)
		return top;

	return (uintptr_t)_dram + (probe_ramsize((uintptr_t)_dram, CONFIG_DRAM_SIZE_MB) * MiB);
}
