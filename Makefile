NAME        := pmdk
VERSION     := 1.5.1
RELEASE     := 1
DIST        := $(shell rpm --eval %{dist})
SRPM        := _topdir/SRPMS/$(NAME)-$(VERSION)-$(RELEASE)$(DIST).src.rpm
RPMS        := _topdir/RPMS/x86_64/$(NAME)-$(VERSION)-$(RELEASE)$(DIST).x86_64.rpm           \
	       _topdir/RPMS/x86_64/$(NAME)-devel-$(VERSION)-$(RELEASE)$(DIST).x86_64.rpm     \
	       _topdir/RPMS/x86_64/$(NAME)-debuginfo-$(VERSION)-$(RELEASE)$(DIST).x86_64.rpm
SPEC        := $(NAME).spec
SRC_EXT     := gz
SOURCE      := https://github.com/pmem/$(NAME)/archive/$(VERSION).tar.$(SRC_EXT)
SOURCES     := _topdir/SOURCES/$(NAME)-$(VERSION).tar.$(SRC_EXT)
TARGETS      := $(RPMS) $(SRPM)

all: $(TARGETS)

%/:
	mkdir -p $@

_topdir/SOURCES/%: % | _topdir/SOURCES/
	rm -f $@
	ln $< $@

$(NAME)-$(VERSION).tar.$(SRC_EXT):
	curl -f -L -O '$(SOURCE)'
	mv $(VERSION).tar.$(SRC_EXT) $@

# see https://stackoverflow.com/questions/2973445/ for why we subst
# the "rpm" for "%" to effectively turn this into a multiple matching
# target pattern rule
$(subst rpm,%,$(RPMS)): $(SPEC) $(SOURCES)
	rpmbuild -bb --without rpmem --without ndctl \
	         --define "%_topdir $$PWD/_topdir"   \
                 --nocheck $(SPEC)


$(SRPM): $(SPEC) $(SOURCES)
	rpmbuild -bs --define "%_topdir $$PWD/_topdir" $(SPEC)

srpm: $(SRPM)

$(RPMS): Makefile

rpms: $(RPMS)

ls: $(TARGETS)
	ls -ld $^

mockbuild: $(SRPM) Makefile
	mock --nocheck $<

rpmlint: $(SPEC)
	rpmlint $<

.PHONY: srpm rpms ls mockbuild rpmlint FORCE
