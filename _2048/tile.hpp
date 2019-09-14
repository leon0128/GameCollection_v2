#pragma once

#include "../main/actor.hpp"
#include "../component/rectangle_component.hpp"
#include "../component/string_component.hpp"

namespace _2048
{

class Tile : public Actor
{
public:
    // タイルの色
    static const std::unordered_map<int, SDL_Color> COLOR_MAP;

    Tile(class Controller* controller,
         class Board* owner,
         int score);
    ~Tile(){}

    // mScore を +1, mIsJoined を true
    void join(){mScore++; 
                mIsJoined = true;}
    
    // メンバ変数の取得
    int getScore() const {return mScore;}
    bool isJoined() const {return mIsJoined;}

private:
    void updateActor(float deltaTime) override;

    class Board* mOwner; // 所属する Baord
    int mScore;          // 指数
    RectangleComponent* mRectangle; // 矩形
    StringComponent* mString;       // 文字

    bool mIsJoined; // フレーム内で結合したか
};

};