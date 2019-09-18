#pragma once

#include "../main/actor.hpp"

namespace TETRIS
{

class Tetris : public Actor
{
public:
    Tetris(class Controller* controller);
    ~Tetris(){}
};

};