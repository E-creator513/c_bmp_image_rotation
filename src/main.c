#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bmp_io.h"
#include "bmp_struct.h"
#include "bmp_rotation.h"

#define STANDART_OUT_FILE "output.bmp"

// i use arch btw

int main(int argc, char *argv[]) {
    if (argc <2) {
        printf("Usage: %s <input_file> [output file]\n", argv[0]);
        return 1;
    }
 const char *input_path = argv[1];
    const char *output_path;
    if (argc < 3) {
        output_path = STANDART_OUT_FILE;
    } else {
        output_path = argv[2];
    }
    printf("Input File: '%s' \nOutput File: '%s'\n", input_path, output_path);
    struct image *img = malloc_bmp();

    FILE *in = fopen(input_path, "rb");
    uint8_t status_r = from_bmp(in,img);
    switch (status_r) {
        case READ_OK: {
            printf("File '%s' is loaded\n",input_path);
            break;
        }
        case READ_INVALID_PATH: {
            printf("Input file path not found\n");
            return 1;
        }
        case READ_INVALID_HEADER: {
            printf("Invalid file header\n");
            return 1;
        }
        case READ_INVALID_BITS: {
            printf("Only 24-bit bpm file supported\n");
            return 1;
        }
        default: {
            printf("Undefined reading error\n");
            return 666;
        }
    }
    fclose(in);

    struct image * rotated_img = rotate(img);
    free_bmp(img);

    FILE *out = fopen(output_path, "wb");
    if (!out) {
        printf("File '%s' open error\n", output_path);
        return 1;
    }

    uint8_t status_w = to_bmp(out,rotated_img);
    fclose(out);
    free_bmp(rotated_img);
     switch (status_w){
        case WRITE_OK: {
            printf("Image is saved in file '%s'\n", output_path);
            break;
        }
        case WRITE_ERROR:{
            printf("File write error\n");
            return 1;
        }
        default: {
            printf("Undefined writing error\n");
            return 666;
        }
    }
    printf("Memory freed\n");
    return 0;
}
