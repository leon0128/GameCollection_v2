#pragma once

class Component
{
public:
    Component(class Actor* actor,
              int order = 100);
    virtual ~Component(){}

    // Actor::update() で呼び出す
    virtual void update(float deltaTime){}

    // メンバ変数の取得
    int getOrder() const {return mOrder;}

protected:
    class Actor* getActor() const {return mActor;}

private:
    class Actor* mActor; // 自身の所属するActor
    int mOrder;          // Component の更新順序
};