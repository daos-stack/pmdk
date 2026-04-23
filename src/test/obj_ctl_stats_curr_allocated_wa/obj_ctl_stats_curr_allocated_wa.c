// SPDX-License-Identifier: BSD-3-Clause
/* Copyright 2017-2023, Intel Corporation */
/* Copyright 2026, Hewlett Packard Enterprise Development LP */

/*
 * obj_ctl_stats_curr_allocated_wa.c -- tests for curr_allocated WA
 */

#include "unittest.h"

#include <../../libpmemobj/obj.h>

#define LAYOUT "ctl"

/*
 * init -- creates a pool, enables stats, and allocates an object to make sure
 * that stats are initialized.
 */
static void
init(const char *path)
{
	PMEMobjpool *pop;
	pop = pmemobj_create(path, LAYOUT, PMEMOBJ_MIN_POOL, S_IWUSR | S_IRUSR);
	UT_ASSERTne(pop, NULL);

	int enabled = 1;
	uint64_t allocated = 0;
	int ret;

	ret = pmemobj_ctl_set(pop, "stats.enabled", &enabled);
	UT_ASSERTeq(ret, 0);

	PMEMoid oid;
	ret = pmemobj_alloc(pop, &oid, 1, 0, NULL, NULL);
	UT_ASSERTeq(ret, 0);

	ret = pmemobj_ctl_get(pop, "stats.heap.curr_allocated", &allocated);
	UT_ASSERTeq(ret, 0);
	UT_ASSERTne(allocated, 0);

	UT_OUT("curr_allocated: %lu", allocated);

	pmemobj_close(pop);
}

/*
 * break_curr_allocated -- break curr_allocated
 */
static void
break_curr_allocated(const char *path)
{
	PMEMobjpool *pop = pmemobj_open(path, LAYOUT);
	UT_ASSERTne(pop, NULL);

	struct pmemobjpool *ppop = (struct pmemobjpool *)pop;
	uint64_t *curr_allocated = &ppop->stats_persistent.heap_curr_allocated;
	*curr_allocated = UINT64_MAX;
	pmem_persist(curr_allocated, sizeof(*curr_allocated));

	pmemobj_close(pop);
}

/*
 * check -- opens the pool, trigger the curr_allocated WA and checks that it is
 * fixed.
 */
static void
check(const char *path)
{
	PMEMobjpool *pop = pmemobj_open(path, LAYOUT);
	UT_ASSERTne(pop, NULL);

	uint64_t allocated = 0;
	int ret;

	ret = pmemobj_ctl_get(pop, "stats.heap.curr_allocated", &allocated);
	UT_ASSERTeq(ret, 0);
	UT_ASSERTne(allocated, 0);
	UT_ASSERTne(allocated, UINT64_MAX);

	UT_OUT("curr_allocated: %lu", allocated);

	pmemobj_close(pop);
}

int
main(int argc, char *argv[])
{
	START(argc, argv, "obj_ctl_stats_curr_allocated_wa");

	if (argc != 3) {
		UT_FATAL("usage: %s file-name step", argv[0]);
	}

	const char *path = argv[1];
	const char step = argv[2][0];

	switch (step) {
		case 'i':
			init(path);
			break;
		case 'b':
			break_curr_allocated(path);
			break;
		case 'c':
			check(path);
			break;
		default:
			UT_FATAL("invalid step");
	}

	DONE(NULL);
}
