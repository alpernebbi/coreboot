/* SPDX-License-Identifier: GPL-2.0-only */

#include <console/console.h>
#include <device/device.h>
#include <symbols.h>
#include <cbmem.h>
#include <mainboard/addressmap.h>

static void mainboard_enable(struct device *dev)
{
	if (!dev) {
		die("No dev0; die\n");
	}

	ram_from_to(dev, 0, (uintptr_t)_dram, cbmem_top());
}

struct chip_operations mainboard_ops = {
	.enable_dev = mainboard_enable,
};

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
	res->limit = res->base + QEMU_VIRT_PCIE_LOW_MMIO_SIZE - 1;
	res->flags = IORESOURCE_MEM | IORESOURCE_ASSIGNED;

	res = new_resource(dev, index++);
	if (CONFIG(ARCH_RISCV_RV32)) {
		res->base = QEMU_VIRT32_PCIE_HIGH_MMIO_BASE;
		res->limit = res->base + QEMU_VIRT32_PCIE_HIGH_MMIO_SIZE - 1;
	} else {
		res->base = ALIGN_UP((uintptr_t)_dram + (uintptr_t)cbmem_top(),
				     QEMU_VIRT64_PCIE_HIGH_MMIO_SIZE);
		res->limit = res->base + QEMU_VIRT64_PCIE_HIGH_MMIO_SIZE - 1;
	}
	res->flags = IORESOURCE_MEM | IORESOURCE_ASSIGNED;

	mmconf_resource(dev, index++);
}

struct device_operations qemu_riscv_pci_domain_ops = {
	.read_resources    = qemu_riscv_domain_read_resources,
	.set_resources     = pci_domain_set_resources,
	.scan_bus          = pci_host_bridge_scan_bus,
};
