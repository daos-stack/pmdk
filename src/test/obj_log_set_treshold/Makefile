# SPDX-License-Identifier: BSD-3-Clause
# Copyright 2024, Intel Corporation
# Copyright 2025, Hewlett Packard Enterprise Development LP

TOP = ../../..
vpath % .c $(TOP)/src/common/

TARGET = obj_log_set_treshold
OBJS = obj_log_set_treshold.o shutdown_state_helper.o

BUILD_STATIC_DEBUG=n
BUILD_STATIC_NONDEBUG=n

# required for proper mock integration
LIBPMEMOBJ=internal-debug

include ../Makefile.inc
LDFLAGS += $(call extract_funcs, obj_log_set_treshold.c)
