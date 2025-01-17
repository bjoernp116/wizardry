#include "sprite.h"
#include "macros.h"

typedef struct {
    Sprite* sprite;
    u32* framelist;
    f64 frame_duration;

    f64 accumulator;
} Animation;

Animation create_animation(Sprite* sprite, u32* framelist, f32 frame_duration) {
    Animation animation;
    animation.sprite = sprite;
    animation.framelist = framelist;
    animation.frame_duration = frame_duration;
    animation.accumulator = 0.0f;
    return animation;
}

void step_animation(Animation* animation, f64 delta) {
    animation->accumulator += delta;
    if (animation->accumulator >= animation->frame_duration) {
        animation->accumulator -= animation->frame_duration;

        increment_frame(animation->sprite);
    }
}
