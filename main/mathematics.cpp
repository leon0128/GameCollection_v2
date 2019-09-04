#include "mathematics.hpp"

const Vector2 Vector2::ZERO(0.0f, 0.0f);
const Vector2 Vector2::UNIT_X(1.0f, 0.0f);
const Vector2 Vector2::UNIT_Y(0.0f, 1.0f);
const Vector2 Vector2::NEGATIVE_UNIT_X(-1.0f, 0.0f);
const Vector2 Vector2::NEGATIVE_UNIT_Y(0.0f, -1.0f);

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