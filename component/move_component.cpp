#include "move_component.hpp"

#include "../main/actor.hpp"

MoveComponent::MoveComponent(Actor* actor, int order):
    Component(actor, order),
    mMoveTime(0.0f),
    mDestination(),
    mIsMoving(false),
    mIsActive(false)
{
}

void MoveComponent::move(const Vector3& destination,
                         float moveTime)
{
    mMoveTime = moveTime;
    mDestination = destination;
    mIsMoving = true;
    mIsActive = true;
}