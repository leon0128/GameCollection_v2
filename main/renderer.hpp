#pragma once

#include "font.hpp"
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
    // Texture の取得
    class Texture* getTexture(std::string& filename) const;
    class Texture* getCharTexture(Font::ESize size,
                                  char character) const;

    // mSprites に値の追加
    void addSprite(class SpriteComponent* sprite);
    void removeSprite(class SpriteComponent* sprite);

    // ゲーム切替時に Controller で呼び出す
    bool createTexture(const std::string& filename);
    void destroyTexture(const std::string& filename);
    void destoryAllTexture();

private:
    // initialize() で呼び出す
    bool loadShaders();
    bool loadTextureShader();
    void loadSpriteVAO();

    std::unordered_map<EShader, class Shader*> mShaderMap; // シェーダー
    std::vector<class SpriteComponent*> mSprites;          // スプライト
    std::unordered_map<std::string, class Texture*> mTextureMap; // テクスチャ
    std::unordered_map<Font::ESize, 
                       std::unordered_map<char, class Texture*>> mCharTextureMap; // 文字テクスチャ

    class Game* mGame;             // 所属するGame クラス
    SDL_Window* mWindow;           // ウィンドウ
    SDL_GLContext mContext;        // コンテキスト
    class Font* mFont;             // フォント
    class VertexArray* mSpriteVAO; // Sprite 用のVAO
};