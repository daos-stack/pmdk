/* SPDX-License-Identifier: BSD-3-Clause */
/* Copyright 2025, Hewlett Packard Enterprise Development LP */

/*
 * util_sds_check.h -- header for unit test
 */

#include <stdlib.h>
#include <stdbool.h>
#include "unittest.h"
#include "shutdown_state.h"
#include "set.h"

int os_part_deep_common(struct pool_replica *rep, unsigned partidx, void *addr,
	size_t len, int flush);
/* This function does not take part in this unit test. */
int
os_part_deep_common(struct pool_replica *rep, unsigned partidx, void *addr,
	size_t len, int flush)
{
	return 0;
}

#define DIRTY_SET 1
#define DIRTY_CLEAR 0

/* Invalid value for all test cases */
#define INVALID_VALUE 0

#define CHECKSUM 0
#define UUID 1
#define USC 1

#define SDS_CUSTOM(USC, UUID, DIRTY_BIT, CHECKSUM) \
{ \
	.usc = USC, \
	.uuid = UUID, \
	.dirty = DIRTY_BIT, \
	.reserved = {0}, \
	.checksum = CHECKSUM \
}

#define SDS_ZERO {0}

#define SET_SDS(DST, VALUE) \
do { \
	struct shutdown_state sds_src = VALUE; \
	memcpy(&DST, &sds_src, sizeof(struct shutdown_state)); \
} while (0)

/* pool_sds - SDS read from the pool header (persistent) */
static struct shutdown_state Pool_sds;
/*
 * curr_sds - SDS calculated ad hoc considering all the involved PMem DIMMs
 * their UUIDs and USCs (volatile)
 */
static struct shutdown_state Curr_sds;
static struct pool_replica Rep;
