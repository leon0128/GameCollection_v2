#include "tetris.hpp"

#include "../main/game.hpp"
#include "../main/controller.hpp"
#include "../component/texture_component.hpp"

TETRIS::Tetris::Tetris(Controller* controller):
    Actor(controller)
{
    std::string filepath("image/tetris/title_background.png");
    TextureComponent* texture = new TextureComponent(this,
                                                     filepath);
    texture->setSize(Vector2(Game::SCREEN_WIDTH,
                             Game::SCREEN_HEIGHT));
}