#include "rectangle_component.hpp"
#include "../main/actor.hpp"
#include "../main/renderer.hpp"
#include "../main/shader.hpp"

RectangleComponent::RectangleComponent(Actor* actor,
                                       Vector2& size,
                                       SDL_Color& color,
                                       int drawOrder):
    SpriteComponent(actor, drawOrder),
    mColor(color)
{
    setSize(size);
}

void RectangleComponent::draw()
{
    // ワールド空間に変換
    Matrix4 scaleMatrix = Matrix4::createScale(getSize().x,
                                               getSize().y,
                                               1.0f);
    Matrix4 worldMatrix = scaleMatrix * getActor()->getWorldTransform();
    Vector3 relativePos(getRelativePosition().x,
                        getRelativePosition().y,
                        0.0f);
    worldMatrix *= Matrix4::createTranslation(relativePos);

    // Shader の設定
    Shader* shader = getRenderer()->getShader(Renderer::RECTANGLE);
    shader->setActive();
    shader->setUniform("uWorldTransform",
                       Shader::MATRIX4,
                       &worldMatrix);
    shader->setUniform("uFilledColor",
                       Shader::COLOR,
                       &mColor);
    
    glDrawElements(GL_TRIANGLES,
                   6,
                   GL_UNSIGNED_INT,
                   nullptr);
}