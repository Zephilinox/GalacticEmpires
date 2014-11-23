#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath>

#include <SFML/Graphics.hpp>

const float PI = 3.141592653f;

class Vector
{
public:
	Vector(float x = 0, float y = 0);
    Vector(sf::Vector2f vec);
    operator sf::Vector2f();

    static float radToDeg(float rad);
    static float degToRad(float deg);
    static Vector degToVector(float deg);
    static Vector radToVector(float rad);

    Vector& operator=(const Vector& vec);
    Vector& operator+=(const Vector& vec);
    Vector& operator-=(const Vector& vec);
    Vector& operator*=(const Vector& vec);
    Vector& operator/=(const Vector& vec);

    Vector& operator+=(float scalar);
    Vector& operator-=(float scalar);
    Vector& operator*=(float scalar);
    Vector& operator/=(float scalar);

    float x;
    float y;

    float dot(const Vector& vec);
    float length(); //Uses square root
    float lengthSquared(); //Doesn't use square root
    void normalize();
    Vector normalized();

    //Rotate by 90 degrees left
    void turnLeft();
    Vector turnedLeft();

    //Rotate by 90 degrees right
    void turnRight();
    Vector turnedRight();

    void rotateWithDeg(float deg);
    Vector rotatedWithDeg(float deg);

    void rotateWithRad(float rad);
    Vector rotatedWithRad(float rad);

    float degrees();
    float radians();
};

Vector operator+(const Vector& vec, const Vector& vec2);
Vector operator-(const Vector& vec, const Vector& vec2);
Vector operator*(const Vector& vec, const Vector& vec2);
Vector operator/(const Vector& vec, const Vector& vec2);

Vector operator+(const Vector& vec, float scalar);
Vector operator-(const Vector& vec, float scalar);
Vector operator*(const Vector& vec, float scalar);
Vector operator/(const Vector& vec, float scalar);

#endif
