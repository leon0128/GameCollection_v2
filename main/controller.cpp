#include "controller.hpp"
#include "game.hpp"
#include "actor.hpp"

Controller::Controller(Game* game):
    mActors(),
    mPendingActors(),
    mGame(game),
    mLastTicks(0),
    mIsUpdatingActor(false)
{
}

bool Controller::initialize()
{
    return true;
}

void Controller::update()
{

}

void Controller::addActor(Actor* actor)
{
    // mActors が更新中かどうかで格納先の変更
    if(!mIsUpdatingActor)
        mActors.emplace_back(actor);
    else
        mPendingActors.emplace_back(actor);
}