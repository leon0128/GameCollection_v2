#include "string_component.hpp"
#include "../main/actor.hpp"
#include "../main/controller.hpp"
#include "../main/game.hpp"
#include "../main/renderer.hpp"
#include "../main/shader.hpp"
#include "../main/texture.hpp"

StringComponent::StringComponent(Actor* actor,
                                 const std::string& string,
                                 Font::ESize size,
                                 int drawOrder):
    SpriteComponent(actor, drawOrder),
    mString(),
    mFontSize(size)
{
    setString(string);
}

void StringComponent::setString(const std::string& string)
{
    mStringTexture.clear();

    Vector2 size;
    Renderer* renderer = getActor()->getController()->getGame()->getRenderer();
    
    for(size_t i = 0; i < string.size(); i++)
    {
        Texture* texture = renderer->getCharTexture(mFontSize,
                                                    string.at(i));
        
        size.x += texture->getSize().x;
        size.y = (size.y < texture->getSize().y) ? texture->getSize().y : size.y;

        mStringTexture.emplace_back(texture);
    }

    setSize(size);
}