
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include "macros.h"

typedef struct {
    SDL_Texture* tilesheet;
    u32 map_width;
    u32 map_height;
    u32 tile_height;
    u32 tile_width;
} TileMap;

SDL_Rect get_tile_from_sheet(TileMap tm, u32 x, u32 y) {
    SDL_Rect rect;
    rect.w = tm.tile_width;
    rect.h = tm.tile_height;
    rect.x = x * tm.tile_width;
    rect.y = y * tm.tile_height;
    return rect;
}

TileMap create_tilemap(SDL_Renderer* renderer, char* path, u32 map_width, u32 map_height) {
    SDL_Surface* surface = SDL_LoadBMP(path);
    SDL_Texture* texture = SDL_CreateTexture(
            renderer,
            surface->format->format,
            SDL_TEXTUREACCESS_STREAMING,
            surface->w,
            surface->h);
    ASSERT(SDL_UpdateTexture(texture, NULL, surface->pixels, surface->pitch) == 0,
            "Texture cant be made from surface: %s\n", SDL_GetError());

    TileMap tm;
    tm.tilesheet = texture;
    tm.map_width = map_width;
    tm.map_height = map_height;
    tm.tile_width = surface->w / map_width;
    tm.tile_height = surface->h / map_height;

    SDL_FreeSurface(surface);
    return tm;
}

void render_tile(SDL_Renderer* renderer, TileMap* tm, u32 ix, u32 iy, u32 px, u32 py) {
    SDL_Rect dest;
    dest.w = tm->tile_width;
    dest.h = tm->tile_height;
    dest.x = px;
    dest.y = py;

    SDL_Rect src = get_tile_from_sheet(*tm, ix, iy);

    SDL_RenderCopy(renderer, tm->tilesheet, &src, &dest);
}
