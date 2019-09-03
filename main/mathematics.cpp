#include "mathematics.hpp"

// 3 * 3, 4 * 4 の単位行列の作成
static float MAT3[3][3] = {{1.0f, 0.0f, 0.0f},
                           {0.0f, 1.0f, 0.0f},
                           {0.0f, 0.0f, 1.0f}};
static float MAT4[4][4] = {{1.0f, 0.0f, 0.0f, 0.0f},
                           {0.0f, 1.0f, 0.0f, 0.0f},
                           {0.0f, 0.0f, 1.0f, 0.0f},
                           {0.0f, 0.0f, 0.0f, 1.0f}};
const Matrix3 Matrix3::IDENTITY(MAT3);
const Matrix4 Matrix4::IDENTITY(MAT4);

// Quaternion の初期値
const Quaternion Quaternion::IDENTITY(0.0f,
                                      0.0f,
                                      0.0f,
                                      1.0f);

Vector2::Vector2():
    x(0.0f),
    y(0.0f)
{
}

Vector2::Vector2(const float argX,
                 const float argY):
    x(argX),
    y(argY)
{
}

void Vector2::set(const float argX,
                  const float argY)
{
    x = argX;
    y = argY;
}

Vector2 operator+(const Vector2& lhs,
                  const Vector2& rhs)
{
    return Vector2(lhs.x + rhs.x,
                   lhs.y + rhs.y);
}

Vector2 operator-(const Vector2& lhs,
                  const Vector2& rhs)
{
    return Vector2(lhs.x + rhs.x,
                   lhs.y + rhs.y);
}

Vector2 operator*(const Vector2& lhs,
                  const Vector2& rhs)
{
    return Vector2(lhs.x * rhs.x,
                   lhs.y * rhs.y);
}

Vector2 operator*(const Vector2& argVector,
                  const float scale)
{
    return Vector2(argVector.x * scale,
                   argVector.y * scale);
}

Vector2 operator*(const float scale,
                  const Vector2& argVector)
{
    return Vector2(argVector.x * scale,
                   argVector.y * scale);
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

Vector2& Vector2::operator*=(const float scale)
{
    x *= scale;
    y *= scale;
    return *this;
}

Vector3::Vector3():
    x(0.0f),
    y(0.0f),
    z(0.0f)
{
}

Vector3::Vector3(float argX,
                 float argY,
                 float argZ):
    x(argX),
    y(argY),
    z(argZ)
{
}

const float* Vector3::getAsFloatPointer() const
{
    return reinterpret_cast<const float*>(&x);
}

void Vector3::set(float argX,
                  float argY,
                  float argZ)
{
    x = argX;
    y = argY;
    z = argZ;
}

Vector3 Vector3::cross(const Vector3& lhs,
                       const Vector3& rhs)
{
    Vector3 returnValue(lhs.y * rhs.z - lhs.z * rhs.y,
                        lhs.z * rhs.x - lhs.x * rhs.z,
                        lhs.x * rhs.y - lhs.y * rhs.x);
    return returnValue;
}

float Vector3::dot(const Vector3& lhs,
                   const Vector3& rhs)
{
    float returnValue = lhs.x * rhs.x +
                        lhs.y * rhs.y +
                        lhs.z * rhs.z;
    return returnValue;
}

Vector3 Vector3::normalize(const Vector3& argVector)
{
    // ベクトルの長さ
    float length = std::sqrt(argVector.x * argVector.x +
                             argVector.y * argVector.y +
                             argVector.z * argVector.z);

    // 正規化
    return Vector3(argVector.x / length,
                   argVector.y / length,
                   argVector.z / length);
}

Vector3 Vector3::transform(const Vector3& argVector,
                           const Quaternion& q)
{
    Vector3 qVec(q.x,
                 q.y,
                 q.z);
    Vector3 returnVector = argVector;
    returnVector += 2.0f * 
                    Vector3::cross(qVec,
                                   Vector3::cross(qVec,
                                                  argVector) + q.w * argVector);
    return returnVector;
}

Vector3 operator+(const Vector3& lhs,
                  const Vector3& rhs)
{
    return Vector3(lhs.x + rhs.x,
                   lhs.y + rhs.y,
                   lhs.z + rhs.z);
}

Vector3 operator-(const Vector3& lhs,
                  const Vector3& rhs)
{
    return Vector3(lhs.x - rhs.x,
                   lhs.y - rhs.y,
                   lhs.z + rhs.z);
}

Vector3 operator*(const Vector3& lhs,
                  const Vector3& rhs)
{
    return Vector3(lhs.x * rhs.x,
                   lhs.y * rhs.y,
                   lhs.z * rhs.z);
}

Vector3 operator*(const Vector3& argVector,
                  const float scale)
{
    return Vector3(argVector.x * scale,
                   argVector.y * scale,
                   argVector.z * scale);
}

Vector3 operator*(const float scale,
                  const Vector3& argVector)
{
    return Vector3(argVector.x * scale,
                   argVector.y * scale,
                   argVector.z * scale);    
}

Vector3& Vector3::operator+=(const Vector3& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

Vector3& Vector3::operator*=(const float scale)
{
    x *= scale;
    y *= scale;
    z *= scale;
    return *this;
}

Matrix3::Matrix3()
{
    *this = Matrix3::IDENTITY;
}

Matrix3::Matrix3(float argMat[3][3])
{
    std::memcpy(mat,
                argMat,
                9 * sizeof(float));
}

const float* Matrix3::getAsFloatPointer() const
{
    return reinterpret_cast<const float*>(&mat[0][0]);
}

Matrix3 operator*(const Matrix3& lhs,
                  const Matrix3& rhs)
{
    Matrix3 returnMat; // 返す行列
    int size = 3;      // 行列の大きさ
    
    // 各要素の計算
    for(int row = 0; row < size; row++)
    {
        for(int column = 0; column < size; column++)
        {
            float element = 0;
            for(int i = 0; i < size; i++)
                element += lhs.mat[row][i] * 
                            rhs.mat[i][column];
            returnMat.mat[row][column] = element;
        }
    }

    return returnMat;
}

Matrix3& Matrix3::operator*=(const Matrix3& rhs)
{
    *this = *this * rhs;
    return *this;
}

Matrix3 Matrix3::createScaleMatrix(const float xScale,
                                   const float yScale)
{
    float temp[3][3] = {{xScale,   0.0f,   0.0f},
                        {  0.0f, yScale,   0.0f},
                        {  0.0f,   0.0f,   1.0f}};
    return Matrix3(temp);
}

Matrix3 Matrix3::createScaleMatrix(const Vector2& scaleVector)
{
    return createScaleMatrix(scaleVector.x,
                             scaleVector.y);
}

Matrix3 Matrix3::createScaleMatrix(const float scale)
{
    return createScaleMatrix(scale,
                             scale);
}

Matrix3 Matrix3::createRotationMatrix(const float theta)
{
    // シータからラジアンに変更
    float radian = theta * M_PI / 180.0f;

    float temp[3][3] = {{ std::cos(radian), std::sin(radian), 0.0f},
                        {-std::sin(radian), std::cos(radian), 0.0f},
                        {             0.0f,             0.0f, 1.0f}};

    return Matrix3(temp);
}

Matrix3 Matrix3::createTranslationMatrix(const Vector2& displacement)
{
    float temp[3][3] = {{          1.0f,           0.0f, 0.0f},
                        {          0.0f,           1.0f, 0.0f},
                        {displacement.x, displacement.y, 1.0f}};

    return Matrix3(temp);    
}

Matrix4::Matrix4()
{
    *this = Matrix4::IDENTITY;
}

Matrix4::Matrix4(float argMat[4][4])
{
    std::memcpy(mat,
                argMat,
                16 * sizeof(float));
}

const float* Matrix4::getAsFloatPointer() const
{
    return reinterpret_cast<const float*>(&mat[0][0]);
}

Vector3 Matrix4::getTranslation() const
{
    return Vector3(mat[3][0],
                   mat[3][1],
                   mat[3][2]);
}

Matrix4 operator*(const Matrix4& lhs,
                  const Matrix4& rhs)
{
    Matrix4 returnMat; // 返すオブジェクト
    int size = 4;      // 行列の大きさ
    
    // 各要素の計算
    for(int row = 0; row < size; row++)
    {
        for(int column = 0; column < size; column++)
        {
            float element = 0;
            for(int i = 0; i < size; i++)
                element += lhs.mat[row][i] * 
                            rhs.mat[i][column];
            returnMat.mat[row][column] = element;
        }
    }

    return returnMat;
}

Matrix4& Matrix4::operator*=(const Matrix4& rhs)
{
    *this = *this * rhs;
    return *this;
}

Matrix4 Matrix4::invert(const Matrix4& argMat)
{
	// Thanks slow math
	// This is a really janky way to unroll everything...
    float returnValue[4][4] = {{0.0f}};

	float tmp[12] = {0.0f};
	float src[16] = {0.0f}; 
	float dst[16] = {0.0f};
	float det = 0.0f;

	// Transpose matrix
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            src[i + j * 4] = argMat.mat[i][j];
        }
    }

	// Calculate cofactors
	tmp[0]  = src[10] * src[15];
	tmp[1]  = src[11] * src[14];
	tmp[2]  = src[9]  * src[15];
	tmp[3]  = src[11] * src[13];
	tmp[4]  = src[9]  * src[14];
	tmp[5]  = src[10] * src[13];
	tmp[6]  = src[8]  * src[15];
	tmp[7]  = src[11] * src[12];
	tmp[8]  = src[8]  * src[14];
	tmp[9]  = src[10] * src[12];
	tmp[10] = src[8]  * src[13];
	tmp[11] = src[9]  * src[12];
	
	dst[0]  = tmp[0] * src[5] + tmp[3] * src[6] + tmp[4]  * src[7];
	dst[0] -= tmp[1] * src[5] + tmp[2] * src[6] + tmp[5]  * src[7];
	dst[1]  = tmp[1] * src[4] + tmp[6] * src[6] + tmp[9]  * src[7];
	dst[1] -= tmp[0] * src[4] + tmp[7] * src[6] + tmp[8]  * src[7];
	dst[2]  = tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7];
	dst[2] -= tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7];
	dst[3]  = tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6];
	dst[3] -= tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6];
	dst[4]  = tmp[1] * src[1] + tmp[2] * src[2] + tmp[5]  * src[3];
	dst[4] -= tmp[0] * src[1] + tmp[3] * src[2] + tmp[4]  * src[3];
	dst[5]  = tmp[0] * src[0] + tmp[7] * src[2] + tmp[8]  * src[3];
	dst[5] -= tmp[1] * src[0] + tmp[6] * src[2] + tmp[9]  * src[3];
	dst[6]  = tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3];
	dst[6] -= tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3];
	dst[7]  = tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2];
	dst[7] -= tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2];
	
	tmp[0]  = src[2] * src[7];
	tmp[1]  = src[3] * src[6];
	tmp[2]  = src[1] * src[7];
	tmp[3]  = src[3] * src[5];
	tmp[4]  = src[1] * src[6];
	tmp[5]  = src[2] * src[5];
	tmp[6]  = src[0] * src[7];
	tmp[7]  = src[3] * src[4];
	tmp[8]  = src[0] * src[6];
	tmp[9]  = src[2] * src[4];
	tmp[10] = src[0] * src[5];
	tmp[11] = src[1] * src[4];
	
	dst[8]   = tmp[0]  * src[13] + tmp[3]  * src[14] + tmp[4]  * src[15];
	dst[8]  -= tmp[1]  * src[13] + tmp[2]  * src[14] + tmp[5]  * src[15];
	dst[9]   = tmp[1]  * src[12] + tmp[6]  * src[14] + tmp[9]  * src[15];
	dst[9]  -= tmp[0]  * src[12] + tmp[7]  * src[14] + tmp[8]  * src[15];
	dst[10]  = tmp[2]  * src[12] + tmp[7]  * src[13] + tmp[10] * src[15];
	dst[10] -= tmp[3]  * src[12] + tmp[6]  * src[13] + tmp[11] * src[15];
	dst[11]  = tmp[5]  * src[12] + tmp[8]  * src[13] + tmp[11] * src[14];
	dst[11] -= tmp[4]  * src[12] + tmp[9]  * src[13] + tmp[10] * src[14];
	dst[12]  = tmp[2]  * src[10] + tmp[5]  * src[11] + tmp[1]  * src[9];
	dst[12] -= tmp[4]  * src[11] + tmp[0]  * src[9]  + tmp[3]  * src[10];
	dst[13]  = tmp[8]  * src[11] + tmp[0]  * src[8]  + tmp[7]  * src[10];
	dst[13] -= tmp[6]  * src[10] + tmp[9]  * src[11] + tmp[1]  * src[8];
	dst[14]  = tmp[6]  * src[9]  + tmp[11] * src[11] + tmp[3]  * src[8];
	dst[14] -= tmp[10] * src[11] + tmp[2]  * src[8]  + tmp[7]  * src[9];
	dst[15]  = tmp[10] * src[10] + tmp[4]  * src[8]  + tmp[9]  * src[9];
	dst[15] -= tmp[8]  * src[9]  + tmp[11] * src[10] + tmp[5]  * src[8];
	
	// Calculate determinant
	for(int i = 0; i < 4; i++)
        det += src[i] * dst[i];
	
	// Inverse of matrix is divided by determinant
	det = 1 / det;
	for (int j = 0; j < 16; j++)
		dst[j] *= det;

	// Set it back
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            returnValue[i][j] = dst[i * 4 + i];
    
    return Matrix4(returnValue);
}

Matrix4 Matrix4::createScaleMatrix(const float xScale,
                                   const float yScale,
                                   const float zScale)
{
    float temp[4][4] = {{xScale,   0.0f,   0.0f,   0.0f},
                        {  0.0f, yScale,   0.0f,   0.0f},
                        {  0.0f,   0.0f, zScale,   0.0f},
                        {  0.0f,   0.0f,   0.0f,   1.0f}};

    return Matrix4(temp);
}

Matrix4 Matrix4::createScaleMatrix(const float scale)
{
    return createScaleMatrix(scale,
                             scale,
                             scale); 
}

Matrix4 Matrix4::createScaleMatrix(const Vector3& scaleVector)
{
    return createScaleMatrix(scaleVector.x,
                             scaleVector.y,
                             scaleVector.z);
}

Matrix4 Matrix4::createXRotationMatrix(const float theta)
{
    // シータからラジアンに変更
    float radian = theta * M_PI / 180.0f;

    float temp[4][4] = {{1.0f,              0.0f,             0.0f, 0.0f},
                        {0.0f,  std::cos(radian), std::sin(radian), 0.0f},
                        {0.0f, -std::sin(radian), std::cos(radian), 0.0f},
                        {0.0f,              0.0f,             0.0f, 1.0f}};

    return Matrix4(temp);
}

Matrix4 Matrix4::createYRotationMatrix(const float theta)
{
    // シータからラジアンに変更
    float radian = theta * M_PI / 180.0f;

    float temp[4][4] = {{std::cos(radian), 0.0f, -std::sin(radian), 0.0f},
                        {            0.0f, 1.0f,              0.0f, 0.0f},
                        {std::sin(radian), 0.0f,  std::cos(radian), 0.0f},
                                    {0.0f, 0.0f,              0.0f, 1.0f}};

    return Matrix4(temp);
}

Matrix4 Matrix4::createZRotationMatrix(const float theta)
{
    // シータからラジアンに変更
    float radian = theta * M_PI / 180.0f;

    float temp[4][4] = {{ std::cos(radian), std::sin(radian), 0.0f, 0.0f},
                        {-std::sin(radian), std::cos(radian), 0.0f, 0.0f},
                        {             0.0f,             0.0f, 1.0f, 0.0f},
                        {             0.0f,             0.0f, 0.0f, 1.0f}};

    return Matrix4(temp);
}

Matrix4 Matrix4::createTranslationMatrix(const Vector3& displacement)
{
    float temp[4][4] = {{1.0f, 0.0f, 0.0f, 0.0f},
                        {0.0f, 1.0f, 0.0f, 0.0f},
                        {0.0f, 0.0f, 1.0f, 0.0f},
                        {displacement.x, displacement.y, displacement.z, 1.0f}};

    return Matrix4(temp);
}

Matrix4 Matrix4::createSimpleViewProjectionMatrix(const float width,
                                                  const float height)
{
    float temp[4][4] = {{2.0f / width,          0.0f, 0.0f, 0.0f},
                        {        0.0f, 2.0f / height, 0.0f, 0.0f},
                        {        0.0f,          0.0f, 1.0f, 0.0f},
                        {        0.0f,          0.0f, 1.0f, 1.0f}};
    
    return Matrix4(temp);
}

Matrix4 Matrix4::createLookAt(const Vector3& eye,
                              const Vector3& target,
                              const Vector3& up)
{
    Vector3 zAxis = Vector3::normalize(target - eye);
    Vector3 xAxis = Vector3::normalize(Vector3::cross(up, zAxis));
    Vector3 yAxis = Vector3::normalize(Vector3::cross(zAxis, xAxis));

    Vector3 translation(-Vector3::dot(xAxis, eye),
                        -Vector3::dot(yAxis, eye),
                        -Vector3::dot(zAxis, eye));

    float temp[4][4] = {{      xAxis.x,       yAxis.x,       zAxis.x, 0.0f},
                        {      xAxis.y,       yAxis.y,       zAxis.y, 0.0f},
                        {      xAxis.z,       yAxis.z,       zAxis.z, 0.0f},
                        {translation.x, translation.y, translation.z, 1.0f}};

    return Matrix4(temp);
}

Matrix4 Matrix4::createPerspectiveFOV(const float fovY,
                                      const float width,
                                      const float height,
                                      const float near,
                                      const float far)
{
    float yScale = 1.0f / (std::tan(fovY / 2.0f));
    float xScale = yScale * height / width;
    
    float temp[4][4] = {{xScale,   0.0f,                       0.0f, 0.0f},
                        {  0.0f, yScale,                       0.0f, 0.0f},
                        {  0.0f,   0.0f,         far / (far / near), 1.0f},
                        {  0.0f,   0.0f, -near * far / (far - near), 0.0f}};

    return Matrix4(temp);
}

Matrix4 Matrix4::createMatrix4FromQuaternion(const Quaternion& q)
{
    float mat[4][4] = {{0.0f}};

    // 0行
	mat[0][0] = 1.0f - 2.0f * q.y * q.y - 2.0f * q.z * q.z;
	mat[0][1] = 2.0f * q.x * q.y + 2.0f * q.w * q.z;
	mat[0][2] = 2.0f * q.x * q.z - 2.0f * q.w * q.y;
	mat[0][3] = 0.0f;
    // 1行
	mat[1][0] = 2.0f * q.x * q.y - 2.0f * q.w * q.z;
	mat[1][1] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z;
	mat[1][2] = 2.0f * q.y * q.z + 2.0f * q.w * q.x;
	mat[1][3] = 0.0f;
    // 2行
	mat[2][0] = 2.0f * q.x * q.z + 2.0f * q.w * q.y;
	mat[2][1] = 2.0f * q.y * q.z - 2.0f * q.w * q.x;
	mat[2][2] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.y * q.y;
	mat[2][3] = 0.0f;
    // 3行
	mat[3][0] = 0.0f;
	mat[3][1] = 0.0f;
	mat[3][2] = 0.0f;
	mat[3][3] = 1.0f;

    return Matrix4(mat);
}

Quaternion::Quaternion()
{
    *this = Quaternion::IDENTITY;
}

Quaternion::Quaternion(float argX,
                       float argY,
                       float argZ,
                       float argW):
    x(argX),
    y(argY),
    z(argZ),
    w(argW)
{
}

Quaternion::Quaternion(const Vector3& argVector,
                       float theta)
{
    // 度数をラジアンに変換
    float radian = theta * M_PI / 180.0f;
    // 
    float scale = std::sin(radian / 2.0f);

    // 
    x = argVector.x * scale;
    y = argVector.y * scale;
    z = argVector.z * scale;
    
    w = std::cos(radian / 2.0f);
}

void Quaternion::set(float argX,
                     float argY,
                     float argZ,
                     float argW)
{
    x = argX;
    y = argY;
    z = argZ;
    w = argW;
}

Quaternion Quaternion::concatenate(const Quaternion& q,
                                   const Quaternion& p)
{
    // 引数のQuaternionをVector3に変換
    Vector3 qVec(q.x,
                 q.y,
                 q.z);
    Vector3 pVec(p.x,
                 p.y,
                 p.z);
    
    // グラスマン積の演算
    // Vector3部分
    Vector3 resultVec = p.w * qVec + 
                        q.w * pVec +
                        Vector3::cross(pVec, qVec);
    // スカラー部分
    float resultScale = p.w * q.w -
                        Vector3::dot(pVec, qVec);
    
    return Quaternion(resultVec.x,
                      resultVec.y,
                      resultVec.z,
                      resultScale);
}