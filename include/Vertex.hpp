#ifndef VERTEX_H
#define VERTEX_H

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/freeglut.h>

#include "Vector3f.hpp"

typedef GLfloat point2[2];

class Vertex
{
public:
    float x;
    float y;
    float z;
    Vector3f *normal;
    point2 texturePos;

    Vertex();
    ~Vertex();
    Vertex(float x, float y, float z);

    void normalize();
    float getMagnitude();
    void setNormal(GLfloat x, GLfloat y, GLfloat z);
    void setTexturePos(GLfloat x, GLfloat y);
    void setPos(GLfloat x, GLfloat y, GLfloat z);
};

#endif
