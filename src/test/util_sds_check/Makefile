# SPDX-License-Identifier: BSD-3-Clause
# Copyright 2025, Hewlett Packard Enterprise Development LP

#
# src/test/util_sds_check/Makefile -- shutdown_state_check unit test
#
TOP = ../../..
vpath %.c $(TOP)/src/test/unittest/
vpath %.c $(TOP)/src/common/

TARGET = util_sds_check
OBJS = util_sds_check.o\
	shutdown_state.o\
	ut_pmem2_config.o\
	ut_pmem2_source.o\
	ut_pmem2_utils.o

LIBPMEM2=internal-debug

include ../Makefile.inc
# add DEBUG define for logs from shutdown_state.c
CFLAGS += -DDEBUG=1
LDFLAGS += $(call extract_funcs, util_sds_check.c)
