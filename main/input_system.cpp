#include "input_system.hpp"
#include "game.hpp"

InputSystem::InputSystem(Game* game):
    mKeyboardState(),
    mGame(game)
{
}

bool InputSystem::initialize()
{
    // mKeyboardStete を適切な大きさに設定
    int size = 0;
    SDL_GetKeyboardState(&size);
    mKeyboardState.resize(size);
    mKeyboardState.shrink_to_fit();

    return true;
}

void InputSystem::input()
{
    // イベント取得
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case(SDL_QUIT):
                mGame->end();
                break;
        }
    }

    updateKeyboardState();
}

void InputSystem::updateKeyboardState()
{
    // キーボードの状態取得
    int size;
    const Uint8* state = SDL_GetKeyboardState(&size);

    // キーボードの大きさが変更された場合は、mKeyboardState の再設定
    if(size != static_cast<int>(mKeyboardState.size()))
    {
        mKeyboardState.clear();
        mKeyboardState.resize(size);
        mKeyboardState.shrink_to_fit();
    }

    // mKeyboardState の更新
    for(int i = 0; i < size; i++)
    {
        if(state[i])
            mKeyboardState.at(i)++;
        else
            mKeyboardState.at(i) = 0;
    }
}