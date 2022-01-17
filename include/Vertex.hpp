#ifndef VERTEX_H
#define VERTEX_H

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glut.h>

#include "Color.hpp"
#include "Vector3f.hpp"

typedef GLfloat point2[2];

class Vertex
{
public:
    float x;
    float y;
    float z;
    Color *color;
    Vector3f *normal;
    point2 texturePos;

    Vertex();
    Vertex(float x, float y, float z);

    void normalize();
    float getMagnitude();
    void setNormal(GLfloat x, GLfloat y, GLfloat z);
    void setTexturePos(GLfloat x, GLfloat y);
};

#endif
