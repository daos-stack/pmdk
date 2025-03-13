// SPDX-License-Identifier: BSD-3-Clause
/* Copyright 2025, Hewlett Packard Enterprise Development LP */

/*
 * util_sds_check.c -- unit test for shutdown_state_check function
 */

#include "util_sds_check.h"

FUNC_MOCK(shutdown_state_reinit, void, struct shutdown_state *curr_sds,
	struct shutdown_state *pool_sds, struct pool_replica *rep)
FUNC_MOCK_RUN_DEFAULT {
	ASSERTeq(curr_sds, &Curr_sds);
	ASSERTeq(pool_sds, &Pool_sds);
	ASSERTeq(rep, &Rep);
}
FUNC_MOCK_END

/* Test with curr_sds having non-zero values and pool_sds being zeroed out. */
static int
test_dirty_clear()
{
	SET_SDS(Pool_sds, SDS_ZERO);
	SET_SDS(Curr_sds, SDS_CUSTOM(USC, UUID, DIRTY_CLEAR, CHECKSUM));

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
test_dirty_set()
{
	SET_SDS(Pool_sds, SDS_CUSTOM(USC, UUID, DIRTY_SET, CHECKSUM));
	SET_SDS(Curr_sds, SDS_CUSTOM(USC, UUID, DIRTY_CLEAR, CHECKSUM));

	int ret = shutdown_state_check(&Curr_sds, &Pool_sds, &Rep);
	ASSERTeq(ret, 0);
	ASSERTeq(RCOUNTER(shutdown_state_reinit), 1);

	return ret;
}

/* Pool_sds and Curr_sds having different checksum. */
static int
test_invalid_checksum()
{
	SET_SDS(Pool_sds, SDS_CUSTOM(USC, UUID, DIRTY_CLEAR, INVALID_VALUE));
	SET_SDS(Curr_sds, SDS_CUSTOM(USC, UUID, DIRTY_CLEAR, CHECKSUM));

	int ret = shutdown_state_check(&Curr_sds, &Pool_sds, &Rep);
	ASSERTeq(ret, 0);
	ASSERTeq(RCOUNTER(shutdown_state_reinit), 1);

	return ret;
}

/* Pool_sds and Curr_sds having different uuid. */
static int
test_invalid_uuid()
{
	SET_SDS(Pool_sds, SDS_CUSTOM(USC, INVALID_VALUE, DIRTY_CLEAR,
		CHECKSUM));
	SET_SDS(Curr_sds, SDS_CUSTOM(USC, UUID, DIRTY_CLEAR, CHECKSUM));

	int ret = shutdown_state_check(&Curr_sds, &Pool_sds, &Rep);
	ASSERTeq(ret, 0);
	ASSERTeq(RCOUNTER(shutdown_state_reinit), 1);

	return ret;
}

/* Pool_sds and Curr_sds having different uuid. */
static int
test_invalid_uuid_set_dirty()
{
	SET_SDS(Pool_sds, SDS_CUSTOM(USC, INVALID_VALUE, DIRTY_SET, CHECKSUM));
	SET_SDS(Curr_sds, SDS_CUSTOM(USC, UUID, DIRTY_CLEAR, CHECKSUM));

	int ret = shutdown_state_check(&Curr_sds, &Pool_sds, &Rep);
	ASSERTeq(ret, 0);
	ASSERTeq(RCOUNTER(shutdown_state_reinit), 1);

	return ret;
}

/* Pool_sds and Curr_sds having different USC and same UUID. */
static int
test_invalid_usc()
{
	SET_SDS(Pool_sds, SDS_CUSTOM(INVALID_VALUE, UUID, DIRTY_CLEAR,
		CHECKSUM));
	SET_SDS(Curr_sds, SDS_CUSTOM(USC, UUID, DIRTY_CLEAR, CHECKSUM));

	int ret = shutdown_state_check(&Curr_sds, &Pool_sds, &Rep);
	ASSERTeq(ret, 0);
	ASSERTeq(RCOUNTER(shutdown_state_reinit), 1);

	return ret;
}

/* Pool_sds and Curr_sds having different USC and same UUID. */
static int
test_invalid_usc_set_dirty()
{
	SET_SDS(Pool_sds, SDS_CUSTOM(INVALID_VALUE, UUID, DIRTY_SET, CHECKSUM));
	SET_SDS(Curr_sds, SDS_CUSTOM(USC, UUID, DIRTY_CLEAR, CHECKSUM));

	int ret = shutdown_state_check(&Curr_sds, &Pool_sds, &Rep);
	ASSERTeq(ret, 0);
	ASSERTeq(RCOUNTER(shutdown_state_reinit), 1);

	return ret;
}

/* Pool_sds and Curr_sds having identical values (dirty==0). */
static int
test_happy_day()
{
	SET_SDS(Pool_sds, SDS_CUSTOM(USC, UUID, DIRTY_CLEAR, CHECKSUM));
	shutdown_state_init(&Pool_sds, &Rep);

	int ret = shutdown_state_check(&Curr_sds, &Pool_sds, &Rep);
	ASSERTeq(ret, 0);
	ASSERTeq(RCOUNTER(shutdown_state_reinit), 0);

	return ret;
}

static struct test_case test_cases[] = {
	TEST_CASE(test_dirty_clear),
	TEST_CASE(test_dirty_set),
	TEST_CASE(test_invalid_checksum),
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
