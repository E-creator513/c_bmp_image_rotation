#ifndef FILE_IO_H
#define FILE_IO_H
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
enum open_status {
    OPEN_OK = 0,
    OPEN_WRITE_ERROR,
    OPEN_READ_ERROR,
};

enum close_status {
    CLOSE_OK = 0,
};
enum open_status fopen_read(FILE ** file, const char *filepath);
enum open_status fopen_write(FILE ** file, const char *filepath);
enum close_status file_close(FILE * file);

uint8_t print_open_status(enum open_status status);
uint8_t print_close_status(enum open_status status);
#endif
