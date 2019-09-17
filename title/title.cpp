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
    std::string filename = "image/title/hira.png";
    new TextureComponent(this,
                         filename);

    mGamepad = new GamepadComponent(this);
    mGamepad->addKeyboardMap(GamepadComponent::BUTTON_A,
                             SDL_SCANCODE_SPACE);

    Vector2 rect(100.0f, 100.0f);
    SDL_Color color = {255, 255, 100, 200};    
    new RectangleComponent(this,
                           rect,
                           color);

    Vector3 destination(300.0f, 300.0f, 0.0f);
    MoveComponent* move = new MoveComponent(this);
    move->move(destination, 10.0f);

    std::string str("a");
    new StringComponent(this,
                        str);
}

void Title::Title::updateActor(float deltaTime)
{
    if(mGamepad->at(GamepadComponent::BUTTON_A))
    {
        getController()->setState(Controller::_2048);
        setState(DEAD);
    }
}