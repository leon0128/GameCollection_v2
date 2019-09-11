#pragma once

#include "sprite_component.hpp"
#include <string>

class StringComponent : public SpriteComponent
{
public:
    StringComponent(class Actor* actor,
                    const std::string& string,
                    int drawOrder = 100);
    ~StringComponent(){}

    void draw() override;

    void setString(const std::string& string);

private:
    std::string mString; // 描画する文字列
};