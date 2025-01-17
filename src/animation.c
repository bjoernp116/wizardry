#include "sprite.h"
#include "macros.h"

typedef struct {
    Sprite* sprite;
    f64 frame_duration;
    u32 row;
    f64 accumulator;
} Animation;

Animation create_animation(Sprite* sprite, u32 row, f32 frame_duration) {
    Animation animation;
    animation.sprite = sprite;
    animation.sprite->frame = row * sprite->hframes;

    animation.row = row;

    animation.frame_duration = frame_duration;
    animation.accumulator = 0.0f;
    return animation;
}

void step_animation(Animation* animation, f64 delta) {
    animation->accumulator += delta;
    if (animation->accumulator >= animation->frame_duration) {
        animation->accumulator -= animation->frame_duration;
        u32 y = animation->row * animation->sprite->hframes;
        animation->sprite->frame = y + (animation->sprite->frame + 1) % animation->sprite->hframes;
    }
}
