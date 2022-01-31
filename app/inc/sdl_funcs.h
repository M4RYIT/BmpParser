#pragma once

int sdl_open_file(const char *file_name, unsigned char **file_data);

int sdl_bmp_to_static_texture(const unsigned char *file_data, unsigned char **pixels, int *w, int *h, int *ch, SDL_Renderer *rnd, SDL_Texture **tex);

int sdl_bmp_to_static_texture_pitch(const unsigned char *file_data, unsigned char **pixels, int *w, int *h, int *ch, SDL_Renderer *rnd, SDL_Texture **tex);

int sdl_bmp_to_streaming_texture(const unsigned char *file_data, unsigned char **pixels, int *w, int *h, int *ch, SDL_Renderer *rnd, SDL_Texture **tex);

int sdl_bmp_to_streaming_texture_pitch(const unsigned char *file_data, unsigned char **pixels, int *w, int *h, int *ch, SDL_Renderer *rnd, SDL_Texture **tex);

void sdl_clear_pixels(unsigned char *pixels);