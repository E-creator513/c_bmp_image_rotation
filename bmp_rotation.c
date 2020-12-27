#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "bmp_rotation.h"
#include "bmp_io.h"


struct image *rotate(struct image const * img) {
    struct image *img_rotate = malloc_bmp();
    img_rotate->height = img->width;
    img_rotate->width = img->height;
    
    img_rotate->data = (struct pixel *) malloc(img->height * img->width * sizeof(struct pixel));

    for (size_t row = 0; row < img->height; row++) {
        for (size_t col = 0; col < img->width; col++) {
            img_rotate->data[row+((img_rotate->height-col-1) * img_rotate->width)] = img->data[col+row * img->width];
        }
    }
    return img_rotate;
}