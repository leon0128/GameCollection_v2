#include "texture_component.hpp"
#include "../main/actor.hpp"
#include "../main/renderer.hpp"
#include "../main/shader.hpp"
#include "../main/texture.hpp"

TextureComponent::TextureComponent(Actor* actor,
                                   Renderer* renderer,
                                   int drawOrder):
    SpriteComponent(actor, renderer, drawOrder),
    mTexture(nullptr)
{
    setShader(renderer->getShader(Renderer::TEXTURE));
}

void TextureComponent::draw()
{
    if(!mTexture)
        return;

    // ワールド空間に変換
    Matrix4 scaleMatrix = Matrix4::createScale(getSize().x,
                                               getSize().y,
                                               1.0f);
    Matrix4 worldMatrix = scaleMatrix * getActor()->getWorldTransform();

    // Shader の設定
    getShader()->setActive();
    getShader()->setUniform("uWorldTransform",
                            Shader::MATRIX4,
                            &worldMatrix);
    float alpha = getActor()->getClear();
    getShader()->setUniform("uAlpha",
                            Shader::FLOAT,
                            &alpha);
    
    mTexture->setActive();

    // 描画
    glDrawElements(GL_TRIANGLES,
                   6,
                   GL_UNSIGNED_INT,
                   nullptr);
}

void TextureComponent::setTexture(Texture* texture)
{
    if(texture)
        setSize(texture->getSize());

    mTexture = texture;
}