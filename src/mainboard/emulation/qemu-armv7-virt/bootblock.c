/* SPDX-License-Identifier: GPL-2.0-only */

#include <arch/cache.h>
#include <bootblock_common.h>
#include <symbols.h>

/* convenient shorthand (in MB) */
#define DRAM_START	((uintptr_t)_dram / MiB)
#define DRAM_SIZE	CONFIG_DRAM_SIZE_MB
#define DRAM_END	(DRAM_START + DRAM_SIZE)

void bootblock_mainboard_init(void)
{
	dcache_mmu_disable();

	mmu_init();

	mmu_config_range(0, DRAM_START, DCACHE_OFF);
	mmu_config_range(DRAM_START, DRAM_SIZE, DCACHE_WRITEBACK);
	mmu_config_range(DRAM_END, 4096 - DRAM_END, DCACHE_OFF);

	dcache_mmu_enable();
}
