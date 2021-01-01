#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "file_io.h"

enum open_status fopen_read(FILE ** file, const char *filepath){
     *file = fopen(filepath, "rb");
    if (!*file) {
        return OPEN_READ_ERROR;
    }
    return OPEN_OK;
    }
    
enum open_status fopen_write(FILE ** file, const char *filepath){
    *file = fopen(filepath, "wb");
    if (!*file) {
        return OPEN_WRITE_ERROR;
    }
    return OPEN_OK;
    }

enum close_status file_close(FILE * file){
    fclose(file);
    return CLOSE_OK;
    }

uint8_t print_open_status(enum open_status status){
    switch (status){
        case OPEN_OK: {
            printf("File for reading/writing is open\n");
            break;
        }
        case OPEN_WRITE_ERROR:{
            printf("Error opening file for writing\n");
            break;
        }
        case OPEN_READ_ERROR:{
            printf("Error opening file for reading\n");
            break;
        }
    }
    return status;
}

uint8_t print_close_status(enum open_status status){
    printf("File is close");
    return status;
}