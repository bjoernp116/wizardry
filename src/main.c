#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>
#include "macros.h"
#include "font.c"
#include <string.h>
#include <sys/resource.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    u32 pixels[SCREEN_HEIGHT * SCREEN_WIDTH];
    SDL_Texture* texture;
    bool quit;

} state;

int main() {
    printf("starting!\n");
    ASSERT(!SDL_Init(SDL_INIT_VIDEO), "SDL could not initialize %s\n", SDL_GetError());
    state.window = SDL_CreateWindow(
            "Wizardry",
            SDL_WINDOWPOS_CENTERED_DISPLAY(0),
            SDL_WINDOWPOS_CENTERED_DISPLAY(0),
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);
    ASSERT(state.window, "SDL window could not initialize %s\n", SDL_GetError());

    state.renderer = SDL_CreateRenderer(state.window, -1, SDL_RENDERER_PRESENTVSYNC);
    ASSERT(state.renderer, "SDL renderer could not initialize %s\n", SDL_GetError());

    state.texture = SDL_CreateTexture(
            state.renderer,
            SDL_PIXELFORMAT_ABGR8888,
            SDL_TEXTUREACCESS_STREAMING,
            SCREEN_WIDTH,
            SCREEN_HEIGHT);
    ASSERT(state.renderer, "SDL renderer could not initialize %s\n", SDL_GetError());

    Font font = load_font("font.bmp");
    split_font(&font, state.renderer);
    printf("font loaded\n");

    SDL_Surface* image = SDL_LoadBMP("font.bmp");
    SDL_Texture* image_tex = SDL_CreateTextureFromSurface(state.renderer, image);



    while (!state.quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    state.quit = true;
                    break;
            }

        }
        state.pixels[10] = 0xFF0000FF;
        //SDL_UpdateTexture(state.texture, NULL, state.pixels, SCREEN_WIDTH * 4);
        SDL_RenderClear(state.renderer);

        /*SDL_RenderCopyEx(
                state.renderer,
                state.texture,
                NULL,
                NULL,
                0.0,
                NULL, SDL_FLIP_VERTICAL);*/

        SDL_RenderCopy(state.renderer, image_tex, NULL, NULL);

        SDL_RenderPresent(state.renderer);
    }




    printf("Hello, World!\n");
    return 2;
}

