# SPDX-License-Identifier: BSD-3-Clause
# Copyright 2026, Hewlett Packard Enterprise Development LP

TARGET = obj_ndctl_sds
OBJS = obj_ndctl_sds.o

LIBPMEMOBJ=internal-debug

include ../Makefile.inc
LDFLAGS += $(call extract_funcs, obj_ndctl_sds.c)
