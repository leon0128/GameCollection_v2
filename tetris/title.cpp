#include "title.hpp"

#include "../main/game.hpp"
#include "../main/controller.hpp"

TETRIS::Title::Title(Controller* controller):
    Actor(controller),
    mSplashTextures(),
    mElapsedTime(0.0f),
    mFirstRectangle(nullptr),
    mFirstRectPair(std::make_pair(nullptr, nullptr)),
    mSecondRectPair(std::make_pair(nullptr, nullptr)),
    mLogoTexture(nullptr),
    mIsExecRectAnimation(true),
    mIsExecLogoAnimation(true),
    mIsExecSplashAnimation(true)
{
    loadComponents();
}

void TETRIS::Title::updateActor(float deltaTime)
{
    rectangleAnimation(deltaTime);
    logoAnimation(deltaTime);
    splashAnimation(deltaTime);

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
    // 各アニメーションまでの時間
    float sectionTime = 0.0f;
    float waitSection = 0.4f;
    float firstSection = 0.05f;
    float loopSecion = 0.15f;

    if(!mIsExecLogoAnimation)
        return;
    else
        sectionTime += waitSection;

    if(mElapsedTime < sectionTime)
        return;
    else
        sectionTime += firstSection;
    
    if(mElapsedTime < sectionTime)
    {
        float scale = mLogoTexture->getScale() + deltaTime / firstSection;
        mLogoTexture->setScale(scale);

        return;
    }
    else
        sectionTime += loopSecion;

    // 各ループ時のスケール変更レート
    std::array<float, 4> rate = {-0.4f, 0.3f, -0.2f, 0.1f};
    for(size_t i = 0; i < rate.size(); i++)
    {
        if(mElapsedTime < sectionTime)
        {
            float scale = mLogoTexture->getScale() + 
                          rate.at(i) * deltaTime / loopSecion;
            mLogoTexture->setScale(scale);
        }
        else if(i == rate.size() - 1)
        {
            mLogoTexture->setScale(1.0f);
            mIsExecLogoAnimation = false;
        }
        else
        {
            sectionTime += loopSecion;
        }
    }
}

void TETRIS::Title::splashAnimation(float deltaTime)
{
    if(!mIsExecSplashAnimation)
        return;
    
    // アニメーション開始時間
    float waitTime = 0.2f, sectionTime = 0.0f;
    if(mElapsedTime < waitTime)
        return;
    else
        sectionTime += waitTime;

    std::vector<float> secTimes = {0.0f,
                                   0.0f,
                                   0.2f,
                                   0.0f,
                                   0.2f,
                                   0.0f,
                                   0.1f};

    // 移動距離設定
    float dist = Game::SCREEN_WIDTH * deltaTime;
    for(size_t i = 0; i < mSplashTextures.size(); i++)
    {
        sectionTime += secTimes.at(i);

        if(mElapsedTime > sectionTime)
        {
            Vector2 pos = mSplashTextures.at(i)->getPosition();
            float rad = 2 * std::acos(mSplashTextures.at(i)->getRotation().w);
        
            pos.x += dist * std::cos(rad);
            pos.y += dist * std::sin(rad);

            mSplashTextures.at(i)->setPosition(pos);
        }
        else
            break;
    }

    if(mElapsedTime >= 2.0f)
    {
        for(auto& texture : mSplashTextures)
            removeComponent(texture);
        
        mIsExecSplashAnimation = false;
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
    texture->setClear(0.5f);
    
    // mFirstRectangle の設定
    SDL_Color yellow = {255, 255, 50, 255};
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
    float scale = Game::SCREEN_WIDTH / 3.0f / logoSize.x;
    logoSize *= scale;
    mLogoTexture->setSize(logoSize);
    mLogoTexture->setScale(0.0f);

    // mSplashTextures の設定
    std::vector<std::string> minoPath = {"image/tetris/mino_i.png",
                                         "image/tetris/mino_o.png",
                                         "image/tetris/mino_t.png",
                                         "image/tetris/mino_s.png",
                                         "image/tetris/mino_z.png",
                                         "image/tetris/mino_l.png",
                                         "image/tetris/mino_j.png"};
    std::vector<float> thetaList = {  0.0f,
                                    200.0f,
                                    340.0f,
                                    180.0f,
                                    150.0f,
                                     35.0f,
                                    220.0f};
    std::vector<float> scaleList = {2.5f,
                                    3.0f,
                                    2.0f,
                                    2.0f,
                                    2.0f,
                                    1.5f,
                                    1.5f};
    for(size_t i = 0; i < minoPath.size(); i++)
    {
        mSplashTextures.emplace_back(new TextureComponent(this,
                                                          minoPath.at(i),
                                                          80));
        
        Quaternion rotation = Quaternion::concatenate(mSplashTextures.back()->getRotation(),
                                                      Quaternion(Vector3::UNIT_Z, thetaList.at(i)));
        mSplashTextures.back()->setRotation(rotation);
        mSplashTextures.back()->setScale(scaleList.at(i));
    }
}