# SPDX-License-Identifier: BSD-3-Clause
# Copyright 2015-2018, Intel Corporation
# Copyright 2025, Hewlett Packard Enterprise Development LP

#
# src/test/obj_sds/Makefile -- shutdown_state unit test
#
TOP = ../../..
vpath % .c $(TOP)/src/common/

TARGET = obj_sds
OBJS = obj_sds.o shutdown_state_helper.o

LIBPMEMPOOL=y
LIBPMEMOBJ=internal-debug
include ../Makefile.inc
LDFLAGS += $(call extract_funcs, obj_sds.c)
