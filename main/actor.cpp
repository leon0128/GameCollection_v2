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

void Actor::addComponent(Component* component)
{
    // 変数の設定
    int order = component->getOrder();
    auto iterator = mComponents.begin();

    // 挿入する場所の調査
    for(;
        iterator != mComponents.end();
        iterator++)
    {
        if(order < (*iterator)->getOrder())
            break;
    }

    // 挿入
    mComponents.insert(iterator,
                       component);
}

void Actor::removeComponent(Component* component)
{
    auto iterator = mComponents.begin();

    // 削除対象の捜査
    for(;
        iterator != mComponents.end();
        iterator++)
    {
        if(*iterator == component)
            break;
    }

    // 削除するか警告文を表示
    if(iterator != mComponents.end())
    {
        mComponents.erase(iterator);
    }
    else
    {
        SDL_Log("Component to delete was not found: %s",
                __PRETTY_FUNCTION__);
    }
}