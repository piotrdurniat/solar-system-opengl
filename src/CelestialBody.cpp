#include "CelestialBody.hpp"

CelestialBody::CelestialBody(GLfloat radius, GLfloat distFromTheSun, GLfloat orbitalAngularSpeed, GLfloat rotationalAngularSpeed, const char *textureName) : Sphere(40, 40, radius)
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

CelestialBody::~CelestialBody()
{
    delete texture;
}

void CelestialBody::setAxialTilt(GLfloat axialTilt)
{
    this->axialTilt = axialTilt;
}

void CelestialBody::display()
{

    glPushMatrix();

    glRotatef(orbitalAngle, 0, 1, 0);
    glTranslatef(distFromTheSun, 0.0, 0.0);

    if (moon != NULL)
    {
        this->moon->display();
    }

    glRotatef(axialTilt, 1, 0, 0);

    glRotatef(rotationAngle, 0, 1, 0);
    texture->set();

    this->Sphere::display();

    glPopMatrix();
}

void CelestialBody::update()
{

    orbitalAngle += orbitalAngularSpeed;

    rotationAngle += rotationalAngularSpeed;

    rotationAngle = wrapTo360(rotationAngle);
    orbitalAngle = wrapTo360(orbitalAngle);

    if (this->moon != NULL)
    {
        this->moon->update();
    }
}

void CelestialBody::setMoon(CelestialBody *moon)
{
    this->moon = moon;
}

GLfloat CelestialBody::wrapTo360(GLfloat angle)
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
