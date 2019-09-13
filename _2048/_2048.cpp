#include "_2048.hpp"
#include "../main/controller.hpp"
#include "setting.hpp"

_2048::_2048::_2048(Controller* controller):
    Actor(controller),
    mSetting(nullptr)
{
    mSetting = new Setting(controller);
}

void _2048::_2048::updateActor(float deltaTime)
{

}

void _2048::_2048::initialize()
{

}