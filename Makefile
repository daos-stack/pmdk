NAME          := pmdk
SRC_EXT       := gz
TEST_PACKAGES := libpmem libpmem-devel libpmemblk libpmemblk-devel libpmemlog \
		 libpmemlog-devel libpmemobj libpmemobj-devel libpmempool     \
		 libpmempool-devel pmempool pmreorder

EXTERNAL_RPM_BUILD_OPTIONS := --without=ndctl

include packaging/Makefile_packaging.mk
