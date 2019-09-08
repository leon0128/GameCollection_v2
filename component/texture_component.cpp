#include "texture_component.hpp"
#include "../main/actor.hpp"
#include "../main/renderer.hpp"
#include "../main/shader.hpp"
#include "../main/texture.hpp"

TextureComponent::TextureComponent(Actor* actor,
                                   Renderer* renderer,
                                   int drawOrder):
    SpriteComponent(actor, renderer, drawOrder),
    mTexture(nullptr)
{
    setShader(renderer->getShader(Renderer::TEXTURE));
}

void TextureComponent::setTexture(Texture* texture)
{
    if(texture)
        setSize(texture->getSize());

    mTexture = texture;
}