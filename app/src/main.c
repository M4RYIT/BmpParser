#include <SDL.h>
#include "sdl_funcs.h"

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("BMP Parser", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 512, 0);
    if (!window) goto quit;

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) goto quit;

    char *file_name = "assets\\img.bmp";
    unsigned char *file_data;

    if (!sdl_open_file(file_name, &file_data)) goto quit;

    int w, h, channels;
    SDL_Texture *static_texture;
    SDL_Texture *streaming_texture;
    SDL_Texture *static_texture_pitch;
    SDL_Texture *streaming_texture_pitch;
    unsigned char *pixels;

    if (!sdl_bmp_to_static_texture(file_data, &pixels, &w, &h, &channels, renderer, &static_texture)) goto quit;

    if (!sdl_bmp_to_streaming_texture(file_data, &pixels, &w, &h, &channels, renderer, &streaming_texture)) goto quit;

    if (!sdl_bmp_to_static_texture_pitch(file_data, &pixels, &w, &h, &channels, renderer, &static_texture_pitch)) goto quit;

    if (!sdl_bmp_to_streaming_texture_pitch(file_data, &pixels, &w, &h, &channels, renderer, &streaming_texture_pitch)) goto quit;

    int offset_x = 114;
    int offset_y = 115;
    SDL_Rect rect = {offset_x, 0, w, h};

    for (;;)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) goto quit;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        rect.y = offset_y;
        SDL_RenderCopy(renderer, static_texture, NULL, &rect);

        rect.x += w + offset_x;
        SDL_RenderCopy(renderer, streaming_texture, NULL, &rect);

        rect.y += h + offset_y;
        SDL_RenderCopy(renderer, streaming_texture_pitch, NULL, &rect);

        rect.x = offset_x;
        SDL_RenderCopy(renderer, static_texture_pitch, NULL, &rect);

        SDL_RenderPresent(renderer);
    }

quit:
    if (window) SDL_DestroyWindow(window);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (file_data) free(file_data);
    SDL_Quit();
    return 0;
}