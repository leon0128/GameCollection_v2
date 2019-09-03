#pragma once

#include <cstring>
#include <cmath>

// 二次元ベクトル
class Vector2
{
public:
    float x; // x座標
    float y; // y座標

    // コンストラクタ
    // {0.0f, 0.0f} で初期化
    Vector2();
    // 引数の値で初期化
    explicit Vector2(const float argX,
                     const float argY);
    
    // 引数の値をメンバ変数に設定
    void set(const float argX,
             const float argY);

    // 加減算
    friend Vector2 operator+(const Vector2& lhs,
                             const Vector2& rhs);
    friend Vector2 operator-(const Vector2& lhs,
                             const Vector2& rhs);
    // 乗算
    friend Vector2 operator*(const Vector2& lhs,
                             const Vector2& rhs);
    friend Vector2 operator*(const Vector2& argVector,
                             const float scale);
    friend Vector2 operator*(const float scale,
                             const Vector2& argVector);

    // +=
    Vector2& operator+=(const Vector2& rhs);
    // -=
    Vector2& operator-=(const Vector2& rhs);
    // *=
    Vector2& operator*=(const float scale);
};

// 三次元ベクトル
class Vector3
{
public:
    float x; // x座標
    float y; // y座標
    float z; // z座標

    // コンストラクタ
    Vector3();
    explicit Vector3(float argX,
                     float argY,
                     float argZ);

    // Vector3 オブジェクトを float* にキャスト
    const float* getAsFloatPointer() const;

    // メンバ変数を引数の値に設定
    void set(float argX,
             float argY,
             float argZ);

    // クロス積
    static Vector3 cross(const Vector3& lhs,
                         const Vector3& rhs);
    // ドット積
    static float dot(const Vector3& lhs,
                     const Vector3& rhs);
    // 正規化
    static Vector3 normalize(const Vector3& argVector);
    // Vector3 を Quaternion で変換
    static Vector3 transform(const Vector3& argVector,
                             const class Quaternion& q);

    // 加減算
    friend Vector3 operator+(const Vector3& lhs,
                             const Vector3& rhs);
    friend Vector3 operator-(const Vector3& lhs,
                             const Vector3& rhs);
    // 乗算
    friend Vector3 operator*(const Vector3& lhs,
                             const Vector3& rhs);
    friend Vector3 operator*(const Vector3& argVector,
                             const float scale);
    friend Vector3 operator*(const float scale,
                             const Vector3& argVector);

    // +=
    Vector3& operator+=(const Vector3& rhs);
    // -=
    Vector3& operator-=(const Vector3& rhs);
    // *=
    Vector3& operator*=(const float scale);
};

// 3 * 3 行列
class Matrix3
{
public:
    float mat[3][3];               // 3 * 3 行列
    static const Matrix3 IDENTITY; // 3 * 3 単位行列

    // コンストラクタ
    Matrix3();                            // 単位行列
    explicit Matrix3(float argMat[3][3]); // 引数の配列を代入

    // 3 * 3 行列を float* にキャスト
    const float* getAsFloatPointer() const;

    // 乗算
    friend Matrix3 operator*(const Matrix3& lhs,
                                    const Matrix3& rhs);

    // *=
    Matrix3& operator*=(const Matrix3& rhs);

    // スケール行列の作成
    static Matrix3 createScaleMatrix(const float xScale, 
                                            const float yScale);
    static Matrix3 createScaleMatrix(const Vector2& scaleVector);
    static Matrix3 createScaleMatrix(const float scale);

    // z軸を中心とした回転行列の作成
    static Matrix3 createRotationMatrix(const float theta);

    // 平行移動行列の作成
    static Matrix3 createTranslationMatrix(const Vector2& displacement);
};

// 4 * 4 行列
class Matrix4
{
public:
    float mat[4][4];               // 4 * 4 行列
    static const Matrix4 IDENTITY; // 4 * 4 単位行列
    
    // コンストラクタ
    Matrix4();                            // 単位行列
    explicit Matrix4(float argMat[4][4]); // 引数の配列を代入

    // 4 * 4 行列を float* にキャスト
    const float* getAsFloatPointer() const;
    
    // 行列の平行移動成分の取得
    Vector3 getTranslation() const;

    // 乗算
    friend Matrix4 operator*(const Matrix4& lhs,
                                    const Matrix4& rhs);
    // *=
    Matrix4& operator*=(const Matrix4& rhs);

    // 行列を反転させる
    static Matrix4 invert(const Matrix4& argMat);

    // スケール行列の作成
    static Matrix4 createScaleMatrix(const float xScale,
                                            const float yScale,
                                            const float zScale);
    static Matrix4 createScaleMatrix(const float scale);
    static Matrix4 createScaleMatrix(const Vector3& scaleVector);

    // 回転行列の作成
    static Matrix4 createXRotationMatrix(const float theta);
    static Matrix4 createYRotationMatrix(const float theta);
    static Matrix4 createZRotationMatrix(const float theta);

    // 平行移動行列の作成
    static Matrix4 createTranslationMatrix(const Vector3& displacement);

    // 単純なビュー射影行列の作成
    static Matrix4 createSimpleViewProjectionMatrix(const float width,
                                                    const float height);

    // 第一引数から第二引数を見る回転行列の作成
    static Matrix4 createLookAt(const Vector3& eye,
                                const Vector3& target,
                                const Vector3& up);

    // Field of View (視野)
    static Matrix4 createPerspectiveFOV(const float fovY,
                                        const float width,
                                        const float height,
                                        const float near,
                                        const float far);

    // Quaternion から Matrix4 の作成
    static Matrix4 createMatrix4FromQuaternion(const class Quaternion& q);
};

// 四元数
class Quaternion
{
public:
    float x; // x成分
    float y; // y成分
    float z; // z成分
    float w; // スカラー

    static const Quaternion IDENTITY; // Vector成分は 0.0f, スカラーは 1.0f

    // コンストラクタ
    Quaternion();                    
    explicit Quaternion(float argX, 
                        float argY,
                        float argZ,
                        float argW);
    explicit Quaternion(const Vector3& argVector,
                        float theta);

    // 値の設定
    void set(float argX,
             float argY,
             float argZ,
             float argW);

    // グラスマン積pq(qの後、pで回転)
    static Quaternion concatenate(const Quaternion& q,
                                  const Quaternion& p);
};