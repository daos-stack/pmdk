NAME    := pmdk
SRC_EXT := gz
SOURCE  = https://github.com/pmem/$(NAME)/archive/$(VERSION).tar.$(SRC_EXT)

RPM_BUILD_OPTIONS := --without rpmem --without ndctl
MOCK_OPTIONS      := --nocheck

include packaging/Makefile_packaging.mk