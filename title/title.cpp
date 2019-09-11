#include "title.hpp"
#include "../main/controller.hpp"
#include "../component/texture_component.hpp"

Title::Title::Title(Controller* controller):
    Actor(controller),
    mGamepad(nullptr)
{
    std::string filename = "image/title/hira.png";
    new TextureComponent(this,
                         filename);
    setClear(0.5f);

    mGamepad = new GamepadComponent(this);
    mGamepad->addKeyboardMap(GamepadComponent::BUTTON_A,
                             SDL_SCANCODE_SPACE);
}

void Title::Title::updateActor(float deltaTime)
{
    if(mGamepad->at(GamepadComponent::BUTTON_A))
    {
        getController()->setState(Controller::_2048);
        setState(DEAD);
    }
}