#include "title.hpp"

#include "../main/game.hpp"
#include "../main/controller.hpp"

TETRIS::Title::Title(Controller* controller):
    Actor(controller),
    mElapsedTime(0.0f),
    mFirstRectangle(nullptr),
    mFirstRectPair(std::make_pair(nullptr, nullptr)),
    mSecondRectPair(std::make_pair(nullptr, nullptr)),
    mLogoTexture(nullptr),
    mIsExecRectAnimation(true),
    mIsExecLogoAnimation(true)
{
    loadComponents();
}

void TETRIS::Title::updateActor(float deltaTime)
{
    rectangleAnimation(deltaTime);
    logoAnimation(deltaTime);

    mElapsedTime += deltaTime;
}

void TETRIS::Title::rectangleAnimation(float deltaTime)
{
    if(!mIsExecRectAnimation)
        return;

    // mFirstRectangle のアニメーションが終わるまでは他のアニメーションは実行しない
    if(mFirstRectangle)
    {
        float distance = Game::SCREEN_WIDTH * deltaTime * 1.5f;
        Vector2 size(mFirstRectangle->getSize().x - distance,
                     Game::SCREEN_HEIGHT);
        mFirstRectangle->setSize(size);
        if(size.x <= 0)
        {
            removeComponent(mFirstRectangle);
            mFirstRectangle = nullptr;
        }

        return;
    }

    // アニメーション開始から１秒立つまで待機
    if(mElapsedTime < 1.0f)
        return;

    // mFirstRectPair のアニメーション
    Vector2 firSize(mFirstRectPair.first->getSize());
    firSize.x += Game::SCREEN_WIDTH / 10.0f * deltaTime * 1.5f;    
    mFirstRectPair.first->setSize(firSize);
    mFirstRectPair.second->setSize(firSize);

    Vector2 firPos(mFirstRectPair.first->getPosition());
    firPos.x += Game::SCREEN_WIDTH * deltaTime * 0.8f;
    mFirstRectPair.first->setPosition(firPos);
    firPos.x *= -1;
    mFirstRectPair.second->setPosition(firPos);

    // アニメーション開始から1.2秒経つまで待機
    if(mElapsedTime < 1.2f)
        return;

    // mSecondRectPair のアニメーション
    Vector2 secSize(mSecondRectPair.first->getSize());
    secSize.x += Game::SCREEN_WIDTH / 10.0f * deltaTime * 1.5f;
    mSecondRectPair.first->setSize(secSize);
    mSecondRectPair.second->setSize(secSize);

    Vector2 secPos(mSecondRectPair.first->getPosition());
    secPos.x += Game::SCREEN_WIDTH * deltaTime * 0.8f;
    mSecondRectPair.first->setPosition(secPos);
    secPos.x *= -1;
    mSecondRectPair.second->setPosition(secPos);

    // mSecondRectPair が枠外に出たら削除
    if(mSecondRectPair.first->getPosition().x - mSecondRectPair.first->getSize().x / 2.0f >
       Game::SCREEN_WIDTH / 2.0f)
    {
        removeComponent(mFirstRectPair.first);
        removeComponent(mFirstRectPair.second);
        removeComponent(mSecondRectPair.first);
        removeComponent(mSecondRectPair.second);

        mFirstRectPair = std::make_pair(nullptr, nullptr);
        mSecondRectPair = std::make_pair(nullptr, nullptr);
    
        mIsExecRectAnimation = false;
    }
}

void TETRIS::Title::logoAnimation(float deltaTime)
{

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

    // mRectPair の設定
    SDL_Color white = {255, 255, 255, 255};
    mFirstRectPair.first = new RectangleComponent(this,
                                                  Vector2(0.0, 
                                                          Game::SCREEN_HEIGHT),
                                                  white);
    mFirstRectPair.second = new RectangleComponent(this,
                                                   Vector2(0.0, 
                                                           Game::SCREEN_HEIGHT),
                                                   white);
    mSecondRectPair.first = new RectangleComponent(this,
                                                   Vector2(0.0, 
                                                           Game::SCREEN_HEIGHT),
                                                   white);
    mSecondRectPair.second = new RectangleComponent(this,
                                                    Vector2(0.0, 
                                                            Game::SCREEN_HEIGHT),
                                                    white);

    // mLogoTexture の設定
    std::string logoPath("image/tetris/title_logo.png");
    mLogoTexture = new TextureComponent(this,
                                        logoPath,
                                        150);
    Vector2 logoSize(mLogoTexture->getSize());
    float scale = Game::SCREEN_WIDTH / 4.0f / logoSize.x;
    logoSize *= scale;
    mLogoTexture->setSize(logoSize);
    mLogoTexture->setScale(0.0f);
}