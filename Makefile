NAME          := pmdk
SRC_EXT       := gz
TEST_PACKAGES := libpmem libpmem-devel libpmemobj libpmemobj-devel libpmempool \
		 libpmempool-devel pmempool pmreorder

# EXTERNAL_RPM_BUILD_OPTIONS := --without=ndctl
EXTERNAL_RPM_BUILD_OPTIONS := --define _skip_check=1

include packaging/Makefile_packaging.mk
