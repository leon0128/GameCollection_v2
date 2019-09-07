#include "sprite_component.hpp"
#include "../main/actor.hpp"
#include "../main/renderer.hpp"
#include "../main/shader.hpp"

SpriteComponent::SpriteComponent(Actor* actor,
                                 Renderer* renderer,
                                 int drawOrder):
    Component(actor),
    mRenderer(renderer),
    mShader(nullptr),
    mDrawOrder(drawOrder),
    mSize(),
    mRelativePosition()
{
    renderer->addSprite(this);
}

SpriteComponent::~SpriteComponent()
{
    mRenderer->removeSprite();
}