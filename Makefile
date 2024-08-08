NAME          := pmdk
SRC_EXT       := gz
TEST_PACKAGES := libpmem libpmem-devel libpmemobj libpmemobj-devel libpmempool \
		 libpmempool-devel pmempool pmreorder

EXTERNAL_RPM_BUILD_OPTIONS := --with=ndctl

include packaging/Makefile_packaging.mk
