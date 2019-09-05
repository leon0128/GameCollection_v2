#include "actor.hpp"
#include "controller.hpp"
#include "../component/component.hpp"

Actor::Actor(Controller* controller):
    mComponents(),
    mController(controller),
    mState(ACTIVE),
    mWorldTransform(Matrix4::IDENTITY),
    mPosition(),
    mRotation(Quaternion::IDENTITY),
    mScale(1.0f),
    mClear(1.0f),
    mIsRecomputedWorldTransform(true)
{
    controller->addActor(this);
}

Actor::~Actor()
{
    mController->removeActor(this);
}

void Actor::update(float deltaTime)
{
    // mState == ACTIVE なら更新
    if(mState == ACTIVE)
    {
        computeWorldTransform();
        updateComponents(deltaTime);
        updateActor(deltaTime);
        computeWorldTransform();
    }
}