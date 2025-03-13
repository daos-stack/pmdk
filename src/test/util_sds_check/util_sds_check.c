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

int os_part_deep_common(struct pool_replica *rep, unsigned partidx, void *addr,
	size_t len, int flush);
/*
 * os_part_deep_common -- XXX temporally workaround until we will have pmem2
 *		integrated with common
 */
int
os_part_deep_common(struct pool_replica *rep, unsigned partidx, void *addr,
	size_t len, int flush)
{
	return 0;
}

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

static struct test_case test_cases[] = {
	TEST_CASE(test_case_1),
	TEST_CASE(test_case_2),
	TEST_CASE(test_case_3),
};

#define NTESTS ARRAY_SIZE(test_cases)

int
main(int argc, char *argv[])
{
	START(argc, argv, "util_sds_check");
	TEST_CASE_PROCESS(argc, argv, test_cases, NTESTS);
	DONE(NULL);
}
