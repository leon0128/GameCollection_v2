#include "renderer.hpp"
#include "game.hpp"
#include "shader.hpp"
#include "../component/sprite_component.hpp"

Renderer::Renderer(Game* game):
    mShaderMap(),
    mSprites(),
    mGame(game),
    mWindow(nullptr),
    mContext()
{
}

bool Renderer::initialize()
{
    // openGL の属性設定
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,
                        4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,
                        5);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,
                        8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,
                        8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,
                        8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,
                        8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,
                        24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,
                        1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL,
                        1);

    // mWindow の設定
    mWindow = SDL_CreateWindow("Game",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               (int)Game::SCREEN_WIDTH,
                               (int)Game::SCREEN_HEIGHT,
                               SDL_WINDOW_OPENGL);
    if(!mWindow)
    {
        SDL_Log("Failed to create window: %s",
                SDL_GetError());
        return false;
    }

    // mContext の設定
    mContext = SDL_GL_CreateContext(mWindow);

    // GLEW の初期化
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
        SDL_Log("Failed to initialize GLEW");
        return false;
    }
    glGetError();

    // mShaderMap の設定
    if(!loadShaders())
    {
        SDL_Log("Failed to load Shaders");
        return false;
    }

    return true;
}

void Renderer::finalize()
{
    // mContext, mWindow の削除
    SDL_GL_DeleteContext(mContext);
    SDL_DestroyWindow(mWindow);
}

void Renderer::draw()
{
    // カラーバッファの初期化
    glClearColor(1.0f,
                 1.0f,
                 1.0f,
                 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Sprite の描画
    glDisable(GL_DEPTH_TEST); // 深度バッファ無効化
    glEnable(GL_BLEND);       // アルファブレンド有効化
    glBlendEquationSeparate(GL_FUNC_ADD,
                            GL_FUNC_ADD);
    glBlendFuncSeparate(GL_SRC_ALPHA,
                        GL_ONE_MINUS_SRC_ALPHA,
                        GL_ONE,
                        GL_ZERO);

    // mSprites の描画
    for(auto& sprite : mSprites)
        sprite->draw();
    
    // バッファ入れ替え
    SDL_GL_SwapWindow(mWindow);
}

Shader* Renderer::getShader(EShader shader) const
{
    auto iterator = mShaderMap.find(shader);
    if(iterator != mShaderMap.end())
    {
        return iterator->second;
    }
    else
    {
        SDL_Log("Shader not found: %d",
                shader);
        return nullptr;
    }
}

void Renderer::addSprite(SpriteComponent* sprite)
{
    int order = sprite->getOrder();

    // 挿入位置の捜査
    auto iterator = mSprites.begin();
    for(;
        iterator != mSprites.end();
        iterator++)
    {
        if(order < (*iterator)->getOrder())
            break;
    }

    // 挿入
    mSprites.insert(iterator,
                    sprite);
}

void Renderer::removeSprite(SpriteComponent* sprite)
{
    // 対象の位置の捜査
    auto iterator = mSprites.begin();
    for(;
        iterator != mSprites.end();
        iterator++)
    {
        if(*iterator == sprite)
            break;
    }

    // 要素の削除
    if(iterator != mSprites.end())
    {
        mSprites.erase(iterator);
    }
    else
    {
        SDL_Log("The target for deletion was not found: %s",
                __PRETTY_FUNCTION__);
    }
}

bool Renderer::loadShaders()
{
    if(!loadTextureShader())
        return false;
}

bool Renderer::loadTextureShader()
{
    Shader* shader = new Shader();

    // シェーダーの設定
    if(!shader->load("../shader/texture.vert",
                     "../shader/texture.frag"))
    {
        return false;
    }

    // uniform の設定
    shader->setActive();
    shader->setUniform("uViewProjection",
                       Shader::MATRIX4,
                       Matrix4::createSimpleViewProjection(Game::SCREEN_WIDTH,
                                                           Game::SCREEN_HEIGHT));

    mShaderMap.emplace(TEXTURE,
                       shader);
}