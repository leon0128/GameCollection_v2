#include "sprite_component.hpp"
#include "../main/game.hpp"
#include "../main/renderer.hpp"
#include "../main/controller.hpp"
#include "../main/actor.hpp"

SpriteComponent::SpriteComponent(Actor* actor,
                                 int drawOrder):
    Component(actor),
    mDrawOrder(drawOrder),
    mScale(1.0f),
    mClear(1.0f),
    mSize(),
    mPosition(),
    mRotation(),
    mWorldTransform(),
    misRecomputedWorldTransform(true)
{
    mRenderer = actor->getController()->getGame()->getRenderer();
    mRenderer->addSprite(this);
}

SpriteComponent::~SpriteComponent()
{
    mRenderer->removeSprite(this);
}