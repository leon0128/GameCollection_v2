#include "tetris.hpp"

#include "../main/game.hpp"
#include "../main/controller.hpp"
#include "title.hpp"

TETRIS::Tetris::Tetris(Controller* controller):
    Actor(controller),
    mLoader(nullptr),
    mGamepad(nullptr)
{
    new Title(this);
}

void TETRIS::Tetris::conversion()
{
    if(!mLoader->isExecFadeIn() && 
       !mLoader->isExecFadeOut())
        mLoader->execute();
}

void TETRIS::Tetris::loadComponents()
{
    // mGamepad の作成
    mGamepad = new GamepadComponent(this);
    mGamepad->addKeyboardMap(GamepadComponent::BUTTON_START,
                             SDL_SCANCODE_SPACE);

    // mLoader の設定
    mLoader = new Loader(this);
}