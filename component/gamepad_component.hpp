#pragma once

#include "component.hpp"
#include <unordered_map>

class GamepadComponent : public Component
{
public:
    // ゲームパッドのボタンの列挙体
    enum EGamepad
    {
        BUTTON_UP,
        BUTTON_DOWN,
        BUTTON_LEFT,
        BUTTON_RIGHT,
        
        BUTTON_A,
        BUTTON_B,
        BUTTON_X,
        BUTTON_Y,
        
        BUTTON_R,
        BUTTON_L,
        
        BUTTON_SELECT,
        BUTTON_START,
        BUTTON_HOME
    };

    GamepadComponent(class Actor* actor,
                     int order = 10);
    ~GamepadComponent(){}

    // mGamepadの要素の取得
    unsigned int at(EGamepad button) const {return mGamepad.at(button);}

private:
    // mGamepad にキーの設定
    void loadKey();

    std::unordered_map<EGamepad, unsigned int> mGamepad; // ゲームパッド
};