#include "controller.hpp"
#include "game.hpp"
#include "actor.hpp"

Controller::Controller(Game* game):
    mActors(),
    mPendingActors(),
    mGame(game),
    mLastTicks(0),
    mState(TITLE),
    mIsResetActor(true),
    mIsUpdatingActor(false)
{
}

bool Controller::initialize()
{
    // mLastTicks の設定
    mLastTicks = SDL_GetTicks();

    return true;
}

void Controller::update()
{
    // 時間制御
    float deltaTime = controllTime();

    // Actor の作成
    if(mIsResetActor)
        controllActor();

    // Actor の更新
    updateActor(deltaTime);
}

void Controller::addActor(Actor* actor)
{
    // mActors が更新中かどうかで格納先の変更
    if(!mIsUpdatingActor)
        mActors.emplace_back(actor);
    else
        mPendingActors.emplace_back(actor);
}

void Controller::removeActor(Actor* actor)
{
    // mActors 内の調査
    auto actIter = mActors.begin();
    for(;
        actIter != mActors.end();
        actIter++)
    {
        if(actor == *actIter)
            break;
    }
    // mActos に対象のActor が存在するなら削除
    if(actIter != mActors.end())
    {    
        mActors.erase(actIter);
        return;
    }

    // mPendingActors 内を調査
    auto pendActIter = mPendingActors.begin();
    for(;
        pendActIter != mPendingActors.end();
        pendActIter++)
    {
        if(actor == *pendActIter)
            break;
    }
    // mPendingActors 内に対象のActor が存在するなら削除
    if(pendActIter != mPendingActors.end())
    {
        mPendingActors.erase(pendActIter);
        return;
    }

    // 削除するActorが見つからなかった場合、警告文の出力
    if(actIter == mActors.end() &&
       pendActIter == mPendingActors.end())
    {
        SDL_Log("Actor to delete was not found: %s",
                __PRETTY_FUNCTION__);
    }
}

float Controller::controllTime()
{
    // フレームレート管理
    while(!SDL_TICKS_PASSED(SDL_GetTicks(),
                            mLastTicks + 1000 / Game::FRAME_RATE));

    // deltaTime の設定
    float deltaTime = (SDL_GetTicks() - mLastTicks) / 1000.0f;
    if(deltaTime > 3.0f / Game::FRAME_RATE)
        deltaTime = 3.0f / Game::FRAME_RATE;

    // mLastTicks の更新
    mLastTicks = SDL_GetTicks();

    return deltaTime;
}

void Controller::controllActor()
{
    mIsResetActor = false;

    // 現在存在するActorの削除
    for(auto& actor : mActors)
        actor->setState(Actor::DEAD);
    for(auto& actor : mPendingActors)
        actor->setState(Actor::DEAD);

    // mState に応じて作成するActorの設定
    switch(mState)
    {
        case(TITLE):
        {
            break;
        }
        case(SELECT):
        {
            break;
        }
        case(_2048):
        {
            break;
        }
    }
}

void Controller::updateActor(float deltaTime)
{
    // mActors の更新
    mIsUpdatingActor = true;
    for(auto& actor : mActors)
        actor->update(deltaTime);
    mIsUpdatingActor = false;

    // mPendingActor内の要素をmActorsに移動
    for(auto& actor : mPendingActors)
        mActors.emplace_back(actor);
    mPendingActors.clear();

    // Actor::mState == Actor::DEAD の削除
    std::vector<Actor*> deadActors;
    for(auto& actor : mActors)
    {
        if(actor->getState() == Actor::DEAD)
            deadActors.emplace_back(actor);
    }
    for(auto& actor : deadActors)
        delete actor;
}