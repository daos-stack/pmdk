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

#define DIRTY_SET 1
#define DIRTY_CLEAR 0

#define SDS_CUSTOM(DIRTY_BIT) \
{ \
	.usc = 1, \
	.uuid = 1, \
	.dirty = DIRTY_BIT, \
	.reserved = {0}, \
	.checksum = 43 \
}

#define SDS_ZERO {0}

#define SET_SDS(DST, VALUE) \
{ \
	ASSERTeq(memcmp(&DST, &VALUE, sizeof(struct shutdown_state)), 0); \
}

FUNC_MOCK(shutdown_state_reinit, void, struct shutdown_state *curr_sds,
	struct shutdown_state *pool_sds, struct pool_replica *rep)
FUNC_MOCK_RUN_DEFAULT {
	ASSERTeq(curr_sds, &Curr_sds);
	ASSERTeq(pool_sds, &Pool_sds);
	ASSERTeq(rep, &Rep);
}
FUNC_MOCK_END

/* pool_sds - SDS read from the pool header (persistent) */
static struct shutdown_state Pool_sds;
/*
 * curr_sds - SDS calculated ad hoc considering all the involved PMem DIMMs
 * their UUIDs and USCs (volatile)
 */
static struct shutdown_state Curr_sds;
static struct pool_replica Rep;

/* Test with curr_sds having non-zero values and pool_sds being zeroed out. */
static int
test_case_1()
{
	SET_SDS(&Curr_sds, SDS_CUSTOM(DIRTY_CLEAR));
	SET_SDS(&Pool_sds, SDS_ZERO);

	int ret = shutdown_state_check(&Curr_sds, &Pool_sds, &Rep);
	ASSERTeq(ret, 0);
	ASSERTeq(RCOUNTER(shutdown_state_reinit), 1);

	return ret;
}

/*
 * Test with curr_sds and pool_sds having the same values
 * except for the dirty field.
 */
static int
test_case_2()
{
	SET_SDS(&Curr_sds, SDS_CUSTOM(DIRTY_CLEAR));
	SET_SDS(&Curr_sds, SDS_CUSTOM(DIRTY_SET));

	int ret = shutdown_state_check(&Curr_sds, &Pool_sds, &Rep);
	ASSERTeq(ret, 0);
	ASSERTeq(RCOUNTER(shutdown_state_reinit), 1);

	return ret;
}

/* Tests with curr_sds and pool_sds having identical values. */
static int
test_case_3()
{
	SET_SDS(&Curr_sds, SDS_CUSTOM(DIRTY_CLEAR));
	SET_SDS(&Curr_sds, SDS_CUSTOM(DIRTY_CLEAR));

	int ret = shutdown_state_check(&Curr_sds, &Pool_sds, &Rep);
	ASSERTeq(ret, 0);
	ASSERTeq(RCOUNTER(shutdown_state_reinit), 1);

	return ret;
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
