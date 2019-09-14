#include "string_component.hpp"
#include "../main/actor.hpp"
#include "../main/controller.hpp"
#include "../main/game.hpp"
#include "../main/renderer.hpp"
#include "../main/shader.hpp"
#include "../main/texture.hpp"

StringComponent::StringComponent(Actor* actor,
                                 const std::string& string,
                                 Font::ESize size,
                                 int drawOrder):
    SpriteComponent(actor, drawOrder),
    mStringTexture(),
    mColor(),
    mBackGroundColor(),
    mFontSize(size)
{
    SDL_Color bgColor = {0, 0, 0, 0};
    setBackGroundColor(bgColor);

    SDL_Color black = {0, 0, 0, 255};
    setString(string);
    setColor(black);
}

void StringComponent::draw()
{
    if(mStringTexture.size() == 0)
        return;
    for(auto& texture : mStringTexture)
        if(!texture)
            return;

    Shader* shader = getActor()->getController()->getGame()->getRenderer()->getShader(Renderer::STRING);


    float offset = getSize().x / 2.0f * (-1.0f) +
                   mStringTexture.at(0)->getSize().x / 2.0f;
    
    for(size_t i = 0; i < mStringTexture.size(); i++)
    {
        Matrix4 scaleMatrix = Matrix4::createScale(mStringTexture.at(i)->getSize().x,
                                                   mStringTexture.at(i)->getSize().y,
                                                   1.0f);
        
        Matrix4 worldMatrix = scaleMatrix * 
                              getActor()->getWorldTransform() *
                              Matrix4::createTranslation(Vector3(offset + getRelativePosition().x,
                                                                 getRelativePosition().y,
                                                                 0.0f));
        worldMatrix *= Matrix4::createScale(getScale());
    
        offset += mStringTexture.at(i)->getSize().x;

        shader->setActive();
        shader->setUniform("uWorldTransform",
                           Shader::MATRIX4,
                           &worldMatrix);
        shader->setUniform("uCharColor",
                           Shader::COLOR,
                           &mColor);
        shader->setUniform("uBGColor",
                           Shader::COLOR,
                           &mBackGroundColor);

        mStringTexture.at(i)->setActive();

        glDrawElements(GL_TRIANGLES,
                       6,
                       GL_UNSIGNED_INT,
                       nullptr);
    }
}

void StringComponent::setString(const std::string& string)
{
    mStringTexture.clear();

    Vector2 size;
    Renderer* renderer = getActor()->getController()->getGame()->getRenderer();
    
    for(size_t i = 0; i < string.size(); i++)
    {
        Texture* texture = renderer->getCharTexture(mFontSize,
                                                    string.at(i));
        
        size.x += texture->getSize().x;
        size.y = (size.y < texture->getSize().y) ? texture->getSize().y : size.y;

        mStringTexture.emplace_back(texture);
    }

    setSize(size);
}