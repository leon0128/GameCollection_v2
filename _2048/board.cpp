#include "board.hpp"
#include "../main/controller.hpp"
#include "setting.hpp"

_2048::Board::Board(Controller* controller):
    Actor(controller),
    mGameState(),
    mBoardSize()
{

}

void _2048::Board::initialize(Setting* setting)
{
    SDL_Color baseColor  = {55, 55, 55, 255};
    SDL_Color frameColor = {150, 150, 150, 255};

    // 大きさの設定
    Vector2 boardSize(500.0f, 500.0f);
    if(setting->get(Setting::NUM_PLAYER) == 2)
        boardSize.set(450.0f, 450.0f);
    
    mBoardSize = boardSize;

    // 基盤の矩形の作成
    new RectangleComponent(this,
                           mBoardSize,
                           baseColor,
                           10);
}