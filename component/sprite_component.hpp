#pragma once

#include "component.hpp"
#include "../main/mathematics.hpp"

class SpriteComponent : public Component
{
public:
    SpriteComponent(class Actor* actor,
                    int drawOrder = 100);
    virtual ~SpriteComponent();

    // Renderer::draw() で呼び出す
    virtual void draw() = 0;

    // メンバ変数の取得
    int getDrawOrder() const {return mDrawOrder;}
    void setScale(float scale){mScale = scale;
                               mIsRecomputedWorldTransform = true;}
    float getScale() const {return mScale;}
    void setClear(float clear){mClear = clear;}
    float getClear() const {return mClear;}
    void setSize(const Vector2& size){mSize = size;
                                      mIsRecomputedWorldTransform = true;}
    const Vector2& getSize() const {return mSize;}
    void setPosition(const Vector2& position){mPosition = position;
                                              mIsRecomputedWorldTransform = true;}
    const Vector2& getPosition() const {return mPosition;}
    void setRotation(const Quaternion& rotation){mRotation = rotation;
                                                 mIsRecomputedWorldTransform = true;}
    const Quaternion& getRotation() const {return mRotation;}

protected:
    // mWorldTransform の再計算
    // draw() 関数の初めに呼び出すようにする
    void computeWorldTransform();

    // メンバ変数の設定、取得
    class Renderer* getRenderer() const {return mRenderer;}

private:
    class Renderer* mRenderer; // レンダラー
    int mDrawOrder;            // 描画優先度
    float mScale;              // 大きさ
    float mClear;              // 透明度
    Vector2 mSize;             // 大きさ
    Vector2 mPosition;         // Actor からの相対位置
    Quaternion mRotation;      // 回転
    Matrix4 mWorldTransform;   // ワールド変換行列

    bool mIsRecomputedWorldTransform; // mWorldTransform の再計算 
};