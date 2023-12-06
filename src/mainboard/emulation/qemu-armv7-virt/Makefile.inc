## SPDX-License-Identifier: GPL-2.0-only

bootblock-y += bootblock.c

romstage-y += romstage.c

romstage-y += cbmem.c

bootblock-y += media.c
romstage-y += media.c
ramstage-y += media.c

bootblock-y += timer.c
romstage-y += timer.c
ramstage-y += timer.c

bootblock-y += mmio.c
romstage-y += mmio.c
ramstage-y += mmio.c

CPPFLAGS_common += -I$(src)/mainboard/$(MAINBOARDDIR)/include
