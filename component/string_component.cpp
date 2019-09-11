#include "string_component.hpp"
#include "../main/actor.hpp"

StringComponent::StringComponent(Actor* actor,
                                 const std::string& string,
                                 int drawOrder):
    SpriteComponent(actor, drawOrder),
    mString()
{
    setString(string);
}