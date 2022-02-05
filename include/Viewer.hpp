#ifndef VIEWER_HPP
#define VIEWER_HPP

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/freeglut.h>

class Viewer
{
public:
    GLfloat pos[3];
    GLfloat theta;
    GLfloat phi;
    GLfloat r;

    Viewer();
    void thetaAdd(GLfloat x);
    void phiAdd(GLfloat x);
    void rAdd(GLfloat x);
    void updatePos();
};

#endif
