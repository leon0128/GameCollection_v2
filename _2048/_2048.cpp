#include "_2048.hpp"
#include "../main/controller.hpp"

_2048::_2048::_2048(Controller* controller):
    Actor(controller)
{
    SDL_Log("_2048 created");
}