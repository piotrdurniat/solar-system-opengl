#include "Planet.hpp"

Planet::Planet(GLfloat radius, GLfloat distFromTheSun, GLfloat orbitalAngularSpeed, GLfloat rotationalAngularSpeed, const char *textureName) : Sphere(40, 40, radius)
{
    this->distFromTheSun = distFromTheSun;

    this->orbitalAngle = rand() % 360;
    this->rotationAngle = rand() % 360;

    this->orbitalAngularSpeed = orbitalAngularSpeed;
    this->rotationalAngularSpeed = rotationalAngularSpeed;

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

    glRotatef(orbitalAngle, 0, 1, 0);
    glTranslatef(distFromTheSun, 0.0, 0.0);
    glRotatef(rotationAngle, 0, 1, 0);

    this->Sphere::display();

    glPopMatrix();
}

void Planet::update()
{

    orbitalAngle += orbitalAngularSpeed;

    rotationAngle += rotationalAngularSpeed;

    rotationAngle = wrapTo360(rotationAngle);
    orbitalAngle = wrapTo360(orbitalAngle);
}

GLfloat Planet::wrapTo360(GLfloat angle)
{
    if (angle >= 360.0)
    {
        angle -= 360.0;
    }
    else if (angle <= -360.0)
    {
        angle += 360.0;
    }
    return angle;
}
