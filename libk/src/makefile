# Objects to compile in this directory
OBJECTS=

# Subdirectories to compile
SUBDIRS=string stdlib stdio math

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
