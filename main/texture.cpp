#include "texture.hpp"

Texture::Texture():
    mTextureID(0),
    mSize()
{
}

bool Texture::load(const std::string& filename)
{
    unsigned char* image = nullptr;
    int format = 0;

    // 画像のロード
    if(!loadImage(filename,
                  &image,
                  &format))
    {
        return false;
    }

    // 画像をopenGLに渡す
    loadFromImage(&image,
                  &format);

    return true;
}

void Texture::unload()
{
    glDeleteTextures(1,
                     &mTextureID);
}

void Texture::loadFromSurface(SDL_Surface* surface)
{
    // mSize の設定
    mSize.x = surface->w;
    mSize.y = surface->h;

    // openGL Texture の作成
    glGenTextures(1,
                  &mTextureID);
    glBindTexture(GL_TEXTURE_2D,
                  mTextureID);
    
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 mSize.x,
                 mSize.y,
                 0,
                 GL_BGRA,
                 GL_UNSIGNED_BYTE,
                 surface->pixels);
    
    // バイリニアフィルタリングの有効化
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER,
                    GL_LINEAR);
    
    // Surface の開放
    SDL_FreeSurface(surface);
}

void Texture::setActive()
{
    glBindTexture(GL_TEXTURE_2D,
                  mTextureID);
}

bool Texture::loadImage(const std::string& filename,
                        unsigned char** image,
                        int* format)
{
    int channels = 0;
    int width = 0, height = 0;

    // 画像のロード
    *image = SOIL_load_image(filename.c_str(),
                             &width,
                             &height,
                             &channels,
                             SOIL_LOAD_AUTO);
    if(!*image)
    {
        SDL_Log("Failed to load image for %s: %s",
                filename.c_str(),
                SOIL_last_result());
        return false;
    }

    // 取得した値を元に設定
    mSize.x = static_cast<float>(width);
    mSize.y = static_cast<float>(height);
    *format = (channels == 4) ? GL_RGBA : GL_RGB;

    return true;
}

void Texture::loadFromImage(unsigned char** image,
                            int* format)
{
    // openGL Texture オブジェクトを作成し、アクティブ化
    glGenTextures(1,
                  &mTextureID);
    glBindTexture(GL_TEXTURE_2D,
                  mTextureID);
    
    // 画像データのコピー
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 *format,
                 mSize.x,
                 mSize.y,
                 0,
                 *format,
                 GL_UNSIGNED_BYTE,
                 *image);
    
    // image の開放
    SOIL_free_image_data(*image);

    // バイリニアフィルタリングを有効化
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER,
                    GL_LINEAR);
}