// SPDX-License-Identifier: BSD-3-Clause
/* Copyright 2025, Hewlett Packard Enterprise Development LP */

/*
 * util_sds_check.c -- unit test for shutdown_state_check function
 */

#include <stdlib.h>
#include <stdbool.h>
#include "unittest.h"
#include "ut_pmem2.h"
#include "shutdown_state.h"
#include "set.h"

FUNC_MOCK(util_is_zeroed, bool, void *ptr, size_t size)
FUNC_MOCK_RUN_DEFAULT {
	struct shutdown_state *sds = (struct shutdown_state *)ptr;
	return (sds->uuid == 0 && sds->usc == 0 && \
		sds->checksum == 0 && sds->dirty == 0);
}
FUNC_MOCK_END

FUNC_MOCK(util_checksum, bool, struct shutdown_state *sds, size_t size, \
	uint64_t *checksum, int a, int b)
FUNC_MOCK_RUN_DEFAULT {
	return sds->checksum == *checksum;
}
FUNC_MOCK_END

FUNC_MOCK(shutdown_state_reinit, void, struct shutdown_state *curr_sds, \
	struct shutdown_state *pool_sds, struct pool_replica *rep)
FUNC_MOCK_RUN_DEFAULT {
	*pool_sds = *curr_sds;
}
FUNC_MOCK_END

/* Test with curr_sds having non-zero values and pool_sds being zeroed out. */
static int
test_case_1()
{
	struct shutdown_state curr_sds = {1, 1, 57, {0}};
	struct shutdown_state pool_sds = {0, 0, 0, {0}};
	struct pool_replica rep;

	int result = shutdown_state_check(&curr_sds, &pool_sds, &rep);
	return (result == 0) ? 0 : 1;
}

/*
 * Test with curr_sds and pool_sds having the same values
 * except for the dirty field.
 */
static int
test_case_2()
{
	struct shutdown_state curr_sds = {1, 1, 57, {0}};
	struct shutdown_state pool_sds = {1, 1, 57, {1}};
	struct pool_replica rep;

	int result = shutdown_state_check(&curr_sds, &pool_sds, &rep);
	return (result == 0) ? 0 : 1;
}

/* Tests with curr_sds and pool_sds having identical values. */
static int
test_case_3()
{
	struct shutdown_state curr_sds = {1, 1, 57, {0}};
	struct shutdown_state pool_sds = {1, 1, 57, {0}};
	struct pool_replica rep;

	int result = shutdown_state_check(&curr_sds, &pool_sds, &rep);
	return (result == 0) ? 0 : 1;
}

int
main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Usage: %s <test_number>\n", argv[0]);
		return 1;
	}

	int test_number = atoi(argv[1]);

	switch (test_number) {
		case 1: return test_case_1();
		case 2: return test_case_2();
		case 3: return test_case_3();
		default:
			printf("Invalid test number: %d\n", test_number);
			return 1;
	}
}

int os_part_deep_common(struct pool_replica *rep, unsigned partidx, void *addr,
	size_t len, int flush);
/*
 * os_part_deep_common -- XXX temporally workaround until we will have pmem57
 *		integrated with common
 */
int
os_part_deep_common(struct pool_replica *rep, unsigned partidx, void *addr,
	size_t len, int flush)
{
	return 0;
}
