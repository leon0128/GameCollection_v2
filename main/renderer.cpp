#include "renderer.hpp"
#include "game.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "vertex_array.hpp"
#include "../component/sprite_component.hpp"

Renderer::Renderer(Game* game):
    mShaderMap(),
    mSprites(),
    mTextureMap(),
    mCharTextureMap(),
    mGame(game),
    mWindow(nullptr),
    mContext(),
    mFont(nullptr),
    mSpriteVAO(nullptr)
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
                               static_cast<int>(Game::SCREEN_WIDTH),
                               static_cast<int>(Game::SCREEN_HEIGHT),
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

    // mFont の設定
    mFont = new Font();
    if(!mFont->initialize())
    {
        SDL_Log("Failed to initialize Font");
        return false;
    }

    // mShaderMap の設定
    if(!loadShaders())
    {
        SDL_Log("Failed to load Shaders");
        return false;
    }

    // mSpriteVAO の設定
    loadSpriteVAO();

    return true;
}

void Renderer::finalize()
{
    // Texture の削除
    for(auto& map : mCharTextureMap)
    {
        for(auto& texture : map.second)
        {
            texture.second->unload();
            delete texture.second;
        }
    }
    for(auto& texture : mTextureMap)
    {
        texture.second->unload();
        delete texture.second;
    }

    // フォントの削除
    mFont->finalize();
    delete mFont;

    // mSpriteVAO の削除
    delete mSpriteVAO;

    // mShaderMap の削除
    for(auto& shader : mShaderMap)
    {
        shader.second->unload();
        delete shader.second;
    }

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

    // SpriteVAO の有効化
    mSpriteVAO->setActive();

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

bool Renderer::createTexture(const std::string& filename)
{
    // Texture 作成
    Texture* texture = new Texture();
    if(!texture->load(filename))
        return false;

    // mTextures への挿入
    mTextureMap.emplace(filename,
                        texture);
    
    return true;
}

void Renderer::destroyTexture(const std::string& filename)
{
    auto iterator = mTextureMap.begin();
    for(;
        iterator != mTextureMap.end();
        iterator++)
    {
        if(iterator->first == filename)
            break;
    }

    // Texture を削除するか警告文の表示
    if(iterator != mTextureMap.end())
    {
        iterator->second->unload();
        delete iterator->second;
        mTextureMap.erase(iterator);
    }
    else
    {
        SDL_Log("Cannot find Texture to delete: %s",
                filename.c_str());
    }
}

void Renderer::destoryAllTexture()
{
    for(auto& texture : mTextureMap)
    {
        texture.second->unload();
        delete texture.second;
    }
}

bool Renderer::loadShaders()
{
    if(!loadTextureShader())
        return false;
    
    return true;
}

bool Renderer::loadTextureShader()
{
    Shader* shader = new Shader();

    // シェーダーの設定
    if(!shader->load("shader/texture.vert",
                     "shader/texture.frag"))
    {
        return false;
    }

    // uniform の設定
    shader->setActive();
    Matrix4 simple = Matrix4::createSimpleViewProjection(Game::SCREEN_WIDTH,
                                                         Game::SCREEN_HEIGHT);
    shader->setUniform("uViewProjection",
                       Shader::MATRIX4,
                       &simple);

    mShaderMap.emplace(TEXTURE,
                       shader);
    
    return true;
}

void Renderer::loadSpriteVAO()
{
    float vertices[] = {-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                         0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                         0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
    unsigned int indices[] = {0, 1, 2,
                              2, 3, 0};

    mSpriteVAO = new VertexArray(vertices,
                                 4,
                                 indices,
                                 6);
}