#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath>

#include <SFML/Graphics.hpp>

const double PI = 3.141592653;

class Vector
{
public:
    Vector(double x = 0, double y = 0);
    Vector(sf::Vector2f vec);
    operator sf::Vector2f();

    static double radToDeg(double rad);
    static double degToRad(double deg);
    static Vector degToVector(double deg);
    static Vector radToVector(double rad);

    Vector& operator=(const Vector& vec);
    Vector& operator+=(const Vector& vec);
    Vector& operator-=(const Vector& vec);
    Vector& operator*=(const Vector& vec);
    Vector& operator/=(const Vector& vec);

    Vector& operator+=(double scalar);
    Vector& operator-=(double scalar);
    Vector& operator*=(double scalar);
    Vector& operator/=(double scalar);

    double x;
    double y;

    double dot(const Vector& vec);
    double length(); //Uses square root
    double lengthSquared(); //Doesn't use square root
    void normalize();
    Vector normalized();

    //Rotate by 90 degrees left
    void turnLeft();
    Vector turnedLeft();

    //Rotate by 90 degrees right
    void turnRight();
    Vector turnedRight();

    void rotateWithDeg(double deg);
    Vector rotatedWithDeg(double deg);

    void rotateWithRad(double rad);
    Vector rotatedWithRad(double rad);

    double degrees();
    double radians();
};

Vector operator+(const Vector& vec, const Vector& vec2);
Vector operator-(const Vector& vec, const Vector& vec2);
Vector operator*(const Vector& vec, const Vector& vec2);
Vector operator/(const Vector& vec, const Vector& vec2);

Vector operator+(const Vector& vec, double scalar);
Vector operator-(const Vector& vec, double scalar);
Vector operator*(const Vector& vec, double scalar);
Vector operator/(const Vector& vec, double scalar);

#endif
