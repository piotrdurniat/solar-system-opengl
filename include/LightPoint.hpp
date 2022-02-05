#ifndef LIGHT_POINT_HPP
#define LIGHT_POINT_HPP

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/freeglut.h>

class LightPoint
{
public:
    GLfloat pos[4];
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat att_constant;
    GLfloat att_linear;
    GLfloat att_quadratic;

    // Angle of the direction the light is pointed to
    GLfloat theta;

    GLenum identifier;

    LightPoint(GLfloat phi, GLfloat theta, GLfloat r, GLenum identifier);
    void setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat w);
    void setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat w);
    void setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat w);
    void updatePos();
    void setup();
    void enable();
};

#endif
