#include <SDL.h>
#include <string.h>
#include "sdl_funcs.h"
#include "bmp_parser.h"

int sdl_open_file(const char *file_name, unsigned char **file_data)
{
    SDL_RWops *file = SDL_RWFromFile(file_name, "rb");
    if (!file) return 0;

    long long file_size = SDL_RWsize(file);

    *file_data = malloc(file_size);
    if (!*file_data)
    {
        SDL_RWclose(file);
        return 0;
    }

    SDL_RWread(file, *file_data, file_size, 1);
    SDL_RWclose(file);
    return 1;
}

int sdl_bmp_to_static_texture(const unsigned char *file_data, unsigned char **pixels, int *w, int *h, int *ch, SDL_Renderer *rnd, SDL_Texture **tex)
{
    load_bmp(file_data, NULL, w, h, ch);

    *pixels = malloc((*w)*(*h)*(*ch));
    if (!*pixels) return 0;

    *tex = SDL_CreateTexture(rnd, SDL_PIXELFORMAT_BGR24, SDL_TEXTUREACCESS_STATIC, *w, *h);

    load_bmp(file_data, *pixels, w, h, ch);    

    SDL_UpdateTexture(*tex, NULL, *pixels, (*w)*(*ch));
    free(*pixels);

    return 1;
}

int sdl_bmp_to_static_texture_pitch(const unsigned char *file_data, unsigned char **pixels, int *w, int *h, int *ch, SDL_Renderer *rnd, SDL_Texture **tex)
{
    load_bmp_pitch(file_data, NULL, w, h, ch, NULL);

    *pixels = malloc((*w)*(*h)*(*ch));
    if (!*pixels) return 0;

    *tex = SDL_CreateTexture(rnd, SDL_PIXELFORMAT_BGR24, SDL_TEXTUREACCESS_STATIC, *w, *h);

    load_bmp_pitch(file_data, *pixels, w, h, ch, NULL);

    SDL_UpdateTexture(*tex, NULL, *pixels, (*w)*(*ch));
    free(*pixels);

    return 1;
}

int sdl_bmp_to_streaming_texture_pitch(const unsigned char *file_data, unsigned char **pixels, int *w, int *h, int *ch, SDL_Renderer *rnd, SDL_Texture **tex)
{
    load_bmp_pitch(file_data, NULL, w, h, ch, NULL);

    *tex = SDL_CreateTexture(rnd, SDL_PIXELFORMAT_BGR24, SDL_TEXTUREACCESS_STREAMING, *w, *h);

    int pitch;
    SDL_LockTexture(*tex, NULL, (void**)pixels, &pitch);

    load_bmp_pitch(file_data, *pixels, w, h, ch, &pitch);

    SDL_UnlockTexture(*tex);

    return 1;
}

int sdl_bmp_to_streaming_texture(const unsigned char *file_data, unsigned char **pixels, int *w, int *h, int *ch, SDL_Renderer *rnd, SDL_Texture **tex)
{
    load_bmp(file_data, NULL, w, h, ch);

    unsigned char *temp_pixels = malloc((*w)*(*h)*(*ch));
    if (!temp_pixels) return 0;

    load_bmp(file_data, temp_pixels, w, h, ch);

    *tex = SDL_CreateTexture(rnd, SDL_PIXELFORMAT_BGR24, SDL_TEXTUREACCESS_STREAMING, *w, *h);
    
    int pitch;    
    SDL_LockTexture(*tex, NULL, (void**)pixels, &pitch);

    int row_size = (*w)*(*ch);
    for (int y=0; y<(*h); y++)
    {
        memcpy((*pixels)+y*pitch, 
                    temp_pixels+y*row_size,
                    row_size);
    }

    SDL_UnlockTexture(*tex);
    free(temp_pixels);

    return 1;
}