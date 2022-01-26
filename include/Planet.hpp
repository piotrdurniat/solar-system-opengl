#ifndef PLANET_HPP
#define PLANET_HPP

#include "Sphere.hpp"
#include "Texture.hpp"

class Planet : public Sphere
{
protected:
    Texture *texture;
    GLfloat distFromTheSun;
    GLfloat radius;
    GLfloat orbitalAngularSpeed;
    GLfloat rotationalAngularSpeed;

    GLfloat orbitalAngle;
    GLfloat rotationAngle;

public:
    Planet(GLfloat radius, GLfloat distFromTheSun, const char *textureName);

    ~Planet();

    void display();

    void update();

    GLfloat wrapTo360(GLfloat angle);
};

#endif
