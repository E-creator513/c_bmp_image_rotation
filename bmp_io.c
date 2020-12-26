#include "bmp_io.h"
#include "bmp_struct.h"
#include <stdlib.h>
#include <stdio.h>

struct bmp_header * generate_header (struct image const *img) {

    struct bmp_header *header = (struct bmp_header *) malloc(sizeof(struct bmp_header));

    header->bfType = 0x4D42;
    header->bfileSize = img->width * img->height * sizeof(struct pixel) + img->height * (img->width % 4) + sizeof(struct bmp_header);
    header->bfReserved = 0;
    header->bOffBits = sizeof(struct bmp_header);
    header->biSize = 40;
    header->biWidth = img->width;
    header->biHeight = img->height;
    header->biPlanes = 1;
    header->biBitCount = 24;
    header->biCompression = 0;
    header->biSizeImage = header->bfileSize - header->bOffBits;
    header->biXPelsPerMeter = 0;
    header->biYPelsPerMeter = 0;
    header->biClrUsed = 0;
    header->biClrImportant = 0;
    return header;
}

enum read_status from_bmp( FILE* in, struct image* img){
// need to add errors check
    struct bmp_header header;
    fread(&header, 1, sizeof(header), in);

    uint8_t *data = (uint8_t *) malloc(header.biSizeImage);
    fseek(in, header.bOffBits, SEEK_SET);
    fread(data, 1, header.biSizeImage, in);

    img->data = (struct pixel *) malloc(header.biHeight * header.biWidth * sizeof(struct pixel));
    img->height = header.biHeight;
    img->width = header.biWidth;
    int padding = header.biWidth % 4;

    for (size_t row = 0; row < header.biHeight; row++) {
        for (size_t col = 0; col < header.biWidth; col++) {
            size_t i_pixel = row * img->width + col;
            img->data[row * header.biWidth + col] = *(struct pixel *) ((data) + sizeof(struct pixel) * (row * header.biWidth + col) + padding * row);
        }
    }
    return READ_OK;
}

enum write_status to_bmp( FILE* out, struct image const* img ){
    // need to add errors check
    
    struct bmp_header *header = generate_header(img);
    uint64_t padding = img->width % 4;
    uint64_t data_size = (img->width + (padding)) * img->height * sizeof(struct pixel);
    uint8_t *data = (uint8_t *) calloc(1, data_size);
    for (size_t row = 0; row < img->height; row++) {
        for (size_t col = 0; col < img->width; col++) {
            size_t pixel_i = row * img->width + col;
            *((struct pixel *) (data + sizeof(struct pixel) * pixel_i + row * padding)) = img->data[pixel_i];
        }
    }

    fwrite(header, 1, sizeof(struct bmp_header), out);
    fwrite(data, 1, (img->width + padding) * img->height * sizeof(struct pixel), out);
    return WRITE_OK;
}