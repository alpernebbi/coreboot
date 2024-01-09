/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef _ARCH_EXCEPTION_H
#define _ARCH_EXCEPTION_H

#include <stdint.h>

void exception_init(void);
void set_vbar(uint32_t vbar);
void register_data_abort_handler(uint32_t (*handler)(uint32_t *));
void unregister_data_abort_handler(void);

#endif
