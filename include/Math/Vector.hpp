#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath>

const double PI = 3.141592653;

class Vector
{
public:
    Vector(double x = 0, double y = 0);

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
    double length();
    double lengthSquared();
    void normalize();
    Vector normalized();

    void turnLeft();
    Vector turnedLeft();

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