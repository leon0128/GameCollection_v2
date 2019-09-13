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
    void setColor(const SDL_Color& color){mColor = color;}
    void setBackGroundColor(const SDL_Color& color){mBackGroundColor = color;}

private:
    std::vector<class Texture*> mStringTexture; // 描画する文字列 Texture

    SDL_Color mColor;           // 文字列の色
    SDL_Color mBackGroundColor; // 背景色
    Font::ESize mFontSize;      // フォントの大きさ
};