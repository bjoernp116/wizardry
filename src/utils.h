#ifndef UTILS_H
#define UTILS_H

#include "macros.h"

typedef struct {
    u32 x;
    u32 y;
} uv2;


typedef struct {
    f32 x;
    f32 y;
} fv2;

typedef struct {
    i32 x;
    i32 y;
} iv2;

uv2 UV2(u32 x, u32 y) { return { x, y }; }
fv2 FV2(f32 x, f32 y) { return { x, y }; }
iv2 IV2(i32 x, i32 y) { return { x, y }; }

#define ADD(a, b) { a.x + b.x, a.y + b.y }
#define SUB(a, b) { a.x - b.x, a.y - b.y }
#define MUL(a, b) { a.x * b.x, a.y * b.y }
#define DIV(a, b) { a.x / b.x, a.y / b.y }

#endif // !UTILS_H
