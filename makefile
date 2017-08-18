#Makefile for compiling the full OS5 project

# Set a flag indicating that we are calling make from the correct place
GLOBAL_CALLING_FROM_ROOT=t

# Get the root directory (the directory in which this file resides)
GLOBAL_ROOT_DIR=$(shell pwd)

GLOBAL_BIN_DIR=$(GLOBAL_ROOT_DIR)/bin
GLOBAL_DEPS_DIR=$(GLOBAL_ROOT_DIR)/deps

# The globally used linker
GLOBAL_LINKER=i686-elf-gcc

# The globally c compiler
GLOBAL_CC=i686-elf-gcc

# The globally used assembler
GLOBAL_AC=nasm

# Export variables for subdirectory use
export GLOBAL_CALLING_FROM_ROOT
export GLOBAL_ROOT_DIR
export GLOBAL_BIN_DIR
export GLOBAL_DEPS_DIR
export GLOBAL_LINKER
export GLOBAL_CC
export GLOBAL_AC

# Builds the kernel and all it's dependencies
all: build-kernel

# Builds the kernel and creates the ISO
iso: build-kernel
	sudo bash mk_iso.sh

# Builds the kernel, creates the ISO and runs it in QEMU
run-debug: iso
	sudo bash run_qemu_debug.sh

run: iso
	sudo bash run_qemu.sh

# Main target to buiid the kernel
build-kernel: build-libk
	@echo "\033[1;33mBuilding Kernel...\033[0m"
	$(MAKE) -C kernel
	@echo "\033[1;32mKernel Build Done!\033[0m"
# Builds (and installs) libk
build-libk: compile-libk install-libk

# Installs libk
install-libk:
	@echo "\033[1;33mInstalling LIBK...\033[0m"
	cp -u libk/build/libk.a $(GLOBAL_DEPS_DIR)/lib
	cp -u -r libk/include/*.h $(GLOBAL_DEPS_DIR)/include
	@echo "\033[1;32mLIBK Installation Done!\033[0m"

# Main target for compiling libk
compile-libk:
	@echo "\033[1;33mBuilding LIBK...\033[0m"
	$(MAKE) -C libk
	@echo "\033[1;32mLIBK Build Done!\033[0m"

.PHONY: clean

# Cleans the directory
clean:
	-$(MAKE) -C kernel clean
	-$(MAKE) -C libk clean
	-find -type f -name '*~' -print0 | xargs -0 rm -f

