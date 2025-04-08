# SPDX-License-Identifier: BSD-3-Clause
# Copyright 2017-2018, Intel Corporation
# Copyright 2025, Hewlett Packard Enterprise Development LP

#
# src/test/pmem_has_auto_flush/Makefile -- build pmem_has_auto_flush test
#
include ../../common.inc
TOP = ../../..
vpath % .c $(TOP)/src/common/

LIBPMEMCOMMON=internal-debug
LIBPMEM=internal-debug

TARGET = pmem_has_auto_flush

OBJS = pmem_has_auto_flush.o \
	mocks_posix.o \
	shutdown_state_helper.o

include ../Makefile.inc
LDFLAGS += $(call extract_funcs, mocks_posix.c)
