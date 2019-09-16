#include "move_component.hpp"

#include "../main/actor.hpp"

MoveComponent::MoveComponent(Actor* actor, int order):
    Component(actor, order),
    mMoveTime(0.0f),
    mElapseTime(0.0f),
    mDestination(),
    mIsMoving(false),
    mIsActive(false)
{
}

void MoveComponent::update(float deltaTime)
{
    if(!mIsActive)
        return;

    if(mMoveTime <= (mElapseTime + deltaTime))
    {
        getActor()->setPosition(mDestination);
        mIsMoving = false;
        mIsActive = false;
    }

    Vector3 sumDistance = mDestination - getActor()->getPosition();
    Vector3 distance = getActor()->getPosition() +
                       sumDistance * (deltaTime / (mMoveTime - mElapseTime));

    getActor()->setPosition(distance);
                                            
    mElapseTime += deltaTime;
}

void MoveComponent::move(const Vector3& destination,
                         float moveTime)
{
    if(moveTime < 0.0f)
    {
        SDL_Log("Invalid move time value: %f",
                moveTime);
        return;
    }

    mMoveTime = moveTime;
    mElapseTime = 0.0f;
    mDestination = destination;
    mIsMoving = true;
    mIsActive = true;
}