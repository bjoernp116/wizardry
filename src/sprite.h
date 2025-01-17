#ifndef SPRITE_H
#define SPRITE_H


#include <SDL2/SDL_error.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <stdio.h>
#include "macros.h"


typedef struct {
    SDL_Texture* texture;

    u32 frame;

    u32 hframes;
    u32 vframes;

    u32 frame_width;
    u32 frame_height;

    u32 sprite_width;
    u32 sprite_height;

    u32 pos_x;
    u32 pos_y;

    u32 scale;
} Sprite;

Sprite create_sprite(SDL_Renderer* renderer, char* path, u32 hframes, u32 vframes) {
    Sprite sprite;
    SDL_Surface* surface = SDL_LoadBMP(path);
    SDL_Texture* texture = SDL_CreateTexture(renderer, surface->format->format, SDL_TEXTUREACCESS_STREAMING, surface->w, surface->h);

    ASSERT(SDL_UpdateTexture(texture, NULL, surface->pixels, surface->pitch) == 0, "Texture couldnt be loaded from surface! %s\n", SDL_GetError());

    sprite.texture = texture;
    sprite.hframes = hframes;
    sprite.vframes = vframes;
    sprite.frame = 0;

    sprite.sprite_width = surface->w;
    sprite.sprite_height = surface->h;

    sprite.scale = 1;
    sprite.pos_x = 0;
    sprite.pos_y = 0;

    sprite.frame_width = sprite.sprite_width / hframes;
    sprite.frame_height = sprite.sprite_height / vframes;

    SDL_FreeSurface(surface);
    return sprite;
}

void render_sprite(SDL_Renderer* renderer, Sprite* sprite) {
    SDL_Rect src;
    src.h = sprite->frame_height;
    src.w = sprite->frame_width;
    src.y = sprite->frame_height * (sprite->frame / sprite->hframes);
    src.x = sprite->frame_width * (sprite->frame % sprite->vframes);
    printf("Frame Coords: (%d, %d)", src.x / sprite->frame_width, src.y / sprite->frame_height);

    SDL_Rect dest;
    dest.h = sprite->frame_height * sprite->scale;
    dest.w = sprite->frame_width * sprite->scale;
    dest.x = sprite->pos_x;
    dest.y = sprite->pos_y;

    SDL_RenderCopy(renderer, sprite->texture, &src, &dest);
}

void increment_frame(Sprite* sprite) {
    sprite->frame = (sprite->frame + 1 ) % (sprite->hframes * sprite->vframes);
}

void free_sprite(Sprite* sprite) {
    SDL_DestroyTexture(sprite->texture);
    sprite->texture = NULL;
    sprite = NULL;
}

void debug_sprite(Sprite sprite) {
    printf("[SPRITE]\n");
    printf("\tFrame: %u\n", sprite.frame);
    printf("\tHFrames: %u\n", sprite.hframes);
    printf("\tVFrames: %u\n", sprite.vframes);
    printf("\tFrame Size: (%u, %u)\n", sprite.frame_width, sprite.frame_height);
    printf("\tSprite Size: (%u, %u)\n", sprite.sprite_width, sprite.sprite_height);
    printf("\tSprite Position: (%u, %u)\n", sprite.pos_x, sprite.pos_y);
    printf("\tSprite Scale: %u\n", sprite.scale);
}

#endif // !SPRITE_H
