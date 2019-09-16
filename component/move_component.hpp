#pragma once

#include "component.hpp"
#include "../main/mathematics.hpp"
#include <SDL2/SDL.h>

class MoveComponent : public Component
{
public:
    MoveComponent(class Actor* actor,
                  int order = 150);
    ~MoveComponent(){}

    void update(float deltaTime) override;

    // 目的地と移動時間の設定
    void move(const Vector3& destination,
              float moveTime);

private:
    float mMoveTime;   // 目的地までの移動時間
    float mElapseTime; // 経過時間
    Vector3 mDestination;       // 目的地

    bool mIsMoving; // 移動中かどうか
    bool mIsActive; // 移動するかどうか
};