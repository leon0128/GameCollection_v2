#include "setting.hpp"

_2048::Setting::Setting(Controller* controller):
    Actor(controller),
    mVectorMap(),
    mIndicesMap(),
    mStrings(),
    mGamepad(nullptr),
    mSelectedIndex(0),
    mIsCompleted(false),
    mIsStarted(true)
{
    loadMap();
    loadComponents();
    mSelectedIndex = SIZE;
}

int _2048::Setting::get(EIndices index) const
{
    auto& vector = mVectorMap.at(index);
    
    size_t i = mIndicesMap.at(index) % vector.size();

    return vector.at(i);
}

void _2048::Setting::updateActor(float deltaTime)
{
    if(mIsCompleted)
        return;

    input();
    updateStrings();

    if(mIsCompleted)
    {
        mStrings.clear();
        mGamepad = nullptr;
        clearComponent();
    }
    mIsStarted = false;
}

void _2048::Setting::input()
{
    // 上下左右の移動を示す
    int vertical = 0, parallel = 0;
    // 設定完了か
    bool isCompleted = false;

    // mGamepad で上記の値の変更
    if(mGamepad->at(GamepadComponent::BUTTON_UP) == 1)
        vertical--;
    if(mGamepad->at(GamepadComponent::BUTTON_DOWN) == 1)
        vertical++;
    if(mGamepad->at(GamepadComponent::BUTTON_LEFT) == 1)
        parallel--;
    if(mGamepad->at(GamepadComponent::BUTTON_RIGHT) == 1)
        parallel++;
    
    if(mGamepad->at(GamepadComponent::BUTTON_START) == 1 &&
       !mIsStarted)
        isCompleted = true;
    
    // 項目の設定
    mSelectedIndex += vertical;
    mSelectedIndex = (mSelectedIndex < 0) ? static_cast<int>(mStrings.size()) - 1 : mSelectedIndex;

    // 値の設定
    EIndices index = static_cast<EIndices>(mSelectedIndex % mStrings.size());
    if(index != SIZE)
    {
        int i = mIndicesMap.at(index) + parallel;
        i = (mIndicesMap.at(index) < 0) ? static_cast<int>(mVectorMap.at(index).size() - 1) : i;
        mIndicesMap.at(index) = i;
    }
    else if(isCompleted)
    {
        mIsCompleted = true;
    }
}

void _2048::Setting::updateStrings()
{
    EIndices index = static_cast<EIndices>(mSelectedIndex % mStrings.size());
    switch(index)
    {
        case(NUM_PLAYER):
        {
            std::string numPlayer = std::to_string(get(index));
            mStrings.at(index)->setString(numPlayer + " player");
            break;
        }
        case(BOARD_SIZE):
        {
            std::string boardSize = std::to_string(get(index));
            mStrings.at(index)->setString(boardSize + " * " + boardSize);
            break;
        }
        case(MAX_SCORE):
        {
            std::string maxScore;
            if(get(index) != 0)
                maxScore = std::to_string(static_cast<int>(std::pow(2.0f, get(MAX_SCORE))));
            else
                maxScore = "--";

            mStrings.at(index)->setString(maxScore + " points");
            break;
        }
        case(TIME_LIMIT):
        {
            std::string limitTime;
            if(get(index) != 0)
                limitTime = std::to_string(get(index));
            else
                limitTime = "--";

            mStrings.at(index)->setString(limitTime + " seconds");
            break;
        }
        case(SIZE):
            break;
    }

    // 背景色の初期化
    SDL_Color clear = {0, 0, 0, 0};
    SDL_Color gray = {100, 100, 100, 255};
    for(auto& string : mStrings)
        string->setBackGroundColor(clear);
    mStrings.at(index)->setBackGroundColor(gray);
}

void _2048::Setting::loadMap()
{
    EIndices indices[] = {NUM_PLAYER, BOARD_SIZE,
                          MAX_SCORE, TIME_LIMIT};

    // 各項目の値
    std::vector<int> numPlayer = {1, 2};
    std::vector<int> boardSize = {2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> maxScore  = {0, 4, 6, 8, 10, 11, 12, 13, 15, 17, 20, 24, 28, 30};
    std::vector<int> limitTime = {0, 30, 60, 90, 120, 180, 300, 600};

    mVectorMap.emplace(NUM_PLAYER,
                       numPlayer);
    mVectorMap.emplace(BOARD_SIZE,
                       boardSize);
    mVectorMap.emplace(MAX_SCORE,
                       maxScore);
    mVectorMap.emplace(TIME_LIMIT,
                       limitTime);

    for(auto index : indices)
        mIndicesMap.emplace(index, 0);

    mIndicesMap.at(BOARD_SIZE) = 2;
    mIndicesMap.at(MAX_SCORE)  = 0;
    mIndicesMap.at(TIME_LIMIT) = 0;
}

void _2048::Setting::loadComponents()
{
    SDL_Color bgColor = {0, 0, 0, 200};
    SDL_Color titleColor = {220, 220, 220, 255};
    SDL_Color strColor = {255, 255, 255, 255};
    Vector2 bgSize(500, 300);

    Font::ESize titleFont = Font::SIZE_50;
    Font::ESize attriFont = Font::SIZE_30;

    float titleSpace = 80.0f;
    float attriSpace = 45.0f;

    std::vector<std::pair<std::string, std::string>> outputString;
    outputString.emplace_back("Num Player",
                              std::to_string(get(NUM_PLAYER)) + " player");
    outputString.emplace_back("Board Size",
                              std::to_string(get(BOARD_SIZE)) + " * " + std::to_string(get(BOARD_SIZE)));
    outputString.emplace_back("Max Score",
                              "-- points");
    outputString.emplace_back("Time Limit",
                              "-- seconds");

    // 背景の矩形
    new RectangleComponent(this,
                           bgSize,
                           bgColor,
                           10);
    // "Setting"
    std::string setting("Setting");
    Vector2 settingPos(0.0f, bgSize.y / 2.0f - static_cast<int>(attriFont));
    StringComponent* title = new StringComponent(this,
                                 setting,
                                 titleFont);
    title->setPosition(settingPos);
    title->setColor(titleColor);

    // 属性、属性値
    for(size_t i = 0; i < outputString.size(); i++)
    {
        Vector2 position(bgSize.x / (-3.5f),
                         bgSize.y / 2.0f - attriSpace * i - titleSpace);

        StringComponent* string = new StringComponent(this,
                                                      outputString.at(i).first);
        string->setPosition(position);
        string->setColor(strColor);

        position.x = bgSize.x / 4.0f;
        mStrings.emplace_back(new StringComponent(this,
                                                  outputString.at(i).second));
        mStrings.at(i)->setPosition(position);
        mStrings.at(i)->setColor(strColor);
    }

    // "Game Start"
    std::string start("Game Start");
    SDL_Color littleRed = {255, 150, 150, 255};
    Vector2 startPos(0.0f,
                     bgSize.y / 2.0f - attriSpace * mStrings.size() - titleSpace);
    mStrings.emplace_back(new StringComponent(this,
                                              start));
    mStrings.back()->setColor(littleRed);
    mStrings.back()->setPosition(startPos);

    // mGamepad の設定
    mGamepad = new GamepadComponent(this);
    mGamepad->addKeyboardMap(GamepadComponent::BUTTON_DOWN,
                             SDL_SCANCODE_DOWN);
    mGamepad->addKeyboardMap(GamepadComponent::BUTTON_DOWN,
                             SDL_SCANCODE_S);
    mGamepad->addKeyboardMap(GamepadComponent::BUTTON_UP,
                             SDL_SCANCODE_UP);
    mGamepad->addKeyboardMap(GamepadComponent::BUTTON_UP,
                             SDL_SCANCODE_W);
    mGamepad->addKeyboardMap(GamepadComponent::BUTTON_LEFT,
                             SDL_SCANCODE_LEFT);
    mGamepad->addKeyboardMap(GamepadComponent::BUTTON_LEFT,
                             SDL_SCANCODE_A);
    mGamepad->addKeyboardMap(GamepadComponent::BUTTON_RIGHT,
                             SDL_SCANCODE_RIGHT);
    mGamepad->addKeyboardMap(GamepadComponent::BUTTON_RIGHT,
                             SDL_SCANCODE_D);
    mGamepad->addKeyboardMap(GamepadComponent::BUTTON_START,
                             SDL_SCANCODE_SPACE);
}