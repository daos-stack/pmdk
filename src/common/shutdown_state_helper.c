// SPDX-License-Identifier: BSD-3-Clause
/* Copyright 2025, Hewlett Packard Enterprise Development LP */

/*
 * shutdown_state_helper.c -- implementation of shutdown_state_reinit
 */

#include <string.h>
#include <stdbool.h>
#include <endian.h>
#include "shutdown_state.h"
#include "out.h"
#include "util.h"
#include "os_deep.h"
#include "set.h"
#include "libpmem2.h"
#include "bad_blocks.h"
#include "../libpmem2/pmem2_utils.h"

/*
 * shutdown_state_reinit -- reinitializes shutdown_state struct
 */
void
shutdown_state_reinit(struct shutdown_state *curr_sds,
	struct shutdown_state *pool_sds, struct pool_replica *rep)
{
	LOG(3, "curr_sds %p, pool_sds %p", curr_sds, pool_sds);
	shutdown_state_init(pool_sds, rep);
	pool_sds->uuid = htole64(curr_sds->uuid);
	pool_sds->usc = htole64(curr_sds->usc);
	pool_sds->dirty = 0;

	FLUSH_SDS(pool_sds, rep);

	shutdown_state_checksum(pool_sds, rep);
}
