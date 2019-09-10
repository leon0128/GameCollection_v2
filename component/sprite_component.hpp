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
    const Vector2& getSize() const {return mSize;}
    void setRelativePosition(Vector2& position){mRelativePosition = position;}

protected:
    // メンバ変数の設定、取得
    class Renderer* getRenderer() const {return mRenderer;}
    void setSize(const Vector2& size){mSize = size;}
    const Vector2& getRelativePosition() const {return mRelativePosition;}

private:
    class Renderer* mRenderer; // レンダラー
    int mDrawOrder;            // 描画優先度
    Vector2 mSize;             // 大きさ
    Vector2 mRelativePosition; // Actor からの相対位置
};