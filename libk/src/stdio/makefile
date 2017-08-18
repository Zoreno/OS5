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
