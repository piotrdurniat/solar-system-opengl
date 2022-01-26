#ifndef CELESTIAL_BODY_HPP
#define CELESTIAL_BODY_HPP

#include "Sphere.hpp"
#include "Texture.hpp"

class CelestialBody : public Sphere
{
protected:
    Texture *texture;
    GLfloat distFromTheSun;
    GLfloat radius;

    GLfloat orbitalAngularSpeed;
    GLfloat rotationalAngularSpeed;

    GLfloat orbitalAngle;
    GLfloat rotationAngle;

    GLfloat axialTilt = 0.0;

    CelestialBody *moon = NULL;

public:
    CelestialBody(GLfloat radius, GLfloat distFromTheSun, GLfloat orbitalAngularSpeed, GLfloat rotationalAngularSpeed, const char *textureName);
    ~CelestialBody();
    void display();
    void update();
    GLfloat wrapTo360(GLfloat angle);
    void setAxialTilt(GLfloat tilt);
    void setMoon(CelestialBody *moon);
};

#endif
