# SPDX-License-Identifier: BSD-3-Clause
# Copyright 2015-2024, Intel Corporation
# Copyright 2025, Hewlett Packard Enterprise Development LP

#
# src/test/obj_persist_count/Makefile -- build obj_persist_count unit test
#
TOP = ../../..
vpath % .c $(TOP)/src/common/

TARGET = obj_persist_count
OBJS = obj_persist_count.o shutdown_state_helper.o

LIBPMEMOBJ=internal-debug

BUILD_STATIC_DEBUG=n
BUILD_STATIC_NONDEBUG=n

include ../Makefile.inc

LDFLAGS += $(call extract_funcs, obj_persist_count.c)
