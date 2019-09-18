#include "title.hpp"

#include "../main/game.hpp"
#include "../main/controller.hpp"

TETRIS::Title::Title(Controller* controller):
    Actor(controller),
    mFirstRectangle(nullptr),
    mIsExecAnimation(true)
{
    loadComponents();
}

void TETRIS::Title::updateActor(float deltaTime)
{
    startAnimation(deltaTime);
}

void TETRIS::Title::startAnimation(float deltaTime)
{
    if(!mIsExecAnimation)
        return;

    if(mFirstRectangle)
    {
        float distance = Game::SCREEN_WIDTH * deltaTime;
        Vector2 size(mFirstRectangle->getSize().x - distance,
                     Game::SCREEN_HEIGHT);
        mFirstRectangle->setSize(size);
        if(size.x <= 0)
        {
            removeComponent(mFirstRectangle);
            mFirstRectangle = nullptr;
        }
    }

}

void TETRIS::Title::loadComponents()
{
    // 背景の設定
    std::string backgroundPass("image/tetris/title_background.png");
    TextureComponent* texture = new TextureComponent(this,
                                                     backgroundPass,
                                                     10);
    texture->setSize(Vector2(Game::SCREEN_WIDTH,
                             Game::SCREEN_HEIGHT));
    texture->setClear(0.75f);
    
    // mFirstRectangle の設定
    SDL_Color yellow = {255, 255, 0, 255};
    mFirstRectangle = new RectangleComponent(this,
                                             texture->getSize(),
                                             yellow);
}