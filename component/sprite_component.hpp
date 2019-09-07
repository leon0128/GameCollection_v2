#pragma once

#include "component.hpp"
#include "../main/mathematics.hpp"

class SpriteComponent : public Component
{
public:
    SpriteComponent(class Actor* actor,
                    class Shader* shader,
                    int drawOrder = 100);
    virtual ~SpriteComponent();

    // Renderer::draw() で呼び出す
    virtual void draw() = 0;

protected:
    // draw() で呼び出す
    class Shader* getShader() const {return mShader;}

private:
    class Shader* mShader;     // シェーダー
    int mDrawOrder;            // 描画優先度
    Vector2 mSize;             // 大きさ
    Vector2 mRelativePosition; // Actor からの相対位置
};