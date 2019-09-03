#include "game.hpp"

Game::Game():
    mIsLoop(true)
{
}

bool Game::initialize()
{

    return true;
}

void Game::runLoop()
{
    while(mIsLoop)
    {
        input();
        update();
        output();
    }
}

void Game::finalize()
{
    
}

void Game::input()
{

}

void Game::update()
{

}

void Game::output()
{

}