NAME          := pmdk
SRC_EXT       := gz
DL_VERSION    := 1.11.0
TEST_PACKAGES := libpmem libpmem-devel libpmemblk libpmemblk-devel libpmemlog \
		 libpmemlog-devel libpmemobj libpmemobj-devel libpmempool     \
		 libpmempool-devel librpmem librpmem-devel pmempool pmreorder

EXTERNAL_RPM_BUILD_OPTIONS := --without=ndctl

include packaging/Makefile_packaging.mk
