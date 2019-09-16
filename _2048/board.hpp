#pragma once

#include "../main/actor.hpp"
#include "../component/rectangle_component.hpp"
#include "../component/gamepad_component.hpp"

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
    Vector2 getGridPosition(class Tile* tile) const;

    // メンバ変数の取得
    int getSquared() const {return mSquared;}
    const Vector2& getBaseSize() const {return mBaseSize;}
    GamepadComponent* getGamepad(){return mGamepad;}

private:
    void updateActor(float deltaTime) override;

    // initialize() で実行
    void loadBoard(class Setting* setting);   // ボードの枠の作成

    // updateActor() で実行
    bool input(int& vertical, int& parallel) const; // 動作するならtrue
    bool moveTile(int vertical, int parallel);      // タイルの移動 移動したら true
    bool joinTile(int vertical, int parallel);      // タイルの結合 結合したら true
    bool isGameclear() const;       // 目標スコアに達したか
    bool isGameover() const;        // Gameover かの確認
    bool isTimeUp(float deltaTime); // TimeUP かどうか
    bool generateTile();            // mGameState の空いている位置にTile の作成

    std::vector<class Tile*> mGameState; // ゲームの状態

    int mTimeLimit;     // タイムリミット[s]
    int mGoalScore;     // 目標スコア
    int mSquared;       // 列（行）の要素数
    float mElapsedTime; // 経過時間
    Vector2 mBaseSize;  // Board の大きさ
    GamepadComponent* mGamepad; // ゲームパッド
};

};