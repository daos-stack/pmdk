# SPDX-License-Identifier: BSD-3-Clause
# Copyright 2015-2019, Intel Corporation
# Copyright 2025, Hewlett Packard Enterprise Development LP

#
# src/test/obj_critnib/Makefile -- build obj_critnib unit test
#
TOP = ../../..
vpath % .c $(TOP)/src/common/

TARGET = obj_critnib
OBJS = obj_critnib.o shutdown_state_helper.o

LIBPMEMOBJ=internal-debug

include ../Makefile.inc

LDFLAGS += $(call extract_funcs, obj_critnib.c)
