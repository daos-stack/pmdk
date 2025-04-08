# SPDX-License-Identifier: BSD-3-Clause
# Copyright 2016-2019, Intel Corporation
# Copyright 2025, Hewlett Packard Enterprise Development LP

#
# src/test/obj_heap_interrupt/Makefile -- build obj_heap_interrupt unit test
#
TOP = ../../..
vpath % .c $(TOP)/src/common/

TARGET = obj_heap_interrupt
OBJS = obj_heap_interrupt.o shutdown_state_helper.o

LIBPMEMOBJ=internal-debug

include ../Makefile.inc

LDFLAGS += $(call extract_funcs, obj_heap_interrupt.c)
