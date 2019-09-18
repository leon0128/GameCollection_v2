#pragma once

#include "sprite_component.hpp"
#include "../main/mathematics.hpp"
#include <SDL2/SDL.h>

class RectangleComponent : public SpriteComponent
{
public:
    RectangleComponent(class Actor* actor,
                       const Vector2& size,
                       const SDL_Color& color,
                       int drawOrder = 100);

    void draw() override;

    void setColor(const SDL_Color& color){mColor = color;}

private:
    SDL_Color mColor; // 矩形を満たす色
};