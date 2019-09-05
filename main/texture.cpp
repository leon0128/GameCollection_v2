#include "texture.hpp"

Texture::Texture():
    mID(0),
    mSize()
{
}

bool Texture::load(const std::string& filename)
{


    return true;
}

bool Texture::loadImage(const std::string& filename,
                        unsigned char* image,
                        int* format)
{
    int channels = 0;
    int width = 0, height = 0;

    // 画像のロード
    image = SOIL_load_image(filename.c_str(),
                            &width,
                            &height,
                            &channels,
                            SOIL_LOAD_AUTO);
    if(!image)
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