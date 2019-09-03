#pragma once

#include <SDL2/SDL.h>

class Game
{
public:
    Game();
    ~Game(){}

    // main で呼び出す
    bool initialize();
    void runLoop();
    void finalize();

    // Game 終了時に呼び出す
    void end(){mIsLoop = false;}

private:
    // runLoop() 内のループに使用
    void input();
    void update();
    void output();

    // フラグ
    bool mIsLoop; // ゲームを続けるか
};