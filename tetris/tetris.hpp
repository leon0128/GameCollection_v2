#pragma once

#include "../main/actor.hpp"
#include "../component/texture_component.hpp"
#include "../component/rectangle_component.hpp"

namespace TETRIS
{

class Tetris : public Actor
{
public:
    Tetris(class Controller* controller);
    ~Tetris(){}

private:
};

};