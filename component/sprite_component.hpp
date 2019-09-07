#pragma once

#include "component.hpp"
#include "../main/mathematics.hpp"

class SpriteComponent : public Component
{
public:
    SpriteComponent(class Actor* actor,
                    class Renderer* renderer,
                    int drawOrder = 100);
    virtual ~SpriteComponent();

    // Renderer::draw() で呼び出す
    virtual void draw() = 0;

protected:
    // メンバ変数の設定、取得
    class Shader* getShader() const {return mShader;}
    void setShader(class Shader* shader){mShader = shader;}
    class Renderer* getRenderer() const {return mRenderer;}

private:
    class Renderer* mRenderer; // レンダラー
    class Shader* mShader;     // シェーダー
    int mDrawOrder;            // 描画優先度
    Vector2 mSize;             // 大きさ
    Vector2 mRelativePosition; // Actor からの相対位置
};