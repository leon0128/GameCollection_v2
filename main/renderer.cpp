#include "renderer.hpp"

#include "game.hpp"

Renderer::Renderer(Game* game):
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

    
    // バッファ入れ替え
    SDL_GL_SwapWindow(mWindow);
}