NAME          := pmdk
SRC_EXT       := gz
TEST_PACKAGES := libpmem libpmem-devel libpmemblk libpmemblk-devel libpmemlog \
		 libpmemlog-devel libpmemobj libpmemobj-devel libpmempool     \
		 libpmempool-devel pmempool pmreorder

include packaging/Makefile_packaging.mk
