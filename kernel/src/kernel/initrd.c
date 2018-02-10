#include <kernel/initrd.h>
#include <string.h>
#include <stdint.h>

typedef struct _initrd_image_header
{
    char magic[4]; // 'J' 'O' 'R' 'D'

    uint16_t version_minor;
    uint16_t version_major;
    
    uint32_t file_count;
} __attribute__((packed)) image_header_t;

int initrd_mount(initrd_fs_t *fs, uint32_t image_start, uint32_t image_size)
{
    if (image_start == 0 || image_size == 0)
    {
        // Image invalid

        // TODO: Implement error codes

        return -1;
    }

    image_header_t *header = (image_header_t *)image_start;

    // Check the file header

    // TODO: Check if little or big endian
    if(strncmp(header->magic, "JORD", 4) != 0)
    {
        // Header invalid 

        // TODO: Insert error codes
        return -1;
    }

    strcpy(fs->name, "initrd");
    fs->image = image_start;
    fs->size = image_size;
    fs->file_count = header->file_count;

    return 0;
}

int initrd_open(initrd_fs_t *fs, initrd_node_t *node, char *path, char *mode)
{
    // Read past any leading '/' since we for now interpret every path as absolute
    if(*path == '/')
    {
        ++path;
    }

    char *delim = strchr(path, '/');

    if (delim)
    {
        // We did find a '/'. File must be in a subdirectory.
        
        // Open and read subdir
    }

    // Open file
}


int initrd_close(initrd_fs_t *fs, initrd_node_t *node)
{
    // Do nothing
}
