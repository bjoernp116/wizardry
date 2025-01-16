#include <SDL2/SDL_error.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <stdlib.h>
#include "macros.h"
#include "char_map.h"


typedef struct {
    u32 char_height;
    u32 char_width;

    u32 char_spacing;
    u32 line_spacing;

    u32 color;

    SDL_PixelFormat* pixel_format;
    SDL_Texture* char_sheet;
} Font;

Font load_font(SDL_Renderer* renderer, char* path, u32 h, u32 w){
    SDL_Surface* surface = SDL_LoadBMP(path);
    ASSERT(surface, "Cant create surface from BMP: %s\n", SDL_GetError());
    SDL_Texture* texture = SDL_CreateTexture(renderer, surface->format->format, SDL_TEXTUREACCESS_STREAMING, surface->w, surface->h);
    ASSERT(texture, "Cant create texture from surface: %s\n", SDL_GetError());

    ASSERT(SDL_UpdateTexture(texture, NULL, surface->pixels, surface->pitch) == 0, "Failed to update texture: %s\n", SDL_GetError());


    Font font;
    font.char_sheet = texture;
    font.char_height = h;
    font.char_width = w;
    font.pixel_format = surface->format;

    font.char_spacing = 0;
    font.line_spacing = 0;
    return font;
}

void set_color (Font* font, u8 r, u8 g, u8 b, u8 a) {
    font->color = SDL_MapRGBA(font->pixel_format, r, g, b, a);
}

void recolor_font(Font* font){
    u32* pixels = NULL;
    int pitch = 0;
    int w, h;
    SDL_QueryTexture(font->char_sheet, NULL, NULL, &w, &h);

    if (SDL_LockTexture(font->char_sheet, NULL, (void**)&pixels, &pitch)) {
        ASSERT(0, "Font Texture is locked! %s\n", SDL_GetError());
    }
    ASSERT(&font->pixel_format, "Pixelformat unitialized!\n");
    for (int i = 0; i < h * w; i++) {
        u8 alpha = 0;
        SDL_GetRGBA(pixels[i], font->pixel_format, NULL, NULL, NULL, &alpha);
        if (alpha != 0) {
            pixels[i] = font->color;
        }
    }
}


void render_char(SDL_Renderer* renderer, Font font, u32 x, u32 y, unsigned char c, f32 font_size) {
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = font.char_width * font_size;
    dest.h = font.char_height * font_size;

    u32 index = char_to_index(c);

    SDL_Rect src;
    src.x = (index % font.char_width) * font.char_width;
    src.y = (index / font.char_width) * font.char_height;
    src.w = font.char_width;
    src.h = font.char_height;

    SDL_RenderCopy(renderer, font.char_sheet, &src, &dest);
}

void render_string(SDL_Renderer* renderer, Font font, u32 x, u32 y, char* s, f32 font_size) {
    char* t;
    int i = 0;
    u32 ax = x;
    u32 ay = y;
    for(t = s; *t != '\0'; t++) {
        if (*t == '\n') {
            ax = x;
            ay += font.char_height * font_size + font.line_spacing;
            continue;
        }
        render_char(
                renderer,
                font,
                ax,
                ay, // + (i * font.char_height),
                *t,
                font_size
                );
        i++;
        ax += font.char_width * font_size + font.char_spacing;
    }
}



