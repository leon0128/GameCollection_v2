#pragma once

#include <cmath>

// 2次元の整数値座標
class Coordinate2
{
public:
    int x; // X軸
    int y; // Y軸

    // コンストラクタ
    Coordinate2();
    Coordinate2(int inX, int inY);

    // 値の設定
    void set(int inX, int inY);
};

// 2次元ベクトル
class Vector2
{
public:
    float x; // X軸
    float y; // Y軸
    
    // 定数
    static const Vector2 ZERO;
    static const Vector2 UNIT_X;
    static const Vector2 UNIT_Y;
    static const Vector2 NEGATIVE_UNIT_X;
    static const Vector2 NEGATIVE_UNIT_Y;

    // コンストラクタ
    Vector2();
    Vector2(float inX, float inY);

    // 値の設定
    void set(float inX, float inY);
    // Vector2をfloat*にキャスト(openGLで使用)
    const float* getAsFloatPointer() const;
    // 長さの2乗
    float lengthSquared() const;
    // 長さ
    float length() const;
    // 正規化
    void normalize();
    
    // 正規化
    static Vector2 normalize(const Vector2& inVector);
    // ドット積
    static float dot(const Vector2& lhs,
                     const Vector2& rhs);

    // 演算
    friend Vector2 operator+(const Vector2& lhs,
                             const Vector2& rhs);
    friend Vector2 operator-(const Vector2& lhs,
                             const Vector2& rhs);
    friend Vector2 operator*(const Vector2& lhs,
                             const Vector2& rhs);
    friend Vector2 operator*(const Vector2& inVector,
                             float scalar);
    friend Vector2 operator*(float scalar,
                             const Vector2& inVector);
    Vector2& operator+=(const Vector2& rhs);
    Vector2& operator-=(const Vector2& rhs);
    Vector2& operator*=(float scalar);
};