#include "board.hpp"
#include "../main/controller.hpp"
#include "setting.hpp"
#include "tile.hpp"

_2048::Board::Board(Controller* controller):
    Actor(controller),
    mGameState(),
    mState(NONE),
    mTimeLimit(0),
    mGoalScore(0),
    mSquared(0),
    mElapsedTime(0.0f),
    mBaseSize(),
    mGamepad(nullptr)
{
}

void _2048::Board::initialize(Setting* setting)
{
    mTimeLimit = setting->get(Setting::TIME_LIMIT);
    mGoalScore = setting->get(Setting::MAX_SCORE);

    loadBoard(setting);
    mGamepad = new GamepadComponent(this);
    mGameState = std::vector<Tile*>(mSquared * mSquared,
                                    nullptr);
    
    generateTile();
    generateTile();
}

Vector2 _2048::Board::getGridPosition(Tile* tile) const
{
    // mGameState 内の tile の取得
    size_t index = mGameState.size();
    for(size_t i = 0; i < mGameState.size(); i++)
    {
        if(mGameState.at(i) == tile)
        {
            index = i;
            break;
        }
    }
    if(index == mGameState.size())
    {
        SDL_Log("The specified Tile does not exist");
        return Vector2(0.0f, 0.0f);
    }

    Vector2 position;
    // x
    position.x = getPosition().x -
                 mBaseSize.x / 2.0f +
                 mBaseSize.x / mSquared * (0.5f + index % mSquared);
    // y
    position.y = getPosition().y +
                 mBaseSize.y / 2.0f -
                 mBaseSize.y / mSquared * (0.5f + static_cast<int>(index / mSquared));

    return position;
}

void _2048::Board::updateActor(float deltaTime)
{
    // 水平方向と垂直方向の移動
    int vertical = 0, parallel = 0;

    if(input(vertical, parallel))
    {
        // 移動と結合の実行
        bool isFirMoved = moveTile(vertical, parallel);
        bool isJoined   = joinTile(vertical, parallel);
        bool isSecMoved = moveTile(vertical, parallel);

        // ゲームクリアの確認
        if(isJoined)
        {
            if(isGameclear())
                end(CLEAR);
        }

        // mGameState の状態が変わったら generateTile() の実行
        if(isFirMoved || isSecMoved || isJoined)
        {
            generateTile();
            if(isGameover())
                end(GAMEOVER);
        }
    }

    if(isTimeUp(deltaTime))
        end(TIMEUP);
}

void _2048::Board::loadBoard(Setting* setting)
{
    SDL_Color baseColor  = {55, 55, 55, 255};
    SDL_Color frameColor = {150, 150, 150, 255};

    // 大きさの設定
    Vector2 size(500.0f, 500.0f);
    if(setting->get(Setting::NUM_PLAYER) == 2)
        size.set(450.0f, 450.0f);
    
    mBaseSize = size;

    // 基盤の矩形の作成
    new RectangleComponent(this,
                           mBaseSize,
                           baseColor,
                           10);

    // 枠の作成
    mSquared = setting->get(Setting::BOARD_SIZE);
    float width = mBaseSize.x / 400.0f * (45.0f / mSquared - 2.5f);
    float space = mBaseSize.x / mSquared;
    Vector2 temp;
    for(int i = 0; i < mSquared + 1; i++)
    {
        // 平行な枠
        temp.set(mBaseSize.x, width);
        RectangleComponent* parallel = new RectangleComponent(this,
                                                               temp,
                                                               frameColor,
                                                               80);
        temp.set(0.0f, space * i - mBaseSize.x / 2.0f);
        parallel->setRelativePosition(temp);

        // 垂直な枠
        temp.set(width, mBaseSize.y);
        RectangleComponent* vertical = new RectangleComponent(this,
                                                              temp,
                                                              frameColor,
                                                              80);
        temp.set(space * i - size.x / 2.0f, 0.0f);
        vertical->setRelativePosition(temp);
    }
}

bool _2048::Board::input(int& vertical, int& parallel) const
{
    if(mGamepad->at(GamepadComponent::BUTTON_UP) == 1)
        vertical++;
    if(mGamepad->at(GamepadComponent::BUTTON_DOWN) == 1)
        vertical--;
    if(mGamepad->at(GamepadComponent::BUTTON_RIGHT) == 1)
        parallel++;
    if(mGamepad->at(GamepadComponent::BUTTON_LEFT) == 1)
        parallel--;
    
    if((vertical != 0 && parallel != 0) ||
       (vertical == 0 && parallel == 0))
        return false;

    return true;
}

bool _2048::Board::moveTile(int vertical, int parallel)
{
    // 変化前
    std::vector<bool> lastState(mSquared * mSquared,
                                false);
    for(size_t i = 0; i < mGameState.size(); i++)
        lastState.at(i) = mGameState.at(i) ? true : false;

    for(int i = 0; i < mSquared; i++)
    {
        int numEmpty = 0;
        for(int j = 0; j < mSquared; j++)
        {
            size_t index = 0;
            int diff = 0;
            if(vertical == 1)
                index = mSquared * j + i,
                diff = -1 * mSquared;
            else if(vertical == -1)
                index = mSquared * mSquared - 1 - mSquared * j - i,
                diff = mSquared;
            else if(parallel == 1)
                index = mSquared * mSquared - 1 - j - i * mSquared,
                diff = 1;
            else if(parallel == -1)
                index = j + i * mSquared,
                diff = -1;

            if(mGameState.at(index))
                std::iter_swap(mGameState.begin() + index,
                               mGameState.begin() + index + diff * numEmpty);
            else
                numEmpty++;
        }
    }

    for(size_t i = 0; i < mGameState.size(); i++)
    {
        if((mGameState.at(i) && !lastState.at(i)) ||
           (!mGameState.at(i) && lastState.at(i)))
            return true;
    }
    
    return false;
}

bool _2048::Board::joinTile(int vertical, int parallel)
{
    bool isJoined = false;

    for(int i = 0; i < mSquared; i++)
    {
        for(int j = 0; j < mSquared - 1; j++)
        {
            size_t index = 0;
            int diff = 0;
            if(vertical == 1)
                index = mSquared * j + i,
                diff = mSquared;
            else if(vertical == -1)
                index = mSquared * mSquared - 1 - mSquared * j - i,
                diff = -1 * mSquared;
            else if(parallel == 1)
                index = mSquared * mSquared - 1 - j - i * mSquared,
                diff = -1;
            else if(parallel == -1)
                index = j + i * mSquared,
                diff = 1;

            if(!mGameState.at(index) ||
               !mGameState.at(index + diff))
                continue;

            if((!mGameState.at(index)->isJoined() &&
                !mGameState.at(index + diff)->isJoined()) &&
               (mGameState.at(index)->getScore() == 
                mGameState.at(index + diff)->getScore()))
            {
                mGameState.at(index)->join();
                mGameState.at(index + diff)->setState(Actor::DEAD);
                mGameState.at(index + diff) = nullptr;

                isJoined = true;
            }
        }
    }

    return isJoined;
}

bool _2048::Board::isGameclear() const
{
    for(auto& tile : mGameState)
    {
        if(tile)
        {
            if(tile->getScore() == mGoalScore)
                return true;
        }
    }

    return false;
}

bool _2048::Board::isGameover() const
{
    for(int i = 0; i < mSquared; i++)
    {
        int parScore = 0;
        int verScore = 0;
        for(int j = 0; j < mSquared; j++)
        {
            if(!mGameState.at(i * mSquared + j))
                return false;
            if(mGameState.at(i * mSquared + j)->getScore() == verScore)
                return false;

            verScore = mGameState.at(i * mSquared + j)->getScore();

            if(!mGameState.at(i + mSquared * j))
                return false;
            if(mGameState.at(i + mSquared * j)->getScore() == parScore)
                return false;

            parScore = mGameState.at(i + mSquared * j)->getScore();
        }
    }

    return true;
}

bool _2048::Board::isTimeUp(float deltaTime)
{
    if(mTimeLimit == 0)
        return false;

    if(static_cast<int>(mElapsedTime) > mTimeLimit)
        return true;
    
    mElapsedTime += deltaTime;
    return false;
}

bool _2048::Board::generateTile()
{
    // 空いている位置の調査
    std::vector<size_t> emptyCellIndices;
    for(size_t i = 0; i < mGameState.size(); i++)
    {
        if(!mGameState.at(i))
            emptyCellIndices.emplace_back(i);
    }
    if(emptyCellIndices.empty())
        return false;
    
    // ランダムな位置に Tile の作成
    int index = Random::RANDOM(emptyCellIndices.size());
    int score = (Random::RANDOM(10) % 9 != 0) ? 1 : 2;
    mGameState.at(emptyCellIndices.at(index)) = new Tile(getController(), 
                                                         this,
                                                         score);

    return true;
}

void _2048::Board::end(EState state)
{
    mState = state;

    SDL_Color filmColor;
    SDL_Color messageColor;
    std::string filmMessage;

    switch(state)
    {
        case(CLEAR):
            filmColor = {255, 255, 255, 200};
            messageColor = {255, 140, 0, 255};
            filmMessage = "CLEAR";
            break;
        case(GAMEOVER):
            filmColor = {0, 0, 0, 200};
            messageColor = {255, 255, 255, 255};
            filmMessage = "GAMEOVER";
            break;
        case(TIMEUP):
            filmColor = {0, 0, 0, 200};
            messageColor = {255, 255, 255, 255};
            filmMessage = "TIME UP";
            break;
    }

    new RectangleComponent(this,
                           mBaseSize,
                           filmColor,
                           130);
    new StringComponent(this,
                        filmMessage,
                        Font::SIZE_100,
                        150);
    StringComponent* string = new StringComponent(this,
                                                  filmMessage,
                                                  Font::SIZE_100,
                                                  150);
    string->setColor(messageColor);

    setState(Actor::EState::PAUSED);
}