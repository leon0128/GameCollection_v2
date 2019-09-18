#pragma once

#include <SDL2/SDL.h>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <vector>
#include <unordered_map>

class Controller
{
public:
    // Game の状態
    enum EState
    {
        TITLE,
        SELECT,
        _2048,
        TETRIS
    };

    explicit Controller(class Game* game);
    ~Controller(){}

    bool initialize();
    void finalize();

    // Game::update() で呼び出す
    void update();

    // Actor クラスのコンストラクタで呼び出す
    void addActor(class Actor* actor);
    void removeActor(class Actor* actor);

    // Game の状態を更新するか
    void setState(EState state){mState = state;
                                mIsResetObject = true;};
    
    // SpriteComponent でRendererを取得するために一時的に実装
    // 解決策が見つかったら削除予定
    class Game* getGame() const {return mGame;}

private:
    // update() で呼び出す
    float controllTime();              // 時間制御
    void controllActor();              // 各ゲーム、モードの主要Actorの作成
    void controllTexture() const;      // Renderer::mTextureMap の更新
    void updateActor(float deltaTime); // Actor の更新

    std::vector<class Actor*> mActors;        // Actor
    std::vector<class Actor*> mPendingActors; // Actor更新中に一時的に格納される

    std::unordered_map<EState, std::string> mFilePathMap; // 画像ファイルのファイルパス

    class Game* mGame; // 自身が所属するGameクラス
    Uint32 mLastTicks; // 最終更新時間
    EState mState;     // Game の状態

    bool mIsResetObject;    // Actor 及び Texture を再設定するか
    bool mIsUpdatingActor; // Actorを更新中かどうか
};