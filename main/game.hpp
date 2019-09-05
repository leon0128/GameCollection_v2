#pragma once

#include <SDL2/SDL.h>

class Game
{
public:
    // 定数
    const float SCREEN_WIDTH = 1024.0f;  // 幅
    const float SCREEN_HEIGHT = 768.0f; // 高さ

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

    // 各機能
    class InputSystem* mInputSystem; // 入力関連を処理するクラス
    class Controller* mController;   // ゲーム内オブジェクトを処理するクラス
    class Renderer* mRenderer;       // 描画関連を処理するクラス

    // フラグ
    bool mIsLoop; // ゲームを続けるか
};