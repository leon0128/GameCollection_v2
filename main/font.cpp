#include "font.hpp"

Font::Font():
    mFontMap()
{
}

bool Font::initialize()
{
    // SDL_TTF の初期化
    TTF_Init();

    char filename[] = "font/Hack-Regular.ttf";
    ESize sizes[] = {SIZE_8, SIZE_12, SIZE_16, SIZE_20,
                     SIZE_30, SIZE_40, SIZE_50, SIZE_60,
                     SIZE_80, SIZE_100};
    for(ESize size : sizes)
    {
        mFontMap.emplace(size,
                         TTF_OpenFont(filename,
                                      size));
    }

    return true;
}

void Font::finalize()
{
    for(auto& pair : mFontMap)
    {
        TTF_CloseFont(pair.second);
    }
    TTF_Quit();
}

SDL_Surface* Font::getCharSurface(char character,
                                  ESize size)
{
    SDL_Color black = {0, 0, 0, 255};
    char c[] = {character, '\0'};

    SDL_Surface* surface = TTF_RenderUTF8_Blended(mFontMap.at(size),
                                                  c,
                                                  black);
    if(!surface)
    {
        SDL_Log("SDL_Surface creation falied: %s",
                TTF_GetError());
        return nullptr;
    }

    return surface;
}