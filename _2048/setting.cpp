#include "setting.hpp"

_2048::Setting::Setting(Controller* controller):
    Actor(controller),
    mVectorMap(),
    mIndicesMap(),
    mSelectedIndex(0)
{
    loadMap();
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
}