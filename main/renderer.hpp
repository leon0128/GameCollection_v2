#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <vector>
#include <unordered_map>

class Renderer
{
public:
    // Shader 列挙体
    enum EShader
    {
        TEXTURE,
        RECTANGLE,
        STRING
    };

    Renderer(class Game* game);
    ~Renderer(){}

    // Game::initialize() finalize() で呼び出す
    bool initialize();
    void finalize();

    // Game::output() で呼び出す
    void draw();

    // Shader の取得
    class Shader* getShader(EShader shader) const;

    // mSprites に値の追加
    void addSprite(class SpriteComponent* sprite);
    void removeSprite(class SpriteComponent* sprite);

private:
    std::unordered_map<EShader, class Shader*> mShaderMap; // シェーダー
    std::vector<class SpriteComponent*> mSprites;          // スプライト


    class Game* mGame;      // 所属するGame クラス
    SDL_Window* mWindow;    // ウィンドウ
    SDL_GLContext mContext; // コンテキスト
};