# SPDX-License-Identifier: BSD-3-Clause
# Copyright 2025, Hewlett Packard Enterprise Development LP

#
# src/test/util_sds_check/Makefile -- shutdown_state_check unit test
#
BUILD_STATIC_DEBUG=n
BUILD_STATIC_NONDEBUG=n

TARGET = util_sds_check
OBJS = util_sds_check.o

LIBPMEM=y
LIBPMEMCOMMON=internal-debug

include ../Makefile.inc

LDFLAGS += $(call extract_funcs, util_sds_check.c)
