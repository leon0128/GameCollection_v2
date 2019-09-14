#include "tile.hpp"
#include "../main/controller.hpp"
#include "board.hpp"

_2048::Tile::Tile(Controller* controller,
                  Board* owner,
                  int score):
    Actor(controller),
    mOwner(owner),
    mScore(score),
    mCoordinate(),
    mRectangle(nullptr),
    mString(nullptr)
{
}

void _2048::Tile::updateActor(float deltaTime) override
{
    
}