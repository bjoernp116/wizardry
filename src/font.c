#include <SDL2/SDL_error.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <stdio.h>
#include "macros.h"

#define MAP_SIZE_X 64
#define MAP_SIZE_Y 64

#define FONT_SIZE_X 8
#define FONT_SIZE_Y 8

typedef struct {
    u32 pixels[MAP_SIZE_X * MAP_SIZE_Y];
    SDL_Texture* map[FONT_SIZE_X * FONT_SIZE_Y];
} Font;

u32 get_pixel(const SDL_Surface* surface, const u8 x, const u8 y) {
    const u8 bpp = surface->format->BytesPerPixel;

    u8* pixel = (u8*) surface->pixels + y * surface->pitch + x * bpp;
    u32 pixel_data = *(u32*) pixel;

    SDL_Color color = { 0x00, 0x00, 0x00, 0x00 };
    SDL_GetRGBA(pixel_data, surface->format, &color.r, &color.g, &color.b, &color.a);
    u32 out = (color.r << 8*3) + (color.g << 8*2) + (color.b << 8) + color.a;

    return out;
}

Font load_font(char* path) {
    Font font;

    printf("Loading Font!\n");

    SDL_Surface* bmp = SDL_LoadBMP(path);
    ASSERT(bmp, "Cant load font!\n%s", SDL_GetError());

    for(u32 x = 0; x < MAP_SIZE_X; x++) {
        for(u32 y = 0; y < MAP_SIZE_Y; y++) {
            //printf("(%d, %d)\n", x, y);
            u32 pixel = get_pixel(bmp, x, y);
            font.pixels[y * MAP_SIZE_X + x] = pixel;
        }
    }

    for(int i = 0; i < MAP_SIZE_X * MAP_SIZE_Y; i++) {
        printf("PXL: %u\n", font.pixels[i]);
    }

    printf("done\n");
    return font;
}

void split_font(Font* font, SDL_Renderer* renderer){
    for(int i = 0; i < 64; i++) {
        u32 xc = i % FONT_SIZE_X;
        u32 yc = i / FONT_SIZE_X;

        u32 pixels[64];

        for(int x = 0; x < 8; x++) {
            for(int y = 0; y < 8; y++) {
                pixels[y * 8 + x] = font->pixels[(y + FONT_SIZE_Y * yc) * FONT_SIZE_X + (x + FONT_SIZE_X * xc)];
            }
        }
        SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 8, 8);
        SDL_UpdateTexture(texture, NULL, pixels, 0);
        font->map[i] = texture;

    }
}

void render_char(Font font, SDL_Renderer* renderer, u32 index, u32 x, u32 y){
    SDL_Rect texture_rect;
    texture_rect.x = x;
    texture_rect.y = y;
    texture_rect.h = 8;
    texture_rect.w = 8;

    SDL_RenderCopy(renderer, font.map[index], NULL, &texture_rect);
}
