# Use fake pmem; we really want tmpfs if possible.
# No non-pmem dir, as real syncs there are slow.
PMEM_FS_DIR=/tmp
# Use cache flushes instead of msync().
PMEM_FS_DIR_FORCE_PMEM=1
# Don't try static libs.
TEST_BUILD="debug nondebug"
# Display execution time of each test
TM=1
# Be nice to slow hardware.
TEST_TIMEOUT=30m
# We want all failures, not just the first one.
KEEP_GOING=y
# Fails can fill the disk, and we can't investigate them anyway.
CLEAN_FAILED=y
