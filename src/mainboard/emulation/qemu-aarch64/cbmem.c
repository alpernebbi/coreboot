/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <cbmem.h>
#include <ramdetect.h>
#include <symbols.h>
#include <device_tree.h>

uintptr_t cbmem_top_chipset(void)
{
	if (CONFIG(FLATTENED_DEVICE_TREE)) {
		uint64_t top = fdt_get_memory_top((void *)_dram);
		if (top)
			return MIN(top, (uint64_t)4 * GiB) - 1;
	}

	return (uintptr_t)_dram + (probe_ramsize((uintptr_t)_dram, CONFIG_DRAM_SIZE_MB) * MiB);
}
