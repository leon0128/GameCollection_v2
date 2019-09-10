#pragma once

#include "sprite_component.hpp"
#include "../main/mathematics.hpp"
#include <SDL2/SDL.h>

class RectangleComponent : public SpriteComponent
{
public:
    RectangleComponent(class Actor* actor,
                       Vector2& size,
                       SDL_Color& color,
                       int drawOrder = 100);
    ~RectangleComponent(){}

    void draw() override;

private:
    SDL_Color mColor; // 矩形を満たす色
};