#pragma once

// 2次元の整数値座標
class Coordinate2
{
public:
    int x; // X軸
    int y; // Y軸

    // コンストラクタ
    Coordinate2();
    explicit Coordinate2(int inX, int inY);

    // 値の設定
    void set(int inX, int inY);
};