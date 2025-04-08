# SPDX-License-Identifier: BSD-3-Clause
# Copyright 2015-2019, Intel Corporation
# Copyright 2025, Hewlett Packard Enterprise Development LP

#
# src/test/obj_bucket/Makefile -- build bucket unit test
#
TOP = ../../..
vpath % .c $(TOP)/src/common/

TARGET = obj_bucket
OBJS = obj_bucket.o shutdown_state_helper.o

LIBPMEMOBJ=internal-debug

include ../Makefile.inc

LDFLAGS += $(call extract_funcs, obj_bucket.c)
