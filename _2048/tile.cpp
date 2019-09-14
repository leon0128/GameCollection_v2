#include "tile.hpp"
#include "../main/controller.hpp"
#include "board.hpp"

const std::unordered_map<int, SDL_Color> _2048::Tile::COLOR_MAP{{ 1, {250, 250, 210, 255}},
                                                                { 2, {245, 222, 179, 255}},
                                                                { 3, {222, 184, 135, 255}},
                                                                { 4, {210, 180, 140, 255}},
                                                                { 5, {240, 230, 140, 255}},
                                                                { 6, {255, 255,   0, 255}},
                                                                { 7, {255, 215,   0, 255}},
                                                                { 8, {255, 165,   0, 255}},
                                                                { 9, {255,  99,  71, 255}},
                                                                {10, {255,  69,   0, 255}},
                                                                {11, {255,   0,   0, 255}},
                                                                {12, {220,  20,  60, 255}},
                                                                {13, {199,  21, 133, 255}},
                                                                {14, {255,  20, 147, 255}},
                                                                {15, {255,   0, 255, 255}},
                                                                {16, {153,  50, 204, 255}},
                                                                {17, {128,   0, 128, 255}},
                                                                {18, {123, 104, 238, 255}},
                                                                {19, { 95, 158, 160, 255}},
                                                                {20, { 32, 178, 170, 255}},
                                                                {21, {  0, 206, 209, 255}},
                                                                {22, {  0, 255, 255, 255}},
                                                                {23, {  0, 255, 121, 255}},
                                                                {24, {  0, 250, 154, 255}},
                                                                {25, {124, 252,   0, 255}},
                                                                {26, { 50, 205,  50, 255}},
                                                                {27, {107, 142,  35, 255}},
                                                                {28, { 70, 130, 180, 255}},
                                                                {29, {176, 196, 232, 255}},
                                                                {30, {248, 248, 255, 255}}};

_2048::Tile::Tile(Controller* controller,
                  Board* owner,
                  int score):
    Actor(controller),
    mOwner(owner),
    mScore(score),
    mRectangle(nullptr),
    mString(nullptr),
    mIsJoined(false)
{
    Vector2 size(owner->getBaseSize().x / owner->getSquared(),
                 owner->getBaseSize().y / owner->getSquared());
    mRectangle = new RectangleComponent(this,
                                        size,
                                        COLOR_MAP.at(score),
                                        30);
    std::string none;
    mString = new StringComponent(this,
                                  none,
                                  Font::SIZE_100);
}

void _2048::Tile::updateActor(float deltaTime)
{
    mIsJoined = false;

    Vector2 position = mOwner->getGridPosition(this);

    mRectangle->setRelativePosition(position);
    mRectangle->setColor(COLOR_MAP.at(mScore));

    mString->setRelativePosition(position);
    mString->setString(std::to_string(static_cast<int>(std::pow(2.0f, mScore))));

    float xScale = mOwner->getBaseSize().x /
                   mOwner->getSquared() / 
                   mString->getSize().x *
                   1.0f;
    float yScale = mOwner->getBaseSize().y /
                   mOwner->getSquared() /
                   mString->getSize().y *
                   1.0f;
    
    mString->setScale((xScale < yScale) ? xScale : yScale);
}