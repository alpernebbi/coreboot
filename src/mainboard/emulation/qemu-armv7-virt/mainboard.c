/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <cbmem.h>
#include <console/console.h>
#include <device/device.h>
#include <halt.h>
#include <device/mmio.h>
#include <ramdetect.h>
#include <symbols.h>
#include <framebuffer_info.h>
#include <mainboard/addressmap.h>

static void mainboard_enable(struct device *dev)
{
}

struct chip_operations mainboard_emulation_qemu_armv7_ops = {
	.enable_dev = mainboard_enable,
};

static void qemu_armv7_domain_read_resources(struct device *dev)
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

	mmio_range(dev, index++, VIRT_PCIE_ECAM_BASE, VIRT_PCIE_ECAM_SIZE);

	ram_from_to(dev, index++, (uintptr_t)_dram, (uintptr_t)cbmem_top());
}

struct device_operations qemu_armv7_pci_domain_ops = {
	.read_resources    = qemu_armv7_domain_read_resources,
	.set_resources     = pci_domain_set_resources,
	.scan_bus          = pci_host_bridge_scan_bus,
};
