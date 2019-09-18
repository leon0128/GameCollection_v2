#include "title.hpp"
#include "../main/controller.hpp"
#include "../component/texture_component.hpp"
#include "../component/rectangle_component.hpp"
#include "../component/move_component.hpp"
#include "../component/string_component.hpp"

Title::Title::Title(Controller* controller):
    Actor(controller),
    mGamepad(nullptr)
{
    mGamepad = new GamepadComponent(this);
    mGamepad->addKeyboardMap(GamepadComponent::BUTTON_A,
                             SDL_SCANCODE_SPACE);
}

void Title::Title::updateActor(float deltaTime)
{
    if(mGamepad->at(GamepadComponent::BUTTON_A))
        getController()->setState(Controller::TETRIS);
}