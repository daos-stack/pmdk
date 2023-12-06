NAME          := pmdk
SRC_EXT       := gz
TEST_PACKAGES := libpmem libpmem-devel libpmemobj libpmemobj-devel libpmempool \
		 libpmempool-devel pmempool pmreorder

include packaging/Makefile_packaging.mk
