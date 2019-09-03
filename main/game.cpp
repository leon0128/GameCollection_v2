#include "game.hpp"

Game::Game():
    mInputSystem(nullptr),
    mRenderer(nullptr),
    mIsLoop(true)
{
}

bool Game::initialize()
{
    // SDL の初期化
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        SDL_Log("Failed to initialize SDL: %s",
                SDL_GetError());
        return false;
    }

    // mInputSystem の設定
    mInputSystem = new InputSystem(this);
    if(!mInputSystem->initialize())
    {
        SDL_Log("Failed to initialize InputSystem");
        return false;
    }

    // mRenderer の設定
    mRenderer = new Renderer(this);
    if(!mRenderer->initialize())
    {
        SDL_Log("Failed to initialize Renderer");
        return false;
    }

    return true;
}

void Game::runLoop()
{
    while(mIsLoop)
    {
        input();
        update();
        output();
    }
}

void Game::finalize()
{
    // mRenderer の削除
    mRenderer->finalize();
    delete mRenderer;

    // mInputSystem の削除
    delete mInputSystem;

    SDL_Quit();
}

void Game::input()
{
    mInputSystem->input();
}

void Game::update()
{

}

void Game::output()
{
    mRenderer->draw();
}