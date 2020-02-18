NAME    := pmdk
SRC_EXT := gz

EXTERNAL_RPM_BUILD_OPTIONS := --without=ndctl

include packaging/Makefile_packaging.mk
