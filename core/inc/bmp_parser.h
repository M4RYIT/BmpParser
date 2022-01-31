#pragma once

static const int bmp_channels = 3;
static const int bmp_alignment = 4;

void load_bmp(const unsigned char *file_data, unsigned char *pixels, int *w, int *h, int *channels);

void load_bmp_pitch(const unsigned char *file_data, unsigned char *pixels, int *w, int *h, int *channels, int *pitch);

const unsigned char *bmp_start_point(const unsigned char *file_data);

void bmp_dim(const unsigned char *file_data, int *w, int *h);

int bmp_padded_row(const int row_size);