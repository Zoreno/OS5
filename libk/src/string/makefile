OBJECTS=memcmp.o memcpy.o memmove.o memset.o strcat.o strcmp.o strcpy.o strlen.o
SUBDIRS=

all: subdirs $(OBJECTS)

%.o: %.c
	$(LIBK_CC) $(LIBK_CC_FLAGS) -c $< -o $(LIBK_BUILD_DIR)/$@

.PHONY: subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@
