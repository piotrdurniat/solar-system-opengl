#ifndef VECTOR_3F_H
#define VECTOR_3F_H

class Vector3f
{
public:
    float x;
    float y;
    float z;

    Vector3f();
    Vector3f(float x, float y, float z);

    void normalize();
    float getMagnitude();
    void set(float x, float y, float z);
    void invert();
};

#endif
