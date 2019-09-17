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
    Vector3 relation(getPosition().x, getPosition().y, 0.0f);
    Matrix4 worldTransform = Matrix4::createScale(getActor()->getScale()) * Matrix4::createScale(Vector3(getSize().x, getSize().y, 1.0f));
    worldTransform *= Matrix4::createFromQuaternion(getActor()->getRotation());
    worldTransform *= Matrix4::createTranslation(getActor()->getPosition() + relation);

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