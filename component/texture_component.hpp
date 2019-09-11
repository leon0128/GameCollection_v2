#pragma once

#include "sprite_component.hpp"
#include <string>

class TextureComponent : public SpriteComponent
{
public:
    TextureComponent(class Actor* actor,
                     std::string& filename,
                     int drawOrder = 100);
    ~TextureComponent(){}

    void draw() override;

    void setTexture(std::string& filename);

private:
    class Texture* mTexture; // Texture
};