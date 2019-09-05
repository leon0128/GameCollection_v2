#include "controller.hpp"
#include "game.hpp"

Controller::Controller(Game* game):
    mGame(game)
{
}

bool Controller::initialize()
{
    return true;
}

void Controller::update()
{

}