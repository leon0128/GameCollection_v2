#pragma once

#include "../main/actor.hpp"
#include "../component/gamepad_component.hpp"
#include "../component/texture_component.hpp"
#include "../component/rectangle_component.hpp"
#include "loader.hpp"

namespace TETRIS
{

class Tetris : public Actor
{
public:
    Tetris(class Controller* controller);
    ~Tetris(){}

    // 画面切り替え
    void conversion();
    
    // 引数の値に対応する値を取得
    unsigned int gamepad(GamepadComponent::EGamepad button) const {return mGamepad->at(button);}

private:
    void loadComponents();

    Loader* mLoader; // ロードを処理するクラス
    GamepadComponent* mGamepad; // テトリス全体で使用するゲームパッド
};

};