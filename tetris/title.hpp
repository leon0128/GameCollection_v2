#pragma once

#include "../main/actor.hpp"
#include "../component/texture_component.hpp"
#include "../component/rectangle_component.hpp"

namespace TETRIS
{

class Title : public Actor
{
public:
    Title(class Controller* controller);
    ~Title(){}

private:
    void loadComponents();
};

};