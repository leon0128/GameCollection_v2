#pragma once

#include <SDL2/SDL.h>
#include <vector>

class Controller
{
public:
    Controller(class Game* game);
    ~Controller(){}

    bool initialize();

    // Game::update() で呼び出す
    void update();

    // Actor クラスのコンストラクタで呼び出す
    void addActor(class Actor* actor);
    void removeActor(class Actor* actor);

private:
    // update() で呼び出す
    float controllTime();

    std::vector<class Actor*> mActors;        // Actor
    std::vector<class Actor*> mPendingActors; // Actor更新中に一時的に格納される

    class Game* mGame; // 自身が所属するGameクラス
    Uint32 mLastTicks; // 最終更新時間

    bool mIsCreateActor()
    bool mIsUpdatingActor; // Actorを更新中かどうか
};