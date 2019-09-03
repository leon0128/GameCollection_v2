#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>

class Renderer
{
public:
    Renderer(class Game* game);
    ~Renderer(){}

    // Game::initialize() finalize() で呼び出す
    bool initialize();
    void finalize();

    // Game::output() で呼び出す
    void draw();

private:
    class Game* mGame;      // 所属するGame クラス
    SDL_Window* mWindow;    // ウィンドウ
    SDL_GLContext mContext; // コンテキスト
};