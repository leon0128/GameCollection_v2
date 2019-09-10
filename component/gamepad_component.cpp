#include "gamepad_component.hpp"
#include "../main/input_system.hpp"
#include "../main/actor.hpp"

GamepadComponent::GamepadComponent(Actor* actor,
                                   InputSystem* inputSystem,
                                   int order):
    Component(actor, order),
    mGamepad(),
    mKeyboardMap(),
    mInputSystem(inputSystem)
{
    loadKey();
}

void GamepadComponent::update(float deltaTime)
{
    for(auto& pad : mGamepad)
    {
        for(auto scancode : mKeyboardMap.at(pad.first))
        {
            if(mInputSystem->getKeyboardState(scancode))
            {
                pad.second++;
                break;
            }
        }    
    }
}

void GamepadComponent::addKeyboardMap(EGamepad button,
                                      SDL_Scancode scancode)
{
    // 要素がすでに含まれているかの調査
    auto iterator = std::find(mKeyboardMap.at(button).begin(),
                              mKeyboardMap.at(button).end(),
                              scancode);
    
    if(iterator == mKeyboardMap.at(button).end())
        mKeyboardMap.at(button).emplace_back(scancode);
}

void GamepadComponent::loadKey()
{
    EGamepad buttons[] = {    BUTTON_UP,  BUTTON_DOWN, BUTTON_LEFT, BUTTON_RIGHT,
                               BUTTON_A,     BUTTON_B,    BUTTON_X,     BUTTON_Y,
                               BUTTON_R,     BUTTON_L,
                          BUTTON_SELECT, BUTTON_START, BUTTON_HOME};

    for(EGamepad button : buttons)
    {
        mGamepad.emplace(button, 0);
        mKeyboardMap.emplace(button, std::vector<SDL_Scancode>());
    }
}