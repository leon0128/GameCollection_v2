#pragma once

class InputSystem
{
public:
    InputSystem(class Game* game);
    ~InputSystem(){}

private:
    class Game* mGame; // 所属するGameクラス
};