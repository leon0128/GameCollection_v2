#pragma once

#include "mathematics.hpp"
#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <string>

class Texture
{
public:
    Texture();
    ~Texture(){};

    // テクスチャをopenGLにロード、アンロード
    bool load(const std::string& filename);
    void unload();
    // SDL_Surfase から Texture の作成
    void createFromSurface(SDL_Surface* surface);

    // Texture の有効化
    void setActive();

    // メンバ変数の取得
    const Vector2& getSize() const {return mSize;}

private:
    // load() で呼び出す
    bool loadImage(const std::string& filename,
                   unsigned char* image,
                   int* format);

    GLuint mID;    // Texture の openGL ID
    Vector2 mSize; // Texture の大きさ 
};