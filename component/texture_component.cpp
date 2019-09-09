#include "texture_component.hpp"
#include "../main/actor.hpp"
#include "../main/renderer.hpp"
#include "../main/shader.hpp"
#include "../main/texture.hpp"

#include <iostream>

TextureComponent::TextureComponent(Actor* actor,
                                   std::string& filename,
                                   int drawOrder):
    SpriteComponent(actor, drawOrder),
    mTexture(nullptr)
{   
    // setTexture(filename);
    mTexture = getRenderer()->getCharTexture(Font::SIZE_30,
                                         'A');
    setSize(mTexture->getSize());
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

    SDL_Log("%f, %f", getSize().x, getSize().y);
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            std::cout << getActor()->getWorldTransform().mat[i][j] << ", ";
        }

        std::cout << std::endl;
    }

    // Shader の設定
    Shader* shader = getRenderer()->getShader(Renderer::TEXTURE);
    shader->setActive();
    shader->setUniform("uWorldTransform",
                       Shader::MATRIX4,
                       &worldMatrix);
    float alpha = getActor()->getClear();
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