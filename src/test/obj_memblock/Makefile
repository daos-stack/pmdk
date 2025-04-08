# SPDX-License-Identifier: BSD-3-Clause
# Copyright 2016-2019, Intel Corporation
# Copyright 2025, Hewlett Packard Enterprise Development LP

#
# src/test/obj_memblock/Makefile -- build memblock unit test
#
TOP = ../../..
vpath % .c $(TOP)/src/common/

TARGET = obj_memblock
OBJS = obj_memblock.o shutdown_state_helper.o

LIBPMEMOBJ=internal-debug

include ../Makefile.inc

LDFLAGS += $(call extract_funcs, obj_memblock.c)
