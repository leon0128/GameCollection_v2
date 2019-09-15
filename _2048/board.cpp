#include "board.hpp"
#include "../main/controller.hpp"
#include "setting.hpp"
#include "tile.hpp"

_2048::Board::Board(Controller* controller):
    Actor(controller),
    mGameState(),
    mSquared(0),
    mBaseSize(),
    mGamepad(nullptr)
{
}

void _2048::Board::initialize(Setting* setting)
{
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
    position.y = getPosition().y -
                 mBaseSize.y / 2.0f +
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
        bool isMoved  = moveTile(vertical, parallel);
        bool isJoined = joinTile(vertical, parallel);

        // mGameState の状態が変わったら generateTile() の実行
        if(isMoved || isJoined)
            generateTile();
    }

    // ゲームオーバーの確認
    if(isGameover())
        SDL_Log("====GAMEOVER====");
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

bool _2048::Board::moveTile(int verticall, int parallel)
{
    return true;
}

bool _2048::Board::joinTile(int vertical, int parallel)
{
    return true;
}

bool _2048::Board::isGameover() const
{
    return true;
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