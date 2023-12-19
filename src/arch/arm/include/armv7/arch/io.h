/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef __ARCH_IO_H__
#define __ARCH_IO_H__

#include <stdint.h>
#include <arch/mmio.h>
#include <console/console.h>

/*
 * This file contains unimplemented stubs for the x86 IO instructions
 * so we can compile code that can choose between these and MMIO access
 * without having to use #if CONFIG(ARCH_X86) everywhere.
 */
static inline void outb(uint8_t value, uint16_t port)
{
	printk(BIOS_ERR, "arch/io.h: %s() not implemented\n", __func__);
}

static inline void outw(uint16_t value, uint16_t port)
{
	printk(BIOS_ERR, "arch/io.h: %s() not implemented\n", __func__);
}

static inline void outl(uint32_t value, uint16_t port)
{
	printk(BIOS_ERR, "arch/io.h: %s() not implemented\n", __func__);
}

static inline uint8_t inb(uint16_t port)
{
	printk(BIOS_ERR, "arch/io.h: %s() not implemented\n", __func__);
	return 0;
}

static inline uint16_t inw(uint16_t port)
{
	printk(BIOS_ERR, "arch/io.h: %s() not implemented\n", __func__);
	return 0;
}

static inline uint32_t inl(uint16_t port)
{
	printk(BIOS_ERR, "arch/io.h: %s() not implemented\n", __func__);
	return 0;
}

static inline void outsb(uint16_t port, const void *addr, unsigned long count)
{
	printk(BIOS_ERR, "arch/io.h: %s() not implemented\n", __func__);
}

static inline void outsw(uint16_t port, const void *addr, unsigned long count)
{
	printk(BIOS_ERR, "arch/io.h: %s() not implemented\n", __func__);
}

static inline void outsl(uint16_t port, const void *addr, unsigned long count)
{
	printk(BIOS_ERR, "arch/io.h: %s() not implemented\n", __func__);
}

static inline void insb(uint16_t port, void *addr, unsigned long count)
{
	printk(BIOS_ERR, "arch/io.h: %s() not implemented\n", __func__);
}

static inline void insw(uint16_t port, void *addr, unsigned long count)
{
	printk(BIOS_ERR, "arch/io.h: %s() not implemented\n", __func__);
}

static inline void insl(uint16_t port, void *addr, unsigned long count)
{
	printk(BIOS_ERR, "arch/io.h: %s() not implemented\n", __func__);
}

#endif
