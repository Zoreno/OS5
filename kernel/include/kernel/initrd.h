#ifndef __INITRD_H_
#define __INITRD_H_

#include <stdint.h>
#include <string.h>

/*

  Initrd layout:

  _______________
  |             |
  | FS Header   |
  |_____________|
  |             |
  | File Header |
  |_____________|
  |             |
  | File Header |
  |_____________|
  |             |
  | ...         |
  |_____________|
  |             |
  | File Header |
  |_____________|
  |             |
  | File Data   |
  |_____________|
  
  
  File Header: (Can be a directory)
  
  struct _file_header
  {
  char Name[20];
  
  uint32_t size;
 
  uint32_t offset;
 
  uint32_t flags; // This is now too large
  };
  
  Each directory's file area is a File Header array. Number of files is size/sizeof(struct _file_header)
  
  Root is a directory with offset 0.
  
  File Path:
  
  / is root
  /file1 is file named file1 in root
  /dir1/file1 is file named file1 in dir named dir1
  
*/

typedef struct _initrd_fs
{

    // Name of the file system
    char name[20];

    // Address where the image is loaded
    uint32_t image;

    // Size of image
    uint32_t size;

    // Number of files in root.
    uint32_t file_count;
} initrd_fs_t;

typedef struct _initrd_node
{
    char name[120];
    uint32_t size;
    
    uint32_t offset;

    uint32_t position;
    uint32_t eof;
} initrd_node_t;

int initrd_open(initrd_fs_t* fs, initrd_node_t *node, char *path, char *mode);


#endif // __INITRD_H_
