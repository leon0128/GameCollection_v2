#include "rectangle_component.hpp"
#include "../main/actor.hpp"
#include "../main/renderer.hpp"
#include "../main/shader.hpp"

RectangleComponent::RectangleComponent(Actor* actor,
                                       Vector2& size,
                                       const SDL_Color& color,
                                       int drawOrder):
    SpriteComponent(actor, drawOrder),
    mColor()
{
    setColor(color);
    setSize(size);
}

void RectangleComponent::draw()
{
    computeWorldTransform();
    Matrix4 worldTransform = Matrix4::createScale(getSize().x,
                                                  getSize().y,
                                                  0.0f) *
                             getWorldTransform();

    // Shader の設定
    Shader* shader = getRenderer()->getShader(Renderer::RECTANGLE);
    shader->setActive();
    shader->setUniform("uWorldTransform",
                       Shader::MATRIX4,
                       &worldTransform);
    shader->setUniform("uFilledColor",
                       Shader::COLOR,
                       &mColor);
    
    glDrawElements(GL_TRIANGLES,
                   6,
                   GL_UNSIGNED_INT,
                   nullptr);
}