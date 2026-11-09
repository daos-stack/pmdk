# SPDX-License-Identifier: BSD-3-Clause
# Copyright 2015-2023, Intel Corporation
# Copyright 2026, Hewlett Packard Enterprise Development LP

#
# src/test/tools/Makefile -- build unit test helpers
#

TOP = ../../..

TESTCONFIG=$(TOP)/src/test/testconfig.sh

DIRS = \
       pmemspoil\
       pmemwrite\
       pmemalloc\
       pmemobjcli\
       pmemdetect\
       gran_detecto\
       ddmap\
       cmpmap\
       extents\
       fallocate_detect\
       obj_verify\
       usc_permission_check\
       anonymous_mmap\
       mapexec

ifeq ($(ARCH), x86_64)
DIRS += \
	cpufd
endif

all     : TARGET = all
clean   : TARGET = clean
clobber : TARGET = clobber
cstyle  : TARGET = cstyle
sparse  : TARGET = sparse

all test cstyle clean clobber sparse: $(DIRS)

$(TESTCONFIG):

$(DIRS):
	$(MAKE) -C $@ $(TARGET)

check pcheck pycheck: all

.PHONY: all clean clobber cstyle check pcheck $(DIRS)
