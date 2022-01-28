#include <string.h>
#include "bmp_parser.h"

void load_bmp(const unsigned char *file_data, unsigned char *pixels, int *w, int *h, int *channels)
{
    if (!pixels)
    {
        bmp_dim(file_data, w, h);
        *channels = bmp_channels;
        return;
    }

    int row_size = (*w)*(*channels);
    int padded_row_size = bmp_padded_row(row_size);
    const unsigned char *head = bmp_start_point(file_data);

    for (int y=0; y<(*h); y++)
    {
        memcpy(pixels+((*h)-y-1)*row_size,
               head+y*padded_row_size, 
               row_size);
    }
}

const unsigned char *bmp_start_point(const unsigned char *file_data)
{
    int *offset = (int*)(file_data+10);
    return file_data + *offset;
}

void bmp_dim(const unsigned char *file_data, int *w, int *h)
{
    memcpy(w, file_data+18, 4);
    memcpy(h, file_data+22, 4);
}

int bmp_padded_row(const int row_size)
{
    int padded_row_size = (row_size / bmp_alignment) * bmp_alignment;
    if (row_size % bmp_alignment) padded_row_size += bmp_alignment;
    return padded_row_size;
}