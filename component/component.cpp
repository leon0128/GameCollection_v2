#include "component.hpp"
#include "../main/actor.hpp"

Component::Component(Actor* actor, int order):
    mActor(actor),
    mOrder(order)
{
    actor->addComponent(this);
}

Component::~Component()
{
    mActor->removeComponent(this);
}