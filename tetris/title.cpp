#include "title.hpp"

#include "../main/game.hpp"
#include "../main/controller.hpp"

TETRIS::Title::Title(Controller* controller):
    Actor(controller)
{
    loadComponents();
}

void TETRIS::Title::loadComponents()
{
    // 背景の設定
    std::string backgroundPass("image/tetris/title_background.png");
    TextureComponent* texture = new TextureComponent(this,
                                                     backgroundPass,
                                                     10);
    texture->setSize(Vector2(Game::SCREEN_WIDTH,
                             Game::SCREEN_HEIGHT));
    
    
}