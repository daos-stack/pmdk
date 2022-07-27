NAME          := pmdk
SRC_EXT       := gz
ifeq ($(DL_VERSION),)
DL_VERSION    := $(subst ~,,$(VERSION))
endif
TEST_PACKAGES := libpmem libpmem-devel libpmemblk libpmemblk-devel libpmemlog \
		 libpmemlog-devel libpmemobj libpmemobj-devel libpmempool     \
		 libpmempool-devel pmempool pmreorder

EXTERNAL_RPM_BUILD_OPTIONS := --without=ndctl

include packaging/Makefile_packaging.mk
