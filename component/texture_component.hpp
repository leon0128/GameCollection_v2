#pragma once

#include "sprite_component.hpp"

class TextureComponent : public SpriteComponent
{
public:
    TextureComponent(class Actor* actor,
                     class Renderer* renderer,
                     int drawOrder = 100);
    virtual ~TextureComponent(){}

    void draw() override;

    void setTexture(class Texture* texture);

private:
    class Texture* mTexture; // Texture
};