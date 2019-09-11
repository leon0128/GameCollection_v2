#pragma once

#include "sprite_component.hpp"
#include "../main/font.hpp"
#include <string>
#include <vector>

class StringComponent : public SpriteComponent
{
public:
    StringComponent(class Actor* actor,
                    const std::string& string,
                    Font::ESize size = Font::SIZE_30,
                    int drawOrder = 100);
    ~StringComponent(){}

    void draw() override;

    void setString(const std::string& string);

private:
    std::vector<class Texture*> mStringTexture; // 描画する文字列 Texture
    
    Font::ESize mFontSize; // フォントの大きさ
};