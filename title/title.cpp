#include "title.hpp"
#include "../main/controller.hpp"
#include "../component/texture_component.hpp"

Title::Title::Title(Controller* controller):
    Actor(controller)
{
    std::string filename("image/title/hira.png");
    TextureComponent* texture = new TextureComponent(this,
                                                     filename);
}