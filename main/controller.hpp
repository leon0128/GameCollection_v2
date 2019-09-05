#pragma once

#include <SDL2/SDL.h>
#include <vector>

class Controller
{
public:
    // Game の状態
    enum EState
    {
        TITLE,
        SELECT,
        _2048
    };

    explicit Controller(class Game* game);
    ~Controller(){}

    bool initialize();

    // Game::update() で呼び出す
    void update();

    // Actor クラスのコンストラクタで呼び出す
    void addActor(class Actor* actor);
    void removeActor(class Actor* actor);

    // Game の状態を更新するか
    void setState(EState state){mState = state;
                                mIsResetActor = true;};

private:
    // update() で呼び出す
    float controllTime();  // 時間制御
    void controllActor(); // 各ゲーム、モードの主要Actorの作成

    std::vector<class Actor*> mActors;        // Actor
    std::vector<class Actor*> mPendingActors; // Actor更新中に一時的に格納される

    class Game* mGame; // 自身が所属するGameクラス
    Uint32 mLastTicks; // 最終更新時間
    EState mState;     // Game の状態

    bool mIsResetActor;    // Actorを再設定するか
    bool mIsUpdatingActor; // Actorを更新中かどうか
};