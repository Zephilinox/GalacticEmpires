#include "Helper/Math/Vector.hpp"

Vector::Vector(float argX, float argY)
    : x(argX)
    , y(argY)
{
}

Vector::Vector(sf::Vector2f vec)
    : x(vec.x)
    , y(vec.y)
{
}

Vector::operator sf::Vector2f()
{
    return sf::Vector2f(this->x, this->y);
}

float Vector::radToDeg(float argRad)
{
    return argRad * (180.f / PI);
}

float Vector::degToRad(float argDeg)
{
    return argDeg * (PI / 180.f);
}

Vector Vector::degToVector(float deg)
{
    return radToVector(degToRad(deg));
}

Vector Vector::radToVector(float rad)
{
    return Vector(std::sin(rad), -std::cos(rad));
}

Vector& Vector::operator=(const Vector& argVec)
{
    x = argVec.x;
    y = argVec.y;
    return *this;
}

Vector operator+(const Vector& argVec, const Vector& argVec2)
{
    return Vector(argVec.x + argVec2.x, argVec.y + argVec2.y);
}

Vector& Vector::operator+=(const Vector& argVec)
{
    *this = *this + argVec;
    return *this;
}

Vector operator-(const Vector& argVec, const Vector& argVec2)
{
    return Vector(argVec.x - argVec2.x, argVec.y - argVec2.y);
}

Vector& Vector::operator-=(const Vector& argVec)
{
    *this = *this - argVec;
    return *this;
}

Vector operator*(const Vector& argVec, const Vector& argVec2)
{
    return Vector(argVec.x * argVec2.x, argVec.y * argVec2.y);
}

Vector& Vector::operator*=(const Vector& argVec)
{
    *this = *this * argVec;
    return *this;
}

Vector operator/(const Vector& argVec, const Vector& argVec2)
{
    return Vector(argVec.x / argVec2.x, argVec.y / argVec2.y);
}

Vector& Vector::operator/=(const Vector& argVec)
{
    *this = *this / argVec;
    return *this;
}

Vector operator+(const Vector& vec, float argScalar)
{
    return Vector(vec.x + argScalar, vec.y + argScalar);
}

Vector& Vector::operator+=(float argScalar)
{
    *this = *this + argScalar;
    return *this;
}

Vector operator-(const Vector& vec, float argScalar)
{
    return Vector(vec.x - argScalar, vec.y - argScalar);
}

Vector& Vector::operator-=(float argScalar)
{
    *this = *this - argScalar;
    return *this;
}

Vector operator*(const Vector& vec, float argScalar)
{
    return Vector(vec.x * argScalar, vec.y * argScalar);
}

Vector& Vector::operator*=(float argScalar)
{
    *this = *this * argScalar;
    return *this;
}

Vector operator/(const Vector& vec, float argScalar)
{
    return Vector(vec.x / argScalar, vec.y / argScalar);
}

Vector& Vector::operator/=(float argScalar)
{
    *this = *this / argScalar;
    return *this;
}

float Vector::dot(const Vector& argVec)
{
    return (x * argVec.x) + (y * argVec.y);
}

float Vector::length()
{
    return std::sqrt(x * x + y * y);
}

float Vector::lengthSquared()
{
    return x * x + y * y;
}

void Vector::normalize()
{
    if (this->length() != 0)
    {
        *this /= this->length();
    }
}

Vector Vector::normalized()
{
    if (this->lengthSquared() == 0) return Vector(0, 0);
    Vector vec = *this / this->length();
    return vec;
}

void Vector::turnLeft()
{
    this->x = -(this->x);
}

Vector Vector::turnedLeft()
{
    Vector vec(y, -x);
    return vec;
}

void Vector::turnRight()
{
    this->y = -(this->y);
}

Vector Vector::turnedRight()
{
    Vector vec(-y, x);
    return vec;
}

void Vector::rotateWithDeg(float argDeg)
{
    argDeg = Vector::degToRad(argDeg);

    //we use them both twice so store them, sin and cos are expensive calls.
    float sinResult = std::sin(argDeg);
    float cosResult = std::cos(argDeg);

    this->x = (this->x * cosResult) - (this->y * sinResult);
    this->y = (this->x * sinResult) + (this->y * cosResult);
}

Vector Vector::rotatedWithDeg(float argDeg)
{
    argDeg = degToRad(argDeg);

    //we use them both twice so store them, sin and cos are expensive calls.
    float sinResult = std::sin(argDeg);
    float cosResult = std::cos(argDeg);

    Vector vec((this->x * cosResult) - (this->y * sinResult), (this->x * sinResult) + (this->y * cosResult));

    return vec;
}

void Vector::rotateWithRad(float argRad)
{
    //we use them both twice so store them, sin and cos are expensive calls.
    float sinResult = std::sin(argRad);
    float cosResult = std::cos(argRad);

    this->x = (this->x * cosResult) - (this->y * sinResult);
    this->y = (this->x * sinResult) + (this->y * cosResult);
}

Vector Vector::rotatedWithRad(float argRad)
{
    //we use them both twice so store them, sin and cos are expensive calls.
    float sinResult = std::sin(argRad);
    float cosResult = std::cos(argRad);

    Vector vec((this->x * cosResult) - (this->y * sinResult), (this->x * sinResult) + (this->y * cosResult));

    return vec;
}

float Vector::degrees()
{
    return std::atan2(x, -y) * (180.f / PI);
}

float Vector::radians()
{
    return std::atan2(x, -y);
}
