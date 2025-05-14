// SPDX-License-Identifier: BSD-3-Clause
/* Copyright 2025, Hewlett Packard Enterprise Development LP */

/*
 * util_sds_check.c -- unit test for the shutdown_state_check() function
 */

#include "util_sds_check.h"

/* pool_sds - SDS read from the pool header (persistent) */
static struct shutdown_state Pool_sds;
/*
 * curr_sds - SDS calculated ad hoc considering all the involved PMem DIMMs
 * their UUIDs and USCs (volatile)
 */
static struct shutdown_state Curr_sds;
static struct pool_replica Rep;

FUNC_MOCK(shutdown_state_reinit, void, struct shutdown_state *curr_sds,
	struct shutdown_state *pool_sds, struct pool_replica *rep)
FUNC_MOCK_RUN_DEFAULT {
	UT_ASSERTeq(curr_sds, &Curr_sds);
	UT_ASSERTeq(pool_sds, &Pool_sds);
	UT_ASSERTeq(rep, &Rep);
}
FUNC_MOCK_END

/*
 * The persistent SDS turned out to be zeroed out
 * whereas based on the pool structure it should be not.
 */
static int
test_dirty_clear()
{
	SET_SDS(Pool_sds, SDS_ZERO);
	SET_SDS(Curr_sds, SDS_CUSTOM(USC, UUID, DIRTY_CLEAR));

	int ret = shutdown_state_check(&Curr_sds, &Pool_sds, &Rep);
	UT_ASSERTeq(ret, 0);
	UT_ASSERTeq(RCOUNTER(shutdown_state_reinit), 1);

	return NO_ARGS_CONSUMED;
}

/* Pool_sds having an invalid checksum. */
static int
test_invalid_checksum()
{
	SET_SDS(Pool_sds, SDS_CUSTOM(USC, UUID, DIRTY_CLEAR));
	/* Pool_sds.checksum left zeroed out (invalid) */
	SET_SDS(Curr_sds, SDS_CUSTOM(USC, UUID, DIRTY_CLEAR));

	int ret = shutdown_state_check(&Curr_sds, &Pool_sds, &Rep);
	UT_ASSERTeq(ret, 0);
	UT_ASSERTeq(RCOUNTER(shutdown_state_reinit), 1);

	return NO_ARGS_CONSUMED;
}

/*
 * Test with curr_sds and pool_sds having the same values
 * except for the dirty field.
 */
static int
test_dirty_set()
{
	SET_SDS(Pool_sds, SDS_CUSTOM(USC, UUID, DIRTY_SET));
	shutdown_state_checksum(&Pool_sds, &Rep);
	SET_SDS(Curr_sds, SDS_CUSTOM(USC, UUID, DIRTY_CLEAR));

	int ret = shutdown_state_check(&Curr_sds, &Pool_sds, &Rep);
	UT_ASSERTeq(ret, 0);
	UT_ASSERTeq(RCOUNTER(shutdown_state_reinit), 1);

	return NO_ARGS_CONSUMED;
}

/* Pool_sds and Curr_sds having different uuid. */
static int
test_invalid_uuid()
{
	SET_SDS(Pool_sds, SDS_CUSTOM(USC, UUID ^ INVALID_VALUE, DIRTY_CLEAR));
	shutdown_state_checksum(&Pool_sds, &Rep);
	SET_SDS(Curr_sds, SDS_CUSTOM(USC, UUID, DIRTY_CLEAR));

	int ret = shutdown_state_check(&Curr_sds, &Pool_sds, &Rep);
	UT_ASSERTeq(ret, 0);
	UT_ASSERTeq(RCOUNTER(shutdown_state_reinit), 1);

	return NO_ARGS_CONSUMED;
}

/*
 * Pool_sds and Curr_sds having different uuid and
 * Pool_sds.dirty is set.
 */
static int
test_invalid_uuid_set_dirty()
{
	SET_SDS(Pool_sds, SDS_CUSTOM(USC, UUID ^ INVALID_VALUE, DIRTY_SET));
	shutdown_state_checksum(&Pool_sds, &Rep);
	SET_SDS(Curr_sds, SDS_CUSTOM(USC, UUID, DIRTY_CLEAR));

	int ret = shutdown_state_check(&Curr_sds, &Pool_sds, &Rep);
	UT_ASSERTeq(ret, 1);
	UT_ASSERTeq(RCOUNTER(shutdown_state_reinit), 0);

	return NO_ARGS_CONSUMED;
}

/* Pool_sds and Curr_sds having different USC and the same UUID. */
static int
test_invalid_usc()
{
	SET_SDS(Pool_sds, SDS_CUSTOM(USC ^ INVALID_VALUE, UUID, DIRTY_CLEAR));
	shutdown_state_checksum(&Pool_sds, &Rep);
	SET_SDS(Curr_sds, SDS_CUSTOM(USC, UUID, DIRTY_CLEAR));

	int ret = shutdown_state_check(&Curr_sds, &Pool_sds, &Rep);
	UT_ASSERTeq(ret, 0);
	UT_ASSERTeq(RCOUNTER(shutdown_state_reinit), 1);

	return NO_ARGS_CONSUMED;
}

/*
 * Pool_sds and Curr_sds having different USC, the same UUID and
 * Pool_sds.dirty is set.
 */
static int
test_invalid_usc_set_dirty()
{
	SET_SDS(Pool_sds, SDS_CUSTOM(USC ^ INVALID_VALUE, UUID, DIRTY_SET));
	shutdown_state_checksum(&Pool_sds, &Rep);
	SET_SDS(Curr_sds, SDS_CUSTOM(USC, UUID, DIRTY_CLEAR));

	int ret = shutdown_state_check(&Curr_sds, &Pool_sds, &Rep);
	UT_ASSERTeq(ret, 1);
	UT_ASSERTeq(RCOUNTER(shutdown_state_reinit), 0);

	return NO_ARGS_CONSUMED;
}

/* Pool_sds and Curr_sds having identical values (dirty==0). */
static int
test_happy_day()
{
	SET_SDS(Pool_sds, SDS_CUSTOM(USC, UUID, DIRTY_CLEAR));
	shutdown_state_checksum(&Pool_sds, &Rep);
	SET_SDS(Curr_sds, SDS_CUSTOM(USC, UUID, DIRTY_CLEAR));

	int ret = shutdown_state_check(&Curr_sds, &Pool_sds, &Rep);
	UT_ASSERTeq(ret, 0);
	UT_ASSERTeq(RCOUNTER(shutdown_state_reinit), 0);

	return NO_ARGS_CONSUMED;
}

static struct test_case test_cases[] = {
	TEST_CASE(test_dirty_clear),
	TEST_CASE(test_invalid_checksum),
	TEST_CASE(test_dirty_set),
	TEST_CASE(test_invalid_uuid),
	TEST_CASE(test_invalid_uuid_set_dirty),
	TEST_CASE(test_invalid_usc),
	TEST_CASE(test_invalid_usc_set_dirty),
	TEST_CASE(test_happy_day),
};

#define NTESTS ARRAY_SIZE(test_cases)

static void
log_function(enum core_log_level level, const char *file_name,
	unsigned line_no, const char *function_name, const char *message)
{
	UT_OUT("%s", message);
}

int
main(int argc, char *argv[])
{
	START(argc, argv, "util_sds_check");
	core_log_set_function(log_function);
	TEST_CASE_PROCESS(argc, argv, test_cases, NTESTS);
	DONE(NULL);
}
