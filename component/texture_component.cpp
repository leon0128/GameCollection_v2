#include "texture_component.hpp"
#include "../main/actor.hpp"
#include "../main/renderer.hpp"
#include "../main/shader.hpp"
#include "../main/texture.hpp"

TextureComponent::TextureComponent(Actor* actor,
                                   std::string& filename,
                                   int drawOrder):
    SpriteComponent(actor, drawOrder),
    mTexture(nullptr)
{   
    setTexture(filename);
}

void TextureComponent::draw()
{
    if(!mTexture)
        return;

    // ワールド変換行列の更新
    computeWorldTransform();
    Matrix4 worldTransform = Matrix4::createScale(getSize().x,
                                                  getSize().y,
                                                  0.0f) *
                             getWorldTransform();

    // Shader の設定
    Shader* shader = getRenderer()->getShader(Renderer::TEXTURE);
    shader->setActive();
    shader->setUniform("uWorldTransform",
                       Shader::MATRIX4,
                       &worldTransform);
    float alpha = getActor()->getClear() * getClear();
    shader->setUniform("uAlpha",
                       Shader::FLOAT,
                       &alpha);
    
    // Texture の有効化
    mTexture->setActive();

    // 描画
    glDrawElements(GL_TRIANGLES,
                   6,
                   GL_UNSIGNED_INT,
                   nullptr);
}

void TextureComponent::setTexture(std::string& filename)
{
    if(filename.size() == 0)
        return;
    
    mTexture = getRenderer()->getTexture(filename);

    if(mTexture)
        setSize(mTexture->getSize());
}