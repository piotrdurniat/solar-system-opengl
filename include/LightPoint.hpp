#ifndef LIGHT_POINT_HPP
#define LIGHT_POINT_HPP

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glut.h>

class LightPoint
{
public:
    // położenie źródła
    GLfloat pos[4];

    // składowe intensywności świecenia źródła światła otoczenia
    // Ia = [Iar,Iag,Iab]
    GLfloat ambient[4];

    // składowe intensywności świecenia źródła światła powodującego
    // odbicie dyfuzyjne Id = [Idr,Idg,Idb]
    GLfloat diffuse[4];

    // składowe intensywności świecenia źródła światła powodującego
    // odbicie kierunkowe Is = [Isr,Isg,Isb]
    GLfloat specular[4];

    // składowa stała ds dla modelu zmian oświetlenia w funkcji
    // odległości od źródła
    GLfloat att_constant;

    // składowa liniowa dl dla modelu zmian oświetlenia w funkcji
    // odległości od źródła
    GLfloat att_linear;

    /*
     * składowa kwadratowa dq dla modelu zmian oświetlenia w funkcji
     * odległości od źródła
     */
    GLfloat att_quadratic;

    // the direction the light is pointed to (theta)
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
