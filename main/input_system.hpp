#pragma once

#include <SDL2/SDL.h>
#include <vector>

class InputSystem
{
public:
    InputSystem(class Game* game);
    ~InputSystem(){}

    // Game::initialize() で呼び出す
    bool initialize();

    // Game::input() で呼び出す
    void input();

    // キーボードの状態の取得
    const auto& getKeyboardState() const {return mKeyboardState;}
    unsigned int getKeyboardState(SDL_Scancode scancode) const {return mKeyboardState.at(scancode);}

private:
    // mKeyboardState の状態を更新する
    void updateKeyboardState();

    std::vector<unsigned int> mKeyboardState; // キーボードの状態

    class Game* mGame; // 所属するGameクラス
};