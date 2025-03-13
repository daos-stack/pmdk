/* SPDX-License-Identifier: BSD-3-Clause */
/* Copyright 2025, Hewlett Packard Enterprise Development LP */

/*
 * util_sds_check.h -- header for unit test
 */

#include "unittest.h"
#include "shutdown_state.h"
#include "set.h"

#define DIRTY_SET 1
#define DIRTY_CLEAR 0

/* Invalid value for all test cases */
#define INVALID_VALUE 0x60bab3f082b07f57
#define UUID 0xbe4919b3edce624a
#define USC 0x14796ef67d593c7b

#define SDS_CUSTOM(my_usc, my_uuid, my_dirty) \
{ \
	.usc = my_usc, \
	.uuid = my_uuid, \
	.dirty = my_dirty, \
	.reserved = {0}, \
	.checksum = 0 \
}

#define SDS_ZERO {0}

#define SET_SDS(DST, VALUE) \
do { \
	struct shutdown_state sds_src = VALUE; \
	memcpy(&DST, &sds_src, sizeof(struct shutdown_state)); \
} while (0)
