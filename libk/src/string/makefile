### makefile --- 
## 
## Filename: makefile
## Description: 
## Author: Joakim Bertils
## Maintainer: 
## Created: Sat Feb 10 01:15:31 2018 (+0100)
## Version: 
## Package-Requires: ()
## Last-Updated: Sat Feb 10 01:30:30 2018 (+0100)
##           By: Joakim Bertils
##     Update #: 3
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

OBJECTS=memcmp.o \
memcpy.o \
memmove.o \
memset.o \
strcat.o \
strcmp.o \
strcpy.o \
strlen.o \
memchr.o \
strchr.o \
strnlen.o \
strdup.o \
strndup.o \
strcspn.o \
strspn.o \
strtok.o \
strncmp.o
SUBDIRS=

all: subdirs $(OBJECTS)

%.o: %.c
	$(LIBK_CC) $(LIBK_CC_FLAGS) -c $< -o $(LIBK_BUILD_DIR)/$@

.PHONY: subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

######################################################################
### makefile ends here
