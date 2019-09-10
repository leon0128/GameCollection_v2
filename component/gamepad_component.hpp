#pragma once

#include "component.hpp"
#include <SDL2/SDL.h>
#include <unordered_map>
#include <vector>
#include <algorithm>

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

    void update(float deltaTime) override;

    // EGamepad に対応する SDL_Scancode の追加
    void addKeyboardMap(EGamepad button,
                        SDL_Scancode scancode);

    // mGamepadの要素の取得
    unsigned int at(EGamepad button) const {return mGamepad.at(button);}

private:
    // mGamepad と mKeyboardMap にキーの設定
    void loadKey();

    std::unordered_map<EGamepad, unsigned int> mGamepad;                  // ゲームパッド
    std::unordered_map<EGamepad, std::vector<SDL_Scancode>> mKeyboardMap; // EGamepad と SDL_Scancode の対応表

    class InputSystem* mInputSystem; // 入力処理クラス
};