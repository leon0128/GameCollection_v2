#include "gamepad_component.hpp"
#include "../main/actor.hpp"

GamepadComponent::GamepadComponent(Actor* actor,
                                   int order):
    Component(actor, order),
    mGamepad()
{
    loadKey();
}

void GamepadComponent::loadKey()
{
    EGamepad buttons[] = {    BUTTON_UP,  BUTTON_DOWN, BUTTON_LEFT, BUTTON_RIGHT,
                               BUTTON_A,     BUTTON_B,    BUTTON_X,     BUTTON_Y,
                               BUTTON_R,     BUTTON_L,
                          BUTTON_SELECT, BUTTON_START, BUTTON_HOME};

    for(EGamepad button : buttons)
        mGamepad.emplace(button, 0);
}