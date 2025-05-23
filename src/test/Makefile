# SPDX-License-Identifier: BSD-3-Clause
# Copyright 2014-2024, Intel Corporation
#

#
# src/test/Makefile -- build all unit tests
#
# Makefile -- build all unit tests
#

include ../common.inc

TEST_DEPS = \
	unittest\
	tools

OBJ_DEPS = \
	obj_list

# long tests first
OBJ_TESTS = \
	obj_basic_integration\
	obj_many_size_allocs\
	obj_realloc\
	obj_sync\
	obj_action\
	obj_alloc\
	obj_badblock\
	obj_bucket\
	obj_check\
	obj_constructor\
	obj_critnib\
	obj_critnib_mt\
	obj_ctl_alignment\
	obj_ctl_alloc_class\
	obj_ctl_alloc_class_config\
	obj_ctl_arenas\
	obj_ctl_config\
	obj_ctl_debug\
	obj_ctl_heap_size\
	obj_ctl_stats\
	obj_debug\
	obj_defrag\
	obj_defrag_advanced\
	obj_direct\
	obj_direct_volatile\
	obj_extend\
	obj_first_next\
	obj_fragmentation\
	obj_fragmentation2\
	obj_heap\
	obj_heap_interrupt\
	obj_heap_reopen\
	obj_heap_state\
	obj_include\
	obj_lane\
	obj_layout\
	obj_list_insert\
	obj_list_move\
	obj_list_recovery\
	obj_list_remove\
	obj_list_valgrind\
	obj_list_macro\
	obj_locks\
	obj_log_get_treshold\
	obj_log_set_function\
	obj_log_set_treshold\
	obj_mem\
	obj_memblock\
	obj_memcheck\
	obj_memcheck_register\
	obj_memops\
	obj_oid_thread\
	obj_out_of_memory\
	obj_persist_count\
	obj_pmalloc_basic\
	obj_pmalloc_mt\
	obj_pmalloc_oom_mt\
	obj_pmalloc_rand_mt\
	obj_pmemcheck\
	obj_pool\
	obj_pool_lock\
	obj_pool_lookup\
	obj_pool_open_mt\
	obj_recovery\
	obj_recreate\
	obj_reserve_mt\
	obj_root\
	obj_reorder_basic\
	obj_strdup\
	obj_sds\
	obj_toid\
	obj_tx_alloc\
	obj_tx_alloc_mt\
	obj_tx_add_range\
	obj_tx_add_range_direct\
	obj_tx_callbacks\
	obj_tx_flow\
	obj_tx_free\
	obj_tx_invalid\
	obj_tx_lock\
	obj_tx_locks\
	obj_tx_locks_abort\
	obj_tx_mt\
	obj_tx_realloc\
	obj_tx_strdup\
	obj_tx_user_data\
	obj_ulog_advanced\
	obj_ulog_size\
	obj_zones

OTHER_TESTS = \
	arch_flags\
	core_log\
	core_log_default_function\
	core_log_function_mt\
	core_log_internal\
	core_log_max\
	core_log_no_func\
	core_log_threshold_mt\
	checksum\
	compat_incompat_features\
	ctl_prefault\
	ctl_cow\
	magic\
	out_err\
	out_err_mt\
	pmemobjcli\
	pmemspoil\
	scope\
	set_funcs\
	traces\
	unicode_match_script\
	util_badblock\
	util_ctl\
	util_extent\
	util_file_create\
	util_file_open\
	util_is_absolute\
	util_is_poolset\
	util_is_zeroed\
	util_map_proc\
	util_parse_size\
	util_pool_hdr\
	util_poolset\
	util_poolset_foreach\
	util_poolset_parse\
	util_poolset_size\
	util_ravl\
	util_sds\
	util_sds_check\
	util_uuid_generate\
	util_vec\
	util_vecq\
	log_errno\
	valgrind_check

ifeq ($(ARCH), x86_64)
OTHER_TESTS += \
	util_cpuid
endif

PMEM_TESTS = \
	pmem_include\
	pmem_is_pmem\
	pmem_is_pmem_posix\
	pmem_log_get_treshold\
	pmem_log_set_function\
	pmem_log_set_treshold\
	pmem_map_file\
	pmem_has_auto_flush\
	pmem_deep_persist\
	pmem_memcpy\
	pmem_memmove\
	pmem_memset\
	pmem_movnt\
	pmem_movnt_align\
	pmem_eADR_functions\
	pmem_valgr_simple\
	pmem_unmap

PMEM2_TESTS = \
	pmem2_api\
	pmem2_compat\
	pmem2_badblock\
	pmem2_config\
	pmem2_source\
	pmem2_source_alignment\
	pmem2_source_size\
	pmem2_granularity\
	pmem2_include\
	pmem2_integration\
	pmem2_granularity_detection\
	pmem2_map\
	pmem2_map_from_existing\
	pmem2_map_prot\
	pmem2_persist\
	pmem2_persist_valgrind\
	pmem2_perror\
	pmem2_memcpy\
	pmem2_memmove\
	pmem2_memset\
	pmem2_movnt\
	pmem2_movnt_align\
	pmem2_mem_ext\
	pmem2_deep_flush\
	pmem2_vm_reservation\
	pmem2_usc

ifeq ($(OS_DIMM),ndctl)
PMEM2_TESTS += \
	pmem2_badblock_mocks\
	pmem2_source_numa
else
$(info NOTE: Skipping tests because libndctl is disabled (see NDCTL_ENABLE)\
		Skipped tests: pmem2_badblock_mocks pmem2_source_numa)
endif

PMEMPOOL_TESTS = \
	pmempool_check\
	pmempool_create\
	pmempool_dump\
	pmempool_feature\
	pmempool_help\
	pmempool_info\
	pmempool_rm\
	pmempool_sync\
	pmempool_transform\
	pmempool_inval

EXAMPLES_TESTS = \
	ex_libpmem\
	ex_libpmem2\
	ex_libpmemobj\
	ex_linkedlist\
	ex_pmreorder

LIBPMEMPOOL_DEPS = \
	libpmempool_api

LIBPMEMPOOL_TESTS = \
	libpmempool_include\
	libpmempool_backup\
	libpmempool_check_version\
	libpmempool_feature\
	libpmempool_rm

LIBPMEMPOOL_MOD_DEPS = \
	libpmempool_sync

LIBPMEMPOOL_MOD_TESTS = \
	libpmempool_transform

DAXIO_TESTS = \
	daxio

PMREORDER_TESTS = \
	pmreorder_flushes\
	pmreorder_simple\
	pmreorder_stack

LOCAL_TESTS = \
	$(OBJ_TESTS)\
	$(OTHER_TESTS)\
	$(PMEM_TESTS)\
	$(PMEM2_TESTS)\
	$(PMEMPOOL_TESTS)\
	$(LIBPMEMPOOL_TESTS)\
	$(LIBPMEMPOOL_MOD_TESTS)\
	$(DAXIO_TESTS)\
	$(PMREORDER_TESTS)

ifneq ($(BUILD_EXAMPLES),n)
	LOCAL_TESTS += $(EXAMPLES_TESTS)
endif

TESTS = \
	$(LOCAL_TESTS)

TESTS_BUILD = \
	$(TEST_DEPS)\
	$(OBJ_DEPS)\
	$(LIBPMEMPOOL_DEPS)\
	$(LIBPMEMPOOL_MOD_DEPS)\
	$(TESTS)

ifneq ($(BLACKLIST_FILE),)
ifeq ("$(wildcard $(BLACKLIST_FILE))","")
$(error Missing blacklist file: $(BLACKLIST_FILE))
endif
	BLACKLIST_TESTS := $(shell cat $(BLACKLIST_FILE))
	TESTS := $(filter-out $(BLACKLIST_TESTS),$(TESTS))
	LOCAL_TESTS := $(filter-out $(BLACKLIST_TESTS),$(LOCAL_TESTS))
	TESTS_BUILD := $(filter-out $(BLACKLIST_TESTS),$(TESTS_BUILD))
endif

all     : TARGET = all
clean   : TARGET = clean
clobber : TARGET = clobber
test    : TARGET = test
cstyle  : TARGET = cstyle
format  : TARGET = format
check   : TARGET = check
pcheck  : TARGET = pcheck
sparse  : TARGET = sparse
pycheck : TARGET = pycheck

DIR_SYNC=$(TOP)/src/test/.sync-dir
SYNC_EXT=synced
TESTCONFIG=$(TOP)/src/test/testconfig.sh
FILE_MAX_DAX_DEVICES=$(TOP)/src/test/tools/anonymous_mmap/max_dax_devices

all test format sparse: $(TESTS_BUILD) envconfig.sh envconfig.py

cstyle: $(TESTS_BUILD)
	$(CHECK_SHEBANG) $(foreach dir,$(TESTS_BUILD),$(dir)/TEST? $(dir)/TEST??)

clean clobber: $(TESTS_BUILD)
	$(RM) -r $(DIR_SYNC)
	$(RM) *.$(SYNC_EXT)
	$(RM) $(FILE_MAX_DAX_DEVICES)
	$(RM) envconfig.sh envconfig.py

$(TESTS) $(OBJ_DEPS) $(LIBPMEMPOOL_DEPS) $(LIBPMEMPOOL_MOD_DEPS): $(TEST_DEPS)

$(OBJ_TESTS): $(OBJ_DEPS)
$(LIBPMEMPOOL_TESTS): $(LIBPMEMPOOL_DEPS)
$(LIBPMEMPOOL_MOD_TESTS): $(LIBPMEMPOOL_MOD_DEPS)

$(TESTS_BUILD):
	$(MAKE) -C $@ $(TARGET)

envconfig.sh:
	@printf "# autogenerated file\nGLOBAL_LIB_PATH=%s\nGLOBAL_PATH=%s\nGLOBAL_PKG_CONFIG_PATH=%s\n" "$(LIBFABRIC_LD_LIBRARY_PATHS):$(LIBNDCTL_LD_LIBRARY_PATHS)" "$(LIBFABRIC_PATH)" "$(PKG_CONFIG_PATH)" > envconfig.sh

PMEM2_AVX512F_ENABLED := $(shell strings $(TOP)/src/debug/libpmem2/libpmem2_all.o 2>&1 | \
	grep -q "avx512f supported, but disabled at build time" && echo "0" || echo "1")

PMEM2_MOVDIR64B_ENABLED := $(shell strings $(TOP)/src/debug/libpmem2/libpmem2_all.o 2>&1 | \
	grep -q "movdir64b supported, but disabled at build time" && echo "0" || echo "1")

envconfig.py:
	@printf "# autogenerated file\nconfig = {\n  'GLOBAL_LIB_PATH': '%s',\n  'PMEM2_AVX512F_ENABLED': '%s',\n  'PMEM2_MOVDIR64B_ENABLED': '%s',\n  'GLOBAL_PATH': '%s',\n  'GLOBAL_PKG_CONFIG_PATH': '%s'\n}\n" \
		"$(LIBFABRIC_LD_LIBRARY_PATHS):$(LIBNDCTL_LD_LIBRARY_PATHS)" "$(PMEM2_AVX512F_ENABLED)" "$(PMEM2_MOVDIR64B_ENABLED)" "$(LIBFABRIC_PATH)" "$(PKG_CONFIG_PATH)" > envconfig.py

memcheck-summary:
	grep ERROR */memcheck*.log

memcheck-summary-errors:
	grep ERROR */memcheck*.log | grep -v " 0 errors" || true

memcheck-summary-leaks:
	grep "in use at exit" */memcheck*.log | grep -v " 0 bytes in 0 blocks" || true

check:
	@[ -z "$(BLACKLIST_TESTS)" ] || echo "Blacklisted tests: $(BLACKLIST_TESTS)"
	@./RUNTESTS.sh $(RUNTEST_OPTIONS) $(LOCAL_TESTS)
	$(MAKE)
	@echo "No failures."

pycheck: TARGET = pycheck
pycheck: $(TESTS)
	@echo "No failures."

pcheck: pcheck-local-quiet
	@echo "No failures."

pcheck-log: TARGET = pcheck
pcheck-log: $(LOG_TESTS)
	@echo "No failures."

pcheck-obj: TARGET = pcheck
pcheck-obj: $(OBJ_TESTS)
	@echo "No failures."

pcheck-other: TARGET = pcheck
pcheck-other: $(OTHER_TESTS)
	@echo "No failures."

pcheck-pmem: TARGET = pcheck
pcheck-pmem: $(PMEM_TESTS)
	@echo "No failures."

pcheck-pmem2: TARGET = pcheck
pcheck-pmem2: $(PMEM2_TESTS)
	@echo "No failures."

pcheck-pmempool: TARGET = pcheck
pcheck-pmempool: $(PMEMPOOL_TESTS)
	@echo "No failures."

pcheck-libpmempool: TARGET = pcheck
pcheck-libpmempool: $(LIBPMEMPOOL_TESTS)
	@echo "No failures."

pcheck-local-quiet: TARGET = pcheck
pcheck-local-quiet: $(LOCAL_TESTS)

pcheck-local: pcheck-local-quiet
	@echo "No failures."

$(TESTCONFIG):

SUPP_SYNC_FILES=$(shell echo *.supp | sed s/supp/$(SYNC_EXT)/g)

%.$(SYNC_EXT): %.supp $(TESTCONFIG)
	cp $(shell echo $^ | cut -d" " -f1) $(DIR_SYNC)
	@touch $@

.PHONY: all check clean clobber cstyle pcheck pcheck-log pcheck-obj\
	 pcheck-other pcheck-pmem pcheck-pmempool\
	 test unittest tools format pcheck-libpmempool pycheck\
	 pcheck-local $(TESTS_BUILD)
