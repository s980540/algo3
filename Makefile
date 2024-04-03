# Project: algo3
# Makefile created by Steve Chang
# Date modified: 2024.02.25

BINNAME = algo.exe
BINDIR 	= $(PROJDIR)/bin
PROJDIR = $(CURDIR)

LIBDIR	= $(PROJDIR)/lib

SUBDIR = \
	src \
	src/checksum \
	src/crc \
	src/mutex \
	src/thread \
	src/utility \

COMMON_INCLUDE = \
	$(CURDIR)/include \

EXTERN_LIBDIR = \
	"C:/MinGW/lib" \

EXTERN_INCLUDE = \
	"C:/MinGW/include" \

CC = gcc
AR = ar
LD = ld

MAKE_RULES := $(PROJDIR)/make/make_rules.mk

# Extra flags to give to compilers when they are supposed to invoke the linker,
# ‘ld’, such as -L. Libraries (-lfoo) should be added to the LDLIBS variable
# instead.
LDFLAGS = \
	-v \
	$(addprefix -L,$(EXTERN_LIBDIR)) \
	$(addprefix -L,$(LIBDIR)) \
	# -static \
	# -static-libgcc \

# Library flags or names given to compilers when they are supposed to invoke
# the linker, ‘ld’. LOADLIBES is a deprecated (but still supported) alternative to
# LDLIBS. Non-library linker flags, such as -L, should go in the LDFLAGS variable.
LIBS = \
	main \
	checksum \
	crc \
	mutex \
	thread \
	utility \

LDLIBS = $(foreach lib,$(LIBS),-l$(lib)) -lpthread	# <-- Do not change this order.

export BINNAME
export BINDIR
export PROJDIR
export LIBDIR
export COMMON_INCLUDE
export EXTERN_LIBDIR
export EXTERN_INCLUDE
export CC AR
export MAKE_RULES

.PHONY: all
all:
	mkdir -p $(BINDIR)
	mkdir -p $(LIBDIR)
	for dir in $(SUBDIR); do \
		cd $$dir; \
		# make -j $@; \
		make $@; \
		cd $(CURDIR); \
	done
	$(CC) $(LDFLAGS) $(LDLIBS) -o $(BINDIR)/$(BINNAME)

.PHONY: clean
clean:
	rm -f $(BINDIR)/$(BINNAME)
	rm -f $(LIBDIR)/*
	for dir in $(SUBDIR); do \
		cd $$dir; \
		make -j $@; \
		cd $(CURDIR); \
	done

.PHONY: objall
objall:
	for dir in $(SUBDIR); do \
		cd $$dir; \
		make -j $@; \
		cd $(CURDIR); \
	done

.PHONY: objclean
objclean:
	for dir in $(SUBDIR); do \
		cd $$dir; \
		make -j $@; \
		cd $(CURDIR); \
	done

.PHONY: depall
depall:
	for dir in $(SUBDIR); do \
		cd $$dir; \
		make -j $@; \
		cd $(CURDIR); \
	done

.PHONY: depclean
depclean:
	for dir in $(SUBDIR); do \
		cd $$dir; \
		make -j $@; \
		cd $(CURDIR); \
	done

.PHONY: format
format:
	$(CURDIR)/Astyle/bin/astyle.exe --options=./_astylerc -R ./*.c,*.h --exclude=AStyle --formatted