/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <ramdetect.h>
#include <arch/cache.h>
#include <arch/exception.h>
#include <arch/mmio.h>

/*
 * The default probe_mb() triggers a data_abort exception since
 * virt-2.11 so we can't boot. See:
 * https://lore.kernel.org/qemu-devel/1504626814-23124-1-git-send-email-peter.maydell@linaro.org/
 */

static enum {
	ABORT_CHECKER_NOT_TRIGGERED,
	ABORT_CHECKER_TRIGGERED,
} abort_state = ABORT_CHECKER_NOT_TRIGGERED;

static uint32_t abort_checker(uint32_t *regs)
{
	abort_state = ABORT_CHECKER_TRIGGERED;
	return 0;
}

int probe_mb(const uintptr_t dram_start, const uintptr_t size)
{
	uintptr_t addr = dram_start + (size * MiB) - sizeof(uint32_t);
	void *ptr = (void *)addr;

	abort_state = ABORT_CHECKER_NOT_TRIGGERED;
	register_data_abort_handler(&abort_checker);
	dmb();
	read32(ptr);
	dmb();
	unregister_data_abort_handler();
	return abort_state == ABORT_CHECKER_NOT_TRIGGERED;
}
