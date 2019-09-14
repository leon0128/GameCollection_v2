#include "board.hpp"
#include "../main/controller.hpp"
#include "setting.hpp"

_2048::Board::Board(Controller* controller):
    Actor(controller),
    mGameState(),
    mSquared(0),
    mBaseSize()
{
}

void _2048::Board::initialize(Setting* setting)
{
    SDL_Color baseColor  = {55, 55, 55, 255};
    SDL_Color frameColor = {150, 150, 150, 255};

    // 大きさの設定
    Vector2 size(500.0f, 500.0f);
    if(setting->get(Setting::NUM_PLAYER) == 2)
        size.set(450.0f, 450.0f);
    
    mBaseSize = size;

    // 基盤の矩形の作成
    new RectangleComponent(this,
                           mBaseSize,
                           baseColor,
                           10);

    // 枠の作成
    int mSquared = setting->get(Setting::BOARD_SIZE);
    float width = mBaseSize.x / 400.0f * (45.0f / squared - 2.5f);
    float space = mBaseSize.x / mSquared;
    Vector2 temp;
    for(int i = 0; i < mSquared + 1; i++)
    {
        // 平行な枠
        temp.set(mBaseSize.x, width);
        RectangleComponent* parallel = new RectangleComponent(this,
                                                               temp,
                                                               frameColor,
                                                               50);
        temp.set(0.0f, space * i - mBaseSize.x / 2.0f);
        parallel->setRelativePosition(temp);

        // 垂直な枠
        temp.set(width, mBaseSize.y);
        RectangleComponent* vertical = new RectangleComponent(this,
                                                              temp,
                                                              frameColor,
                                                              50);
        temp.set(space * i - size.x / 2.0f, 0.0f);
        vertical->setRelativePosition(temp);
    }
}

Vector2 _2048::Board::getGridPosition(const Coordinate2& coord) const
{
    Vector2 position;
    // x
    position.x = getPosition().x -
                 mBaseSize.x / 2.0f +
                 mBaseSize.x / mSquared * (0.5f + coord.x);
    // y
    position.y = getPosition().y -
                 mBaseSize.y / 2.0f +
                 mBaseSize.y / mSquared * (0.5f + coord.y);

    return position;
}