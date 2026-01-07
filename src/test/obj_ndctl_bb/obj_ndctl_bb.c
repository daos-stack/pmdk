// SPDX-License-Identifier: BSD-3-Clause
/* Copyright 2026, Hewlett Packard Enterprise Development LP */

/*
 * obj_ndctl_bb.c -- crashes whenever badblocks-related code is run
 */

#include <libpmemobj.h>

#include "set.h"

#include "unittest.h"

FUNC_MOCK(badblocks_recovery_file_exists, int, struct pool_set *set)
	FUNC_MOCK_RUN_DEFAULT {
		UT_ASSERT(0);
	}
FUNC_MOCK_END

FUNC_MOCK(badblocks_check_poolset, int, struct pool_set *set, int create)
	FUNC_MOCK_RUN_DEFAULT {
		UT_ASSERT(0);
	}
FUNC_MOCK_END

int
main(int argc, char *argv[])
{
	START(argc, argv, "obj_ndctl_bb");
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
