#ifndef _LIBK__FILE_H
#define _LIBK__FILE_H

#include <stdint.h>

typedef char (*read_function)(void);
typedef void (*write_function)(char);

typedef void (*open_function)(const char*);
typedef void (*close_function)(const char*);

typedef struct {
    char name[32];
    uint32_t flags;
    uint32_t fileLength;

    read_function read;
    write_function write;

    open_function open;
    close_function close;
} FILE, *PFILE;

#endif
