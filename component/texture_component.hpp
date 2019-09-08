#pragma once

#include "sprite_component.hpp"

class TextureComponent : public Component
{
public:
    TextureComponent(class Actor* actor,
                     class Renderer* renderer,
                     int drawOrder = 100);
    virtual ~TextureComponent(){}

    void draw() override;

private:
    class Texture* mTexture; // Texture
};