#pragma once

#include <SDL2/SDL.h>

class Game
{
public:
    // 定数
    static const float SCREEN_WIDTH;  // 幅
    static const float SCREEN_HEIGHT; // 高さ
    static const float FRAME_RATE;    // フレームレート

    Game();
    ~Game(){}

    // main で呼び出す
    bool initialize();
    void runLoop();
    void finalize();

    // Game 終了時に呼び出す
    void end(){mIsLoop = false;}

    // Controller で使用する(修正予定)
    class Renderer* getRenderer() const {return mRenderer;}
    class InputSystem* getInputSystem() const {return mInputSystem;}

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