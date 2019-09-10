#pragma once

#include "../main/actor.hpp"
#include "../component/gamepad_component.hpp"

namespace Title
{

class Title : public Actor
{
public:
    Title(class Controller* controller);
    ~Title(){}

private:
    void updateActor(float deltaTime) override;

    GamepadComponent* mGamepad;    
};

};