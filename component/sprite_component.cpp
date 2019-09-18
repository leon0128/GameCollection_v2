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
    mIsRecomputedWorldTransform(true)
{
    mRenderer = actor->getController()->getGame()->getRenderer();
    mRenderer->addSprite(this);
}

SpriteComponent::~SpriteComponent()
{
    mRenderer->removeSprite(this);
}

void SpriteComponent::computeWorldTransform()
{
    if(mIsRecomputedWorldTransform ||
       getActor()->isRecomputedWorldTransform())
    {
        mWorldTransform  = Matrix4::createScale(mScale * getActor()->getScale());
        mWorldTransform *= Matrix4::createFromQuaternion(getActor()->getRotation());
        mWorldTransform *= Matrix4::createFromQuaternion(mRotation);
        mWorldTransform *= Matrix4::createTranslation(Vector3(mPosition.x, mPosition.y, 0.0f) + getActor()->getPosition());
    
        mIsRecomputedWorldTransform = false;
    }
}