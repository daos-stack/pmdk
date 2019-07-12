NAME    := pmdk
SRC_EXT := gz
SOURCE  = https://github.com/pmem/$(NAME)/archive/$(VERSION).tar.$(SRC_EXT)

RPM_BUILD_OPTIONS := --without rpmem --without ndctl --nocheck
MOCK_OPTIONS      := --nocheck

include Makefile_packaging.mk

