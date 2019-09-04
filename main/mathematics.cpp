#include "mathematics.hpp"

// Vector2 定数
const Vector2 Vector2::ZERO(0.0f, 0.0f);
const Vector2 Vector2::UNIT_X(1.0f, 0.0f);
const Vector2 Vector2::UNIT_Y(0.0f, 1.0f);
const Vector2 Vector2::NEGATIVE_UNIT_X(-1.0f, 0.0f);
const Vector2 Vector2::NEGATIVE_UNIT_Y(0.0f, -1.0f);

// Vector3 定数
const Vector3 Vector3::ZERO(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::UNIT_X(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UNIT_Y(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::UNIT_Z(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::NEGATIVE_UNIT_X(-1.0f, 0.0f, 0.0f);
const Vector3 Vector3::NEGATIVE_UNIT_Y(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::NEGATIVE_UNIT_Z(0.0f, 0.0f, -1.0f);

// Matrix4 定数
static float MAT4[4][4] = {{1.0f, 0.0f, 0.0f, 0.0f},
                           {0.0f, 1.0f, 0.0f, 0.0f},
                           {0.0f, 0.0f, 1.0f, 0.0f},
                           {0.0f, 0.0f, 0.0f, 1.0f}};
const Matrix4 Matrix4::IDENTITY(MAT4);

// Quaternion 定数
const Quaternion Quaternion::IDENTITY(0.0f, 0.0f, 0.0f, 1.0f);

Coordinate2::Coordinate2():
    x(0),
    y(0)
{
}

Coordinate2::Coordinate2(int inX, int inY):
    x(inX),
    y(inY)
{
}

void Coordinate2::set(int inX, int inY)
{
    x = inX;
    y = inY;
}

Vector2::Vector2():
    x(0.0f),
    y(0.0f)
{
}

Vector2::Vector2(float inX, float inY):
    x(inX),
    y(inY)
{
}

void Vector2::set(float inX, float inY)
{
    x = inX;
    y = inY;
}

const float* Vector2::getAsFloatPointer() const
{
    return reinterpret_cast<const float*>(&x);
}

float Vector2::lengthSquared() const
{
    float len = x * x + y * y;
    return len;
}

float Vector2::length() const
{
    float len = std::sqrt(x * x + y * y);
    return len;
}

void Vector2::normalize()
{
    float len = length();
    x /= len;
    y /= len;
}

Vector2 Vector2::normalize(const Vector2& inVector)
{
    Vector2 outVector = inVector;
    outVector.normalize();
    return outVector;
}

float Vector2::dot(const Vector2& lhs,
                   const Vector2& rhs)
{
    float out = lhs.x * rhs.x +
                lhs.y * rhs.y;
    return out;
}

Vector2 operator+(const Vector2& lhs,
                  const Vector2& rhs)
{
    Vector2 vector(lhs.x + rhs.x,
                   lhs.y + rhs.y);
    return vector;
}

Vector2 operator-(const Vector2& lhs,
                  const Vector2& rhs)
{
    Vector2 vector(lhs.x - rhs.x,
                   lhs.y - rhs.y);
    return vector;
}

Vector2 operator*(const Vector2& lhs,
                  const Vector2& rhs)
{
    Vector2 vector(lhs.x * rhs.x,
                   lhs.y * rhs.y);
    return vector;
}

Vector2 operator*(const Vector2& inVector,
                  float scalar)
{
    Vector2 outVector(inVector.x * scalar,
                      inVector.y * scalar);
    return outVector;
}

Vector2 operator*(float scalar,
                  const Vector2& inVector)
{
    Vector2 outVector(inVector.x * scalar,
                      inVector.y * scalar);
    return outVector;
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

Vector2& Vector2::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector3::Vector3():
    x(0.0f),
    y(0.0f),
    z(0.0f)
{
}

Vector3::Vector3(float inX, float inY, float inZ):
    x(inX),
    y(inY),
    z(inZ)
{
}

void Vector3::set(float inX, float inY, float inZ)
{
    x = inX;
    y = inY;
    z = inZ;
}

const float* Vector3::getAsFloatPointer() const
{
    return reinterpret_cast<const float*>(&x);
}

float Vector3::lengthSquared() const
{
    float len = x * x +
                y * y +
                z * z;
    return len;
}

float Vector3::length() const
{
    float len = std::sqrt(lengthSquared());
    return len;
}

void Vector3::normalize()
{
    float len = length();
    x /= len;
    y /= len;
    z /= len;
}

Vector3 Vector3::normalize(const Vector3& inVector)
{
    Vector3 outVector = inVector;
    outVector.normalize();
    return outVector;
}

float Vector3::dot(const Vector3& lhs,
                   const Vector3& rhs)
{
    float out = lhs.x * rhs.x +
                lhs.y * rhs.y +
                lhs.z * rhs.z;
    return out;
}

Vector3 Vector3::cross(const Vector3& lhs,
                       const Vector3& rhs)
{
    Vector3 outVector;
    outVector.x = lhs.y * rhs.z - lhs.z * rhs.y;
    outVector.y = lhs.z * rhs.x - lhs.x * rhs.z;
    outVector.z = lhs.x * rhs.y - lhs.y * rhs.x;
    return outVector;
}

Vector3 operator+(const Vector3& lhs,
                  const Vector3& rhs)
{
    Vector3 outVector(lhs.x + rhs.x,
                      lhs.y + rhs.y,
                      lhs.z + rhs.z);
    return outVector;
}

Vector3 operator-(const Vector3& lhs,
                  const Vector3& rhs)
{
    Vector3 outVector(lhs.x - rhs.x,
                      lhs.y - rhs.y,
                      lhs.z - rhs.z);
    return outVector;
}

Vector3 operator*(const Vector3& lhs,
                  const Vector3& rhs)
{
    Vector3 outVector(lhs.x * rhs.x,
                      lhs.y * rhs.y,
                      lhs.z * rhs.z);
    return outVector;
}

Vector3 operator*(const Vector3& inVector,
                  float scalar)
{
    Vector3 outVector(inVector.x * scalar,
                      inVector.y * scalar,
                      inVector.z * scalar);
    return outVector;
}

Vector3 operator*(float scalar,
                  const Vector3& inVector)
{
    Vector3 outVector(inVector.x * scalar,
                      inVector.y * scalar,
                      inVector.z * scalar);
    return outVector;
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

Vector3& Vector3::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Matrix4::Matrix4()
{
    *this = Matrix4::IDENTITY;
}

Matrix4::Matrix4(float inMat[4][4])
{
    std::memcpy(mat,
                inMat,
                4 * 4 * sizeof(float));
}

const float* Matrix4::getAsFloatPointer() const
{
    return reinterpret_cast<const float*>(&mat[0][0]);
}

Matrix4 Matrix4::createScale(float xScalar,
                             float yScalar,
                             float zScalar)
{
    Matrix4 outMatrix = Matrix4::IDENTITY;
    outMatrix.mat[0][0] = xScalar;
    outMatrix.mat[1][1] = yScalar;
    outMatrix.mat[2][2] = zScalar;
    return outMatrix;
}

Matrix4 Matrix4::createScale(const Vector3& inVector)
{
    return Matrix4::createScale(inVector.x,
                                inVector.y,
                                inVector.z);
}

Matrix4 Matrix4::createScale(float scalar)
{
    return Matrix4::createScale(scalar,
                                scalar,
                                scalar);
}

Matrix4 Matrix4::createRotationX(float theta)
{
    float radian = theta * M_PI / 180.0f;

    Matrix4 outMatrix = Matrix4::IDENTITY;
    outMatrix.mat[1][1] = std::cos(radian);
    outMatrix.mat[1][2] = std::sin(radian);
    outMatrix.mat[2][1] = -std::sin(radian);
    outMatrix.mat[2][2] = std::cos(radian);
    return outMatrix;
}

Matrix4 Matrix4::createRotationY(float theta)
{
    float radian = theta * M_PI / 180.0f;
    
    Matrix4 outMatrix = Matrix4::IDENTITY;
    outMatrix.mat[0][0] = std::cos(radian);
    outMatrix.mat[0][2] = -std::sin(radian);
    outMatrix.mat[2][0] = std::sin(radian);
    outMatrix.mat[2][2] = std::cos(radian);
    return outMatrix;
}

Matrix4 Matrix4::createRotationZ(float theta)
{
    float radian = theta * M_PI / 180.0f;

    Matrix4 outMatrix = Matrix4::IDENTITY;
    outMatrix.mat[0][0] = std::cos(radian);
    outMatrix.mat[0][1] = std::sin(radian);
    outMatrix.mat[1][0] = -std::sin(radian);
    outMatrix.mat[1][1] = std::cos(radian);
    return outMatrix;
}

Matrix4 Matrix4::createFromQuaternion(const Quaternion& q)
{
    Matrix4 outMatrix = Matrix4::IDENTITY;

	outMatrix.mat[0][0] = 1.0f - 2.0f * q.y * q.y - 2.0f * q.z * q.z;
	outMatrix.mat[0][1] = 2.0f * q.x * q.y + 2.0f * q.w * q.z;
	outMatrix.mat[0][2] = 2.0f * q.x * q.z - 2.0f * q.w * q.y;
	outMatrix.mat[0][3] = 0.0f;

	outMatrix.mat[1][0] = 2.0f * q.x * q.y - 2.0f * q.w * q.z;
	outMatrix.mat[1][1] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z;
	outMatrix.mat[1][2] = 2.0f * q.y * q.z + 2.0f * q.w * q.x;
	outMatrix.mat[1][3] = 0.0f;

	outMatrix.mat[2][0] = 2.0f * q.x * q.z + 2.0f * q.w * q.y;
	outMatrix.mat[2][1] = 2.0f * q.y * q.z - 2.0f * q.w * q.x;
	outMatrix.mat[2][2] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.y * q.y;
	outMatrix.mat[2][3] = 0.0f;

	outMatrix.mat[3][0] = 0.0f;
	outMatrix.mat[3][1] = 0.0f;
	outMatrix.mat[3][2] = 0.0f;
	outMatrix.mat[3][3] = 1.0f;

    return outMatrix;
}

Matrix4 Matrix4::createTranslation(const Vector3& translation)
{
    Matrix4 outMatrix = Matrix4::IDENTITY;
    outMatrix.mat[3][0] = translation.x;
    outMatrix.mat[3][1] = translation.y;
    outMatrix.mat[3][2] = translation.z;
    return outMatrix;
}

Matrix4 Matrix4::createSimpleViewProjection(float width, float height)
{
    Matrix4 outMatrix = Matrix4::IDENTITY;
    outMatrix.mat[0][0] = 2.0f / width;
    outMatrix.mat[1][1] = 2.0f / height;
    outMatrix.mat[3][2] = 1.0f;
    return outMatrix;
}

Quaternion::Quaternion():
    x(0.0f),
    y(0.0f),
    z(0.0f),
    w(1.0f)
{
}

Quaternion::Quaternion(float inX, float inY, float inZ, float inW):
    x(inX),
    y(inY),
    z(inZ),
    w(inW)
{ 
}

Quaternion::Quaternion(const Vector3& axis, float theta)
{
    float radian = theta * M_PI / 180.0f;
    float scalar = std::sin(radian / 2.0f);

    x = axis.x * scalar;
    y = axis.y * scalar;
    z = axis.z * scalar;
    w = std::cos(radian / 2.0f);
}

void Quaternion::set(float inX, float inY, float inZ, float inW)
{
    x = inX;
    y = inY;
    z = inZ;
    w = inW;
}

Quaternion Quaternion::concatenate(const Quaternion& q,
                                   const Quaternion& p)
{
    Quaternion quaternion;

    Vector3 qVec(q.x, q.y, q.z);
    Vector3 pVec(p.x, p.y, p.z);

    Vector3 temp = p.w * qVec + 
                   q.w * pVec + 
                   Vector3::cross(pVec, qVec);

    quaternion.x = temp.x;
    quaternion.y = temp.y;
    quaternion.z = temp.z;

    quaternion.w = p.w * q.w - Vector3::dot(pVec, qVec);

    return quaternion;
}