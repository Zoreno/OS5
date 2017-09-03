#===============================================================================
# Makefile for compiling the kernel binary
#===============================================================================

#===============================================================================
# Error Check
#===============================================================================

# Check that root called us
ifneq ($(GLOBAL_CALLING_FROM_ROOT),t)
$(error Make should be called from root directory)
endif

#===============================================================================
# Compiling parameters
#===============================================================================

# The name of the kernel binary image
KERNEL_BINARY_NAME=OS5.bin

# Name and path of target executable
KERNEL_TARGET=$(GLOBAL_BIN_DIR)/$(KERNEL_BINARY_NAME)

# Kernel dependencies directory
KERNEL_DEPS_DIR=$(GLOBAL_ROOT_DIR)/deps

# Kernel Directories
KERNEL_ROOT_DIR=$(shell pwd)
KERNEL_SOURCE_DIR=$(KERNEL_ROOT_DIR)/src
KERNEL_INCLUDE_DIR=$(KERNEL_ROOT_DIR)/include
KERNEL_BUILD_DIR=$(KERNEL_ROOT_DIR)/build

# The kernel linker
KERNEL_LINKER=$(GLOBAL_LINKER)

# Name of the linker script used to link kernel
KERNEL_LINK_FILE=$(KERNEL_ROOT_DIR)/link.ld

# Linker flags
KERNEL_LINK_FLAGS=-ffreestanding -O2 -nostdlib -L $(KERNEL_DEPS_DIR)/lib -T $(KERNEL_LINK_FILE)

# Libraries which should be linked into this executable
KERNEL_LINK_LIBS=-lgcc -lk

# Kernel compiler is the same as the global one
KERNEL_CC=$(GLOBAL_CC)

# Kernel compile flags
KERNEL_CC_FLAGS:=-std=gnu99 -O2 -Wall -Wextra -Wpedantic -fno-builtin -g -I $(KERNEL_DEPS_DIR)/include -I $(KERNEL_INCLUDE_DIR)

# Kernel assembler
KERNEL_AC=nasm

# Kernel assembler flags
KERNEL_AC_FLAGS=-felf32

#===============================================================================
# Export
#===============================================================================

# Export linking parameters

export KERNEL_LINKER
export KERNEL_TARGET
export KERNEL_LINK_FLAGS
export KERNEL_LINK_LIBS

# Export c compiling parameters

export KERNEL_CC
export KERNEL_CC_FLAGS

# Export assembler compiling parameters

export KERNEL_AC
export KERNEL_AC_FLAGS

# Export Paths

export KERNEL_ROOT_DIR
export KERNEL_SOURCE_DIR
export KERNEL_INCLUDE_DIR
export KERNEL_BUILD_DIR

#===============================================================================
# Default target
#===============================================================================

all: link

#===============================================================================
# Linking target
#===============================================================================

link: compile
	$(MAKE) -C $(KERNEL_BUILD_DIR)

#===============================================================================
# Compiling target
#===============================================================================

compile:
	$(MAKE) -C $(KERNEL_SOURCE_DIR)

#===============================================================================
# Clean target
#===============================================================================

clean:
	-rm -f $(KERNEL_BUILD_DIR)/*.o

# Quick Reference:
#
# $@ - Name of this target
# $< - Name of first dependency
# $^ - All dependencies separated by space
