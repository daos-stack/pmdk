// SPDX-License-Identifier: BSD-3-Clause
/* Copyright 2026, Hewlett Packard Enterprise Development LP */

/*
 * obj_ctl_stats_curr_allocated_wa.c -- tests for curr_allocated WA
 */

#include "unittest.h"

#include <../../libpmemobj/obj.h>

#define LAYOUT "ctl"

#define MB (1 << 20)

/*
 * set_curr_allocated -- set curr_allocated to a specific value
 */
static void
set_curr_allocated(PMEMobjpool *pop, uint64_t value)
{
	struct pmemobjpool *ppop = (struct pmemobjpool *)pop;
	uint64_t *curr_allocated = &ppop->stats_persistent.heap_curr_allocated;
	*curr_allocated = value;
	pmem_persist(curr_allocated, sizeof(*curr_allocated));
}

/*
 * get_curr_allocated -- get the curr_allocated value
 */
static uint64_t
get_curr_allocated(PMEMobjpool *pop)
{
	int ret;
	uint64_t allocated;

	ret = pmemobj_ctl_get(pop, "stats.heap.curr_allocated", &allocated);
	UT_ASSERTeq(ret, 0);

	return allocated;
}

/*
 * huge_alloc -- make a huge allocation
 */
static void
huge_alloc(PMEMobjpool *pop, PMEMoid *oid)
{
	int ret = pmemobj_alloc(pop, oid, 4 * MB, 0, NULL, NULL);
	UT_ASSERTeq(ret, 0);
}

static void
underflow(PMEMobjpool *pop, uint64_t *exp_allocated)
{
	UT_ASSERTne(exp_allocated, NULL);

	/* Create a huge allocation and query the statistic */
	PMEMoid oid;
	huge_alloc(pop, &oid);

	*exp_allocated = get_curr_allocated(pop);

	/* Inject a smaller than expected value. */
	set_curr_allocated(pop, *exp_allocated - 1);

	/* Trigger underflow. */
	pmemobj_free(&oid);
}

/*
 * test -- allocates an object to make sure that stats are initialized.
 */
static void
test(PMEMobjpool *pop)
{
	PMEMoid oid;
	uint64_t exp_allocated;

	/* trigger underflow */
	underflow(pop, &exp_allocated);

	/* Check the statistic is updated correctly. */
	UT_ASSERTeq(get_curr_allocated(pop), 0);

	/* trigger underflow and attempt crossing zero again */
	underflow(pop, &exp_allocated);
	huge_alloc(pop, &oid);

	/* Check the statistic is updated correctly. */
	UT_ASSERTeq(get_curr_allocated(pop), exp_allocated);
}

int
main(int argc, char *argv[])
{
	START(argc, argv, "obj_ctl_stats_curr_allocated_wa");

	if (argc != 2) {
		UT_FATAL("usage: %s file-name", argv[0]);
	}

	const char *path = argv[1];

	PMEMobjpool *pop;
	pop = pmemobj_create(path, LAYOUT, PMEMOBJ_MIN_POOL, S_IWUSR | S_IRUSR);
	UT_ASSERTne(pop, NULL);

	int enabled = 1;
	int ret;

	/* Enable stats. */
	ret = pmemobj_ctl_set(pop, "stats.enabled", &enabled);
	UT_ASSERTeq(ret, 0);

	test(pop);

	pmemobj_close(pop);

	DONE(NULL);
}
