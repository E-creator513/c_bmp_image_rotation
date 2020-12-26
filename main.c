#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bmp_io.h"
#include "bmp_struct.h"
#include "bmp_rotation.h"

#define STANDART_OUT_FILE "output.bmp"

int main(int argc, char *argv[]) {
    // need to add errors check
    // readimg img
    struct image *img = (struct image *) malloc(sizeof(struct image));
    FILE *in = fopen("examples/in.bmp", "rb");
    from_bmp(in,img);
    fclose(in);
    // rotate
    struct image * rotated_img = rotate(img);
    // writing img
    FILE *out = fopen("examples/"STANDART_OUT_FILE, "wb");
    to_bmp(out,rotated_img);
    fclose(out);
return 0;
}
