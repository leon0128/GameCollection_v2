#pragma once

#include "../main/actor.hpp"
#include "../component/rectangle_component.hpp"

namespace TETRIS
{

class Loader : public Actor
{
public:
    Loader(class Tetris* owner);
    ~Loader(){}

    // ロードの実行
    void execute(){mIsExecFadeOut = true;}

    // メンバ変数の取得
    bool isExecFadeOut() const {return mIsExecFadeOut;}
    bool isExecFadeIn() const {return mIsExecFadeIn;}

private:
    void updateActor(float deltaTime) override;

    // 呼ばれた画面からフェードアウト(イン)
    void fadeOut(float deltaTime);
    void fadeIn(float deltaTime);

    std::vector<RectangleComponent*> mDirectionRects; // 四方の矩形

    class Tetris* mOwner; // Tetris クラス
    RectangleComponent* mBGRectangle; // 背景の矩形

    bool mIsExecFadeOut; // fadeOut() の状態
    bool mIsExecFadeIn;  // fadeIn() の状態
};

};