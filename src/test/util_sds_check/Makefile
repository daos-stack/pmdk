# SPDX-License-Identifier: BSD-3-Clause
# Copyright 2025, Hewlett Packard Enterprise Development LP

#
# src/test/util_sds_check/Makefile -- shutdown_state_check unit test
#
TOP = ../../..
vpath % .c $(TOP)/src/common/

TARGET = util_sds_check
OBJS = util_sds_check.o\
	shutdown_state_helper.o\
	shutdown_state.o

LIBPMEM2=y

include ../Makefile.inc

CFLAGS += -DDEBUG -Wno-ignored-qualifiers

LDFLAGS += $(call extract_funcs, util_sds_check.c)
