# SPDX-License-Identifier: BSD-3-Clause
# Copyright 2017-2019, Intel Corporation
# Copyright 2025, Hewlett Packard Enterprise Development LP

#
# src/test/obj_pmalloc_rand_mt/Makefile -- build obj_pmalloc_rand_mt unit test
#
TOP = ../../..
vpath % .c $(TOP)/src/common/

TARGET = obj_pmalloc_rand_mt
OBJS = obj_pmalloc_rand_mt.o shutdown_state_helper.o

LIBPMEMOBJ=internal-debug
LIBPMEMCOMMON=y

include ../Makefile.inc
