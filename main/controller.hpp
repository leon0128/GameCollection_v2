#pragma once

class Controller
{
public:
    Controller(class Game* game);
    ~Controller(){}

    bool initialize();

    void update();

private:
    class Game* mGame; // 自身が所属するGameクラス
};