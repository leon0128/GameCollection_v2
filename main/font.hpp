#pragma once

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <unordered_map>

class Font
{
public:

    // フォントの大きさ
    enum ESize
    {
        SIZE_8  = 8,
        SIZE_12 = 12,
        SIZE_16 = 16,
        SIZE_20 = 20,
        SIZE_30 = 30,
        SIZE_40 = 40,
        SIZE_50 = 50,
        SIZE_60 = 60,
        SIZE_80 = 80,
        SIZE_100 = 100
    };

    Font();
    ~Font(){}

    bool initialize();
    void finalize();

    SDL_Surface* getCharSurface(char character,
                                ESize size);

private:
    std::unordered_map<ESize, TTF_Font*> mFontMap; // 作成したフォントのMap
};