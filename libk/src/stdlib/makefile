### makefile --- 
## 
## Filename: makefile
## Description: 
## Author: Joakim Bertils
## Maintainer: 
## Created: Tue Feb  6 21:03:11 2018 (+0100)
## Version: 
## Package-Requires: ()
## Last-Updated: Tue Feb  6 21:13:39 2018 (+0100)
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
OBJECTS=abs.o random.o div.o bsearch.o itoa.o strtol.o atoi.o qsort.o alloc.o

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
