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

    // 作成時のアニメーション
    void startAnimation(float deltaTime);

    void loadComponents();

    RectangleComponent* mFirstRectangle; // 開始時に画面を覆う矩形

    bool mIsExecAnimation; // 開始時のアニメーションを実行しているか
};

};