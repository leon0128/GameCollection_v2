#include "_2048.hpp"
#include "../main/game.hpp"
#include "../main/controller.hpp"
#include "setting.hpp"
#include "board.hpp"

_2048::_2048::_2048(Controller* controller):
    Actor(controller),
    mBoards(),
    mSetting(nullptr),
    mIsInitialized(false)
{
    mSetting = new Setting(controller);
}

void _2048::_2048::updateActor(float deltaTime)
{
    if(!mSetting->isCompleted())
        return;
    
    if(!mIsInitialized)
        initialize();
}

void _2048::_2048::initialize()
{
    switch(mSetting->get(Setting::NUM_PLAYER))
    {
        case(1):
        {
            mBoards.emplace_back(new Board(getController()));
            mBoards.front()->initialize(mSetting);
            break;
        }
        case(2):
        {
            for(int i = 0; i < 2; i++)
            {
                mBoards.emplace_back(new Board(getController()));
                Vector3 position((std::pow(-1.0f, i + 1)) * Game::SCREEN_WIDTH / 4.0f,
                                 0.0f,
                                 0.0f);
                mBoards.back()->setPosition(position);
                mBoards.back()->initialize(mSetting);
            }
            break;
        }
        default:
            SDL_Log("Invalid number of players: %d",
                    mSetting->get(Setting::NUM_PLAYER));
    }

    // Board::mGamepad の設定
    GamepadComponent* gamepad = mBoards.front()->getGamepad();
    gamepad->addKeyboardMap(GamepadComponent::BUTTON_UP,
                            SDL_SCANCODE_W);
    gamepad->addKeyboardMap(GamepadComponent::BUTTON_DOWN,
                            SDL_SCANCODE_S);
    gamepad->addKeyboardMap(GamepadComponent::BUTTON_LEFT,
                            SDL_SCANCODE_A);
    gamepad->addKeyboardMap(GamepadComponent::BUTTON_RIGHT,
                            SDL_SCANCODE_D);
    gamepad->addKeyboardMap(GamepadComponent::BUTTON_HOME,
                            SDL_SCANCODE_SPACE);
    
    gamepad = mBoards.back()->getGamepad();
    gamepad->addKeyboardMap(GamepadComponent::BUTTON_UP,
                            SDL_SCANCODE_UP);
    gamepad->addKeyboardMap(GamepadComponent::BUTTON_DOWN,
                            SDL_SCANCODE_DOWN);
    gamepad->addKeyboardMap(GamepadComponent::BUTTON_LEFT,
                            SDL_SCANCODE_LEFT);
    gamepad->addKeyboardMap(GamepadComponent::BUTTON_RIGHT,
                            SDL_SCANCODE_RIGHT);
    gamepad->addKeyboardMap(GamepadComponent::BUTTON_HOME,
                            SDL_SCANCODE_SPACE);

    mIsInitialized = true;
}