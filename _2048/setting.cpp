#include "setting.hpp"

_2048::Setting::Setting(Controller* controller):
    Actor(controller),
    mVectorMap(),
    mIndicesMap(),
    mStrings(),
    mSelectedIndex(0)
{
    loadMap();
    loadComponents();
}

int _2048::Setting::get(EIndices index) const
{
    auto& vector = mVectorMap.at(index);
    
    size_t i = mIndicesMap.at(index) % vector.size();

    return vector.at(i);
}

void _2048::Setting::loadMap()
{
    EIndices indices[] = {NUM_PLAYER, BOARD_SIZE,
                          MAX_SCORE, TIME_LIMIT};

    // 各項目の値
    std::vector<int> numPlayer = {1, 2};
    std::vector<int> boardSize = {2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> maxScore  = {0, 4, 6, 8, 10, 11, 12, 13, 15, 17, 20, 24, 28, 32};
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
    mIndicesMap.at(MAX_SCORE)  = 5;
    mIndicesMap.at(TIME_LIMIT) = 5;
}

void _2048::Setting::loadComponents()
{
    SDL_Color bgColor = {0, 0, 0, 200};
    SDL_Color titleColor = {220, 220, 220, 255};
    SDL_Color strColor = {255, 255, 255, 255};
    Vector2 bgSize(400, 300);

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
                              std::to_string(static_cast<int>(std::pow(2.0f, get(MAX_SCORE)))) + " points");
    outputString.emplace_back("Time Limit",
                              std::to_string(get(TIME_LIMIT)) + " seconds");

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
    title->setRelativePosition(settingPos);
    title->setColor(strColor);

    // 属性、属性値
    for(size_t i = 0; i < outputString.size(); i++)
    {
        Vector2 position(bgSize.x / (-4.0f),
                         bgSize.y / 2.0f - attriSpace * i - titleSpace);

        StringComponent* string = new StringComponent(this,
                                                      outputString.at(i).first);
        string->setRelativePosition(position);
        string->setColor(strColor);

        position.x = bgSize.x / 4.0f;
        mStrings.emplace_back(new StringComponent(this,
                                                  outputString.at(i).second));
        mStrings.at(i)->setRelativePosition(position);
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
    mStrings.back()->setRelativePosition(startPos);
}