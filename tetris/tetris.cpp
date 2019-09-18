#include "tetris.hpp"

#include "../main/game.hpp"
#include "../main/controller.hpp"
#include "title.hpp"

TETRIS::Tetris::Tetris(Controller* controller):
    Actor(controller)
{
    new Title(getController());
}