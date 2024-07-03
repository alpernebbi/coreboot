/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <cbmem.h>
#include <symbols.h>
#include <device/device.h>
#include <bootmem.h>
#include <mainboard/addressmap.h>
#include <drivers/emulation/qemu/ramfb.h>

void bootmem_platform_add_ranges(void)
{

	/* Flash memory */
	bootmem_add_range(0x0, 0x08000000, BM_MEM_RESERVED);

	/* Miscellaneous device I/O */
	bootmem_add_range(0x08000000, 0x3f000000, BM_MEM_RESERVED);
	bootmem_add_range((uintptr_t)_bl31, REGION_SIZE(bl31), BM_MEM_BL31);

	/* PCI */
	bootmem_add_range(VIRT_PCIE_LOW_MMIO_BASE,
			  VIRT_PCIE_LOW_MMIO_LIMIT - VIRT_PCIE_LOW_MMIO_BASE,
			  BM_MEM_RESERVED);
	bootmem_add_range(VIRT_PCIE_LOW_MMIO_LIMIT, 0x10000, /* VIRT_PCIE_PIO */
			  BM_MEM_RESERVED);
	bootmem_add_range(VIRT_PCIE_HIGH_MMIO_BASE,
			  VIRT_PCIE_HIGH_MMIO_LIMIT - VIRT_PCIE_HIGH_MMIO_BASE,
			  BM_MEM_RESERVED);
}

static void mainboard_enable(struct device *dev)
{
	fw_cfg_ramfb_init();
}

struct chip_operations mainboard_ops = {
	.enable_dev = mainboard_enable,
};

struct chip_operations mainboard_emulation_qemu_aarch64_ops = { };

static void qemu_aarch64_domain_read_resources(struct device *dev)
{
	struct resource *res;
	int index = 0;
	/* Initialize the system-wide I/O space constraints. */
	res = new_resource(dev, index++);
	res->limit = 0xffff;
	res->flags = IORESOURCE_IO | IORESOURCE_ASSIGNED;

	/* Initialize the system-wide memory resources constraints. */
	res = new_resource(dev, index++);
	res->base = VIRT_PCIE_LOW_MMIO_BASE;
	res->limit = VIRT_PCIE_LOW_MMIO_LIMIT;
	res->flags = IORESOURCE_MEM | IORESOURCE_ASSIGNED;

	res = new_resource(dev, index++);
	res->base = VIRT_PCIE_HIGH_MMIO_BASE;
	res->limit = VIRT_PCIE_HIGH_MMIO_LIMIT;
	res->flags = IORESOURCE_MEM | IORESOURCE_ASSIGNED;

	mmio_range(dev, index++, VIRT_PCIE_ECAM_BASE, VIRT_PCIE_ECAM_SIZE);

	ram_from_to(dev, index++, (uintptr_t)_dram, cbmem_top());
}

struct device_operations qemu_aarch64_pci_domain_ops = {
	.read_resources    = qemu_aarch64_domain_read_resources,
	.set_resources     = pci_domain_set_resources,
	.scan_bus          = pci_host_bridge_scan_bus,
};
