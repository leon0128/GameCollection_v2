#pragma once

#include "../main/actor.hpp"
#include "../component/texture_component.hpp"
#include "../component/rectangle_component.hpp"

namespace TETRIS
{

class Title : public Actor
{
public:
    Title(class Controller* controller);
    ~Title(){}

private:
    void updateActor(float deltaTime) override;

    // 矩形を使用したアニメーション
    void rectangleAnimation(float deltaTime);

    void loadComponents();

    float mElapsedTime; // 経過時間
    RectangleComponent* mFirstRectangle; // 開始時に画面を覆う矩形
    std::pair<RectangleComponent*, 
              RectangleComponent*> mFirstRectPair;  // 一回目の柱の矩形
    std::pair<RectangleComponent*,
              RectangleComponent*> mSecondRectPair; // 二回目の柱の矩形

    bool mIsExecAnimation; // 開始時のアニメーションを実行しているか
};

};