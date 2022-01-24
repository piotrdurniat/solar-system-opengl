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

public:
    Planet(GLfloat radius, GLfloat distFromTheSun, const char *textureName);

    ~Planet();

    void display();
};

#endif
