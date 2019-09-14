#pragma once

#include "../main/actor.hpp"
#include "../component/rectangle_component.hpp"

namespace _2048
{

class Board : public Actor
{
public:
    Board(class Controller* controller);
    ~Board(){}

    void initialize(class Setting* setting);

private:
    std::vector<class Tile*> mGameState; // ゲームの状態

    Vector2 mBoardSize; // Board の大きさ
};

};