#include "Vector3f.hpp"
#include <cmath>

Vector3f::Vector3f()
{
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
}

Vector3f::Vector3f(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

float Vector3f::getMagnitude()
{
    return sqrt(x * x + y * y + z * z);
}

void Vector3f::normalize()
{
    float magnitude = getMagnitude();
    x = x / magnitude;
    y = y / magnitude;
    z = z / magnitude;
}

void Vector3f::set(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector3f::invert()
{
    x = -x;
    y = -y;
    z = -z;
}
