#pragma once

#include "../main/actor.hpp"
#include "../main/controller.hpp"
#include "../component/string_component.hpp"
#include "../component/rectangle_component.hpp"
#include "../component/gamepad_component.hpp"
#include <unordered_map>

namespace _2048
{

class Setting : public Actor
{
public:
    enum EIndices
    {
        NUM_PLAYER,
        BOARD_SIZE,
        MAX_SCORE,
        TIME_LIMIT,

        SIZE
    };

    Setting(Controller* controller);
    ~Setting(){}

    // 各要素の値の取得
    int get(EIndices index) const;

private:
    void updataActor(float deltaTime);

    // メンバ変数のマップに値のロード
    void loadMap();
    // Component の設定
    void loadComponents();

    std::unordered_map<EIndices, std::vector<int>> mVectorMap; // 配列を纏めたマップ
    std::unordered_map<EIndices, int> mIndicesMap; // インデックスを纏めた配列
    std::vector<class StringComponent*> mStrings;  // 属性値のStringComponents

    int mSelectedIndex;
};

};