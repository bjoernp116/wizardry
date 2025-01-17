#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
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
#include "sprite.h"
#include "animation.c"
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

    Font font = load_font(state.renderer, "font.bmp", 8, 8);
    font.line_spacing = 10;
    set_color(&font, 255, 0, 0, 255);
    //recolor_font(&font);

    Sprite sprite = create_sprite(state.renderer, "troll.bmp", 3, 4);
    sprite.pos_x = 10;
    sprite.pos_y = 10;
    u32 framelist[5] = { 0, 1, 2, 3, 4 };
    Animation animation = create_animation(&sprite, &framelist[0], 500);



    u32 NOW = SDL_GetPerformanceCounter();
    u32 LAST;
    f64 delta;
    while (!state.quit) {
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        delta = (double)((NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency());

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    state.quit = true;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym){
                        case SDLK_ESCAPE:
                            state.quit = true;
                    }
            }
        }

        state.pixels[10] = 0xFF0000FF;
        SDL_UpdateTexture(state.texture, NULL, state.pixels, SCREEN_WIDTH * 4);
        SDL_RenderClear(state.renderer);

        SDL_RenderCopyEx(
                state.renderer,
                state.texture,
                NULL,
                NULL,
                0.0,
                NULL, SDL_FLIP_VERTICAL);
        //render_string(state.renderer, &font, 10, 10,
        //        (unsigned char*)"THE QUICK BROWN FOX \nÆØÅ JUMPES OVER THE \nLAZY DOG!", 3);

        debug_sprite(sprite);
        step_animation(&animation, delta);
        render_sprite(state.renderer, &sprite);


        SDL_RenderPresent(state.renderer);
    }

    free_font(&font);
    free_sprite(&sprite);


    return 2;
}

