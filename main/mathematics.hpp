#pragma once

#include <cmath>
#include <cstring>

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

// 3次元ベクトル
class Vector3
{
public:
    float x; // X軸
    float y; // Y軸
    float z; // Z軸

    // 定数
    static const Vector3 ZERO;
    static const Vector3 UNIT_X;
    static const Vector3 UNIT_Y;
    static const Vector3 UNIT_Z;
    static const Vector3 NEGATIVE_UNIT_X;
    static const Vector3 NEGATIVE_UNIT_Y;
    static const Vector3 NEGATIVE_UNIT_Z;

    // コンストラクタ
    Vector3();
    Vector3(float inX, float inY, float inZ);

    // 値の設定
    void set(float inX, float inY, float inZ);
    // Vector3をfloat* にキャスト(openGL で使用)
    const float* getAsFloatPointer() const;
    // 長さの2乗
    float lengthSquared() const;
    // 長さ
    float length() const;
    // 正規化
    void normalize();

    // 正規化
    static Vector3 normalize(const Vector3& inVector);
    // ドット積
    static float dot(const Vector3& lhs,
                     const Vector3& rhs);
    // クロス積
    static Vector3 cross(const Vector3& lhs,
                         const Vector3& rhs);
    
    // 演算
    friend Vector3 operator+(const Vector3& lhs,
                             const Vector3& rhs);
    friend Vector3 operator-(const Vector3& lhs,
                             const Vector3& rhs);
    friend Vector3 operator*(const Vector3& lhs,
                             const Vector3& rhs);
    friend Vector3 operator*(const Vector3& inVector,
                             float scalar);
    friend Vector3 operator*(float scalar,
                             const Vector3& inVector);
    Vector3& operator+=(const Vector3& rhs);
    Vector3& operator-=(const Vector3& rhs);
    Vector3& operator*=(float scalar);
};

// 4 * 4 行列
class Matrix4
{
public:
    float mat[4][4]; // 4 * 4 行列
    
    // 定数
    static const Matrix4 IDENTITY;

    // コンストラクタ
    Matrix4();
    explicit Matrix4(float inMat[4][4]);

    // Matrix4 を float* にキャスト(openGL で使用)
    const float* getAsFloatPointer() const;

    // スケール変換行列
    static Matrix4 createScale(float xScalar,
                               float yScalar,
                               float zScalar);
    static Matrix4 createScale(const Vector3& inVector);
    static Matrix4 createScale(float scalar);
    // X軸回転変換行列
    static Matrix4 createRotationX(float theta);
    // Y軸回転変換行列
    static Matrix4 createRotationY(float theta);
    // Z軸観点変換行列
    static Matrix4 createRotationZ(float theta);
    // 回転を表す Quaternion から Matrix4 に変換
    static Matrix4 createFromQuaternion(const class Quaternion& quaternion);
    // 平行移動変換行列
    static Matrix4 createTranslation(const Vector3& translation);
    // 2次元のワールド空間からクリップ空間への変換行列
    static Matrix4 createSimpleViewProjection(float width, float height);
};

class Quaternion
{
public:
    float x; // Vector成分
    float y; // Vector成分
    float z; // Vector成分
    float w; // スカラー成分
    
    // 定数
    static const Quaternion IDENTITY;

    // コンストラクタ
    Quaternion();
    Quaternion(float inX, float inY, float inZ, float inW);
    Quaternion(const Vector3& axis, float theta);

    // 値の設定
    void set(float inX, float inY, float inZ, float inW);
};