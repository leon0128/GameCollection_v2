#include "_2048.hpp"
#include "../main/controller.hpp"
#include "../component/string_component.hpp"
#include "../component/texture_component.hpp"
#include "../component/rectangle_component.hpp"

_2048::_2048::_2048(Controller* controller):
    Actor(controller)
{
    SDL_Color black = {255, 255, 255, 255};
    Vector2 size(100.0f, 100.0f);

    RectangleComponent* rect = new RectangleComponent(this,
                                                      size,
                                                      black);
}