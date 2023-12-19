/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef __ARCH_IO_H__
#define __ARCH_IO_H__

#include <stdint.h>
#include <arch/mmio.h>

/*
 * This file contains unimplemented stubs for the x86 IO instructions
 * so we can compile code that can choose between these and MMIO access
 * at build-time without having to use #if CONFIG(ARCH_X86) everywhere.
 *
 * TODO: The hardware often has a translator that enable us to work with
 *       an IO port space over MMIO, so these are possible to implement.
 */
void outb(uint8_t value, uint16_t port);
void outw(uint16_t value, uint16_t port);
void outl(uint32_t value, uint16_t port);

uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);
uint32_t inl(uint16_t port);

void outsb(uint16_t port, const void *addr, unsigned long count);
void outsw(uint16_t port, const void *addr, unsigned long count);
void outsl(uint16_t port, const void *addr, unsigned long count);

void insb(uint16_t port, void *addr, unsigned long count);
void insw(uint16_t port, void *addr, unsigned long count);
void insl(uint16_t port, void *addr, unsigned long count);

#endif
