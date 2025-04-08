# SPDX-License-Identifier: BSD-3-Clause
# Copyright 2024, Intel Corporation
# Copyright 2025, Hewlett Packard Enterprise Development LP
#

#
# src/test/pmem_log_get_treshold/Makefile -- build pmem_log_get_treshold unit test
#
TOP = ../../..
vpath % .c $(TOP)/src/common/

TARGET = pmem_log_get_treshold
OBJS = pmem_log_get_treshold.o shutdown_state_helper.o

BUILD_STATIC_DEBUG=n
BUILD_STATIC_NONDEBUG=n

# required for proper mock integration
LIBPMEMCOMMON=internal-debug
LIBPMEM=internal-debug

include ../Makefile.inc
LDFLAGS += $(call extract_funcs, pmem_log_get_treshold.c)
