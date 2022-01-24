#include "Planet.hpp"

Planet::Planet(GLfloat radius, GLfloat distFromTheSun, const char *textureName) : Sphere(40, 40, radius)
{
    this->distFromTheSun = distFromTheSun;

    texture = new Texture();
    setDisplayMode(DisplayMode::filledTriangles);

    texture->load(textureName);
}

Planet::~Planet()
{
    delete texture;
}

void Planet::display()
{
    texture->set();

    glPushMatrix();

    glTranslatef(distFromTheSun, 0, 0);

    this->Sphere::display();

    glPopMatrix();
}
