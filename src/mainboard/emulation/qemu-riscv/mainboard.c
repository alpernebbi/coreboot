/* SPDX-License-Identifier: GPL-2.0-only */

#include <cbmem.h>
#include <console/console.h>
#include <device/device.h>
#include <symbols.h>
#include <ramdetect.h>
#include <mainboard/addressmap.h>

static void mainboard_enable(struct device *dev)
{
}

struct chip_operations mainboard_ops = {
	.enable_dev = mainboard_enable,
};

struct chip_operations mainboard_emulation_qemu_riscv_ops = { };

static void qemu_riscv_domain_read_resources(struct device *dev)
{
	struct resource *res;
	int index = 0;
	/* Initialize the system-wide I/O space constraints. */
	res = new_resource(dev, index++);
	res->limit = 0xffff;
	res->flags = IORESOURCE_IO | IORESOURCE_ASSIGNED;

	/* Initialize the system-wide memory resources constraints. */
	res = new_resource(dev, index++);
	res->base = QEMU_VIRT_PCIE_LOW_MMIO_BASE;
	res->limit = QEMU_VIRT_PCIE_LOW_MMIO_LIMIT;
	res->flags = IORESOURCE_MEM | IORESOURCE_ASSIGNED;

	res = new_resource(dev, index++);
	res->base = QEMU_VIRT_PCIE_HIGH_MMIO_BASE;
	res->limit = QEMU_VIRT_PCIE_HIGH_MMIO_LIMIT;
	res->flags = IORESOURCE_MEM | IORESOURCE_ASSIGNED;

	mmio_range(dev, index++, QEMU_VIRT_PCIE_ECAM_BASE, QEMU_VIRT_PCIE_ECAM_SIZE);

	ram_from_to(dev, index++, (uintptr_t)_dram, (uintptr_t)cbmem_top());
}

struct device_operations qemu_riscv_pci_domain_ops = {
	.read_resources    = qemu_riscv_domain_read_resources,
	.set_resources     = pci_domain_set_resources,
	.scan_bus          = pci_host_bridge_scan_bus,
};
