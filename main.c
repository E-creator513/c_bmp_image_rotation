#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bmp_io.h"
#include "bmp_struct.h"
#include "bmp_rotation.h"

#define STANDART_OUT_FILE "output.bmp"

int main(int argc, char *argv[]) {
    if (argc <2) {
        printf("Use arguments: input_file [output file]\n");
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
    
     switch (from_bmp(in,img)) {
        case READ_OK: {
            printf("File '%s' is loaded\n",input_path);
            break;
        }
        case READ_INVALID_PATH: {
            printf("Input file path not found\n");
            return 1;
        }
        default: {
            printf("Undefined reading error\n");
            return 666;
        }
    }
    fclose(in);

    struct image * rotated_img = rotate(img);

    FILE *out = fopen(output_path, "wb");
     switch (to_bmp(out,rotated_img)){
        case WRITE_OK: {
            printf("Image is saved in file '%s'\n", output_path);
            break;
        }
        default: {
            printf("Undefined reading error\n");
            return 666;
        }
    }
    fclose(out);
    free_bmp(img);
    free_bmp(rotated_img);
    printf("Memory freed\n");
    return 0;
}
