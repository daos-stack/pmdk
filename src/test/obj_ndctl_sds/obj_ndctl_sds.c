// SPDX-License-Identifier: BSD-3-Clause
/* Copyright 2026, Hewlett Packard Enterprise Development LP */

/*
 * obj_ndctl_sds.c -- crashes whenever shutdown-state-related code is run
 */

#include <libpmemobj.h>

#include "set.h"

#include "unittest.h"

FUNC_MOCK(shutdown_state_init, int, struct shutdown_state *sds,
	struct pool_replica *rep)
	FUNC_MOCK_RUN_DEFAULT {
		UT_ASSERT(0);
	}
FUNC_MOCK_END

FUNC_MOCK(shutdown_state_set_dirty, void, struct shutdown_state *sds,
	struct pool_replica *rep)
	FUNC_MOCK_RUN_DEFAULT {
		UT_ASSERT(0);
	}
FUNC_MOCK_END

FUNC_MOCK(shutdown_state_check, int, struct shutdown_state *curr_sds,
	struct shutdown_state *pool_sds, struct pool_replica *rep)
	FUNC_MOCK_RUN_DEFAULT {
		UT_ASSERT(0);
	}
FUNC_MOCK_END

int
main(int argc, char *argv[])
{
	START(argc, argv, "obj_ndctl_sds");
	if (argc < 3) {
		UT_FATAL("usage: %s <path> <c|o>\nc - create\no - open",
			argv[0]);
	}

	const char *path = argv[1];
	const char *cmd = argv[2];
	PMEMobjpool *pop;

	if (strlen(cmd) != 1) {
		UT_FATAL("unknown command: %s", cmd);
	}

	switch (cmd[0]) {
		case 'c':
			pop = pmemobj_create(path, NULL, PMEMOBJ_MIN_POOL,
				0600);
		break;
		case 'o':
			pop = pmemobj_open(path, NULL);
		break;
		default:
			UT_FATAL("unknown command: %s", cmd);
	}

	UT_ASSERTne(pop, NULL);

	pmemobj_close(pop);

	DONE(NULL);
}
