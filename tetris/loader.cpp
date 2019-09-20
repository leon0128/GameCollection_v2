#include "loader.hpp"
#include "../main/game.hpp"
#include "../main/controller.hpp"
#include "tetris.hpp"

TETRIS::Loader::Loader(Tetris* owner):
    Actor(owner->getController()),
    mDirectionRects(),
    mOwner(owner),
    mBGRectangle(nullptr),
    mIsExecFadeOut(false),
    mIsExecFadeIn(false)
{
}

void TETRIS::Loader::updateActor(float deltaTime)
{
    if(mIsExecFadeOut)
        fadeOut(deltaTime);
    if(mIsExecFadeIn)
        fadeIn(deltaTime);
}

void TETRIS::Loader::fadeOut(float deltaTime)
{
    SDL_Color white = {255, 255, 255, 255};
    mBGRectangle = new RectangleComponent(this,
                                          Vector2(Game::SCREEN_WIDTH,
                                                  Game::SCREEN_HEIGHT),
                                          white,
                                          1000);
}

void TETRIS::Loader::fadeIn(float deltaTime)
{

}