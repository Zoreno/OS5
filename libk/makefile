# Makefile for compiling the LIBK kernel library

# Check that root called us
ifneq ($(GLOBAL_CALLING_FROM_ROOT),t)
$(error Make should be called from root directory)
endif

LIBK_DIR=$(shell pwd)

LIBK_BUILD_DIR=$(LIBK_DIR)/build
LIBK_SOURCE_DIR=$(LIBK_DIR)/src
LIBK_INCLUDE_DIR=$(LIBK_DIR)/include

LIBK_TARGET_NAME=libk.a

LIBK_ARCHIVER=ar
LIBK_ARCHIVER_FLAGS=rcs

LIBK_CC=$(GLOBAL_CC)
LIBK_CC_FLAGS=-std=gnu99 -O2 -Wall -Wextra -Wpedantic -fno-builtin -I $(LIBK_INCLUDE_DIR) -lgcc

LIBK_DEBUG=t

# If we should debug, append the debug flag
ifeq ($(LIBK_DEBUG), t)
LIBK_CC_FLAGS += -g
endif

export LIBK_ARCHIVER
export LIBK_ARCHIVER_FLAGS
export LIBK_TARGET_NAME

export LIBK_CC
export LIBK_CC_FLAGS
export LIBK_BUILD_DIR

all: link

link: compile
	$(MAKE) -C $(LIBK_BUILD_DIR) link

compile:
	$(MAKE) -C $(LIBK_SOURCE_DIR)

.PHONY: clean

clean:
	-rm -f $(LIBK_BUILD_DIR)/*.o
