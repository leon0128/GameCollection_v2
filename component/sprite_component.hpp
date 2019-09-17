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
    void setScale(float scale){mScale = scale;}
    float getScale() const {return mScale;}
    const Vector2& getSize() const {return mSize;}
    void setPosition(Vector2& position){mPosition = position;}

protected:
    // メンバ変数の設定、取得
    class Renderer* getRenderer() const {return mRenderer;}
    void setSize(const Vector2& size){mSize = size;}
    const Vector2& getPosition() const {return mPosition;}

private:
    class Renderer* mRenderer; // レンダラー
    int mDrawOrder;            // 描画優先度
    float mScale;              // 大きさ
    float mClear;              // 透明度
    Vector2 mSize;             // 大きさ
    Vector2 mPosition;         // Actor からの相対位置
    Quaternion mRotation;      // 回転
    Matrix4 mWorldTransform;   // ワールド変換行列

    bool misRecomputedWorldTransform; // mWorldTransform の再計算 
};