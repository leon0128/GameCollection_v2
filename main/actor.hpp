#pragma once

#include "mathematics.hpp"
#include <vector>

class Actor
{
public:
    // Actorの状態を表す列挙体
    enum EState
    {
        ACTIVE, // 更新
        PAUSED, // 更新停止
        DEAD    // 削除
    };

    explicit Actor(class Controller* controller);
    virtual ~Actor();

    // Controllerクラスで毎フレームごとに呼び出す
    void update(float deltaTime);

    // mComponentsからComponentの追加、削除を行う
    void addComponent(class Component* component);
    void removeComponent(class Component* component);

    // メンバ変数の設定、取得
    void setState(EState state){mState = state;}
    EState getState() const {return mState;}
    const Matrix4& getWorldTransform() const {return mWorldTransform;}
    void setClear(float clear){mClear = clear;}
    float getClear() const {return mClear;}
 
    // SpriteComponent で Renderer を取得するために一時的に実装
    // 解決策が見つかったら削除予定
    class Controller* getController() const {return mController;}

protected:
    // mComponentsを空にする
    void clearComponent();

    // update() で呼び出す
    virtual void updateActor(float deltaTime){}; // 固有の更新

private:
    // update() で呼び出す
    void updateComponents(float deltaTime); // mComponents の更新
    void computeWorldTransform();           // ワールド変換行列の計算
 
    // メンバ変数
    std::vector<class Component*> mComponents; // 自身の所有するComponent

    class Controller* mController; // Controller クラス
    EState mState;                 // 状態
    Matrix4 mWorldTransform;       // ワールド空間への座標変換を行う
    Vector3 mPosition;             // Actor の中心座標
    Quaternion mRotation;          // 回転Quaternion
    float mScale;                  // 大きさ(1.0f で100%)
    float mClear;                  // 透明度(1.0f で100%)

    bool mIsRecomputedWorldTransform; // mWorldTransform を再計算するか
};