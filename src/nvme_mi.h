#ifndef NVME_MI_H
#define NVME_MI_H

#include "types.h"

typedef struct _product_info_mname_t {
	/**
	 * IEEE OUI Identifier (IEEE):
	 * Contains the Organization Unique Identifier (OUI) for the controller
	 * vendor.
	 */
	byte ieee[3];
	/**
	 * PCI Subsystem Vendor ID (SSVID):
	 * Contains the company vendor identifier that is assigned by the PCI SIG
	 * for the subsystem.
	 */
	word ssvid;
} __attribute__((packed)) product_info_mname_t;

extern void nvme_mi_test_checksum(void);

#endif