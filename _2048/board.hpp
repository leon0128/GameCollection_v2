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

    // 初期化
    void initialize(class Setting* setting);

    // Coordinate に対応する位置を返す
    Vector2 getGridPosition(const Coordinate2& coord) const;

private:
    // mGameState の空いている位置にTile の作成
    bool generateTile();

    std::vector<class Tile*> mGameState; // ゲームの状態

    int mSquared;      // 列（行）の要素数
    Vector2 mBaseSize; // Board の大きさ
};

};