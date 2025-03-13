# SPDX-License-Identifier: BSD-3-Clause
# Copyright 2025, Hewlett Packard Enterprise Development LP

#
# src/test/util_sds_check/Makefile -- shutdown_state_check unit test
#
TOP = ../../..
vpath %.c $(TOP)/src/common/
vpath %.c $(TOP)/src/test/unittest/

TARGET = util_sds_check
OBJS = util_sds_check.o\
	shutdown_state.o

LIBPMEM2=y

include ../Makefile.inc

CFLAGS += -Wall -Wextra -Wno-unused-parameter -Wno-ignored-qualifiers

LDFLAGS += $(call extract_funcs, util_sds_check.c)
