# SPDX-License-Identifier: BSD-2-Clause-Patent
# Copyright (c) 2019-2024 Intel Corporation

NAME          := pmdk
SRC_EXT       := gz
TEST_PACKAGES := libpmem libpmem-devel libpmemobj libpmemobj-devel libpmempool \
		 libpmempool-devel pmempool pmreorder

include packaging/Makefile_packaging.mk
