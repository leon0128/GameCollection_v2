#pragma once

#include "../main/actor.hpp"

namespace _2048
{

class _2048 : public Actor
{
public:
    _2048(class Controller* controller);
    ~_2048(){}

private:
    void updateActor(float deltaTime) override;

    // mSetting を参考に各種オブジェクトの作成
    void initialize();

    class Setting* mSetting; // Setting クラス

    bool mIsInitialized; // 初期化したか(initialize() を実行したか)
};

};