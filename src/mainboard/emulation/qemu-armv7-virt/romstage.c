/* SPDX-License-Identifier: GPL-2.0-only */

#include <arch/exception.h>
#include <cbmem.h>
#include <program_loading.h>
#include <romstage_common.h>

#if CONFIG(SEPARATE_ROMSTAGE)
void main(void)
{
	console_init();
	exception_init();
	romstage_main();
}
#endif

void __noreturn romstage_main(void)
{
	cbmem_initialize_empty();
	run_ramstage();
}