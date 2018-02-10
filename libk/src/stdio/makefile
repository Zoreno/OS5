### makefile --- 
## 
## Filename: makefile
## Description: 
## Author: Joakim Bertils
## Maintainer: 
## Created: Sat Feb 10 00:48:29 2018 (+0100)
## Version: 
## Package-Requires: ()
## Last-Updated: Sat Feb 10 00:48:30 2018 (+0100)
##           By: Joakim Bertils
##     Update #: 1
## URL: 
## Doc URL: 
## Keywords: 
## Compatibility: 
## 
######################################################################
## 
### Commentary: 
## 
## 
## 
######################################################################
## 
### Change Log:
## 
## 
######################################################################
## 
## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or (at
## your option) any later version.
## 
## This program is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with GNU Emacs.  If not, see <https://www.gnu.org/licenses/>.
## 
######################################################################
## 
### Code:




# Template for compiling the sources to LIBK.
# Copy to directory and fill in OBJECTS and SUBDIRS

# Objects to compile in this directory
OBJECTS=set_stdout.o fputc.o fputs.o putchar.o puts.o vsprintf.o printf.o fprintf.o sprintf.c

# Subdirectories to compile
SUBDIRS=

# Default target. 
all: subdirs $(OBJECTS)

# Rule for compiling c files
%.o: %.c
	$(LIBK_CC) $(LIBK_CC_FLAGS) -c $< -o $(LIBK_BUILD_DIR)/$@

.PHONY: subdirs $(SUBDIRS)

# Rule for compiling all subdirs
subdirs: $(SUBDIRS)

# Rule for compiling a specific subdir
$(SUBDIRS):
	$(MAKE) -C $@

######################################################################
### makefile ends here
