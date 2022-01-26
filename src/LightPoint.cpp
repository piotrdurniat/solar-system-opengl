#include <LightPoint.hpp>
#include <cmath>

LightPoint::LightPoint(GLfloat x, GLfloat y, GLfloat z, GLenum identifier)
{

    this->pos[0] = x;
    this->pos[1] = y;
    this->pos[2] = z;
    this->pos[3] = 1.f;

    ambient[0] = 0.1;
    ambient[1] = 0.1;
    ambient[2] = 0.1;
    ambient[3] = 1.0;

    diffuse[0] = 1.0;
    diffuse[1] = 1.0;
    diffuse[2] = 1.0;
    diffuse[3] = 1.0;

    specular[0] = 1.0;
    specular[1] = 1.0;
    specular[2] = 1.0;
    specular[3] = 1.0;

    att_constant = {1.0};

    att_linear = {0.05};
    att_quadratic = {0.001};

    this->identifier = identifier;

    updatePos();
}

void LightPoint::setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat w)
{
    ambient[0] = r;
    ambient[1] = g;
    ambient[2] = b;
    ambient[3] = w;
}

void LightPoint::setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat w)
{
    specular[0] = r;
    specular[1] = g;
    specular[2] = b;
    specular[3] = w;
}

void LightPoint::setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat w)
{
    diffuse[0] = r;
    diffuse[1] = g;
    diffuse[2] = b;
    diffuse[3] = w;
}

void LightPoint::updatePos()
{
    glLightfv(identifier, GL_POSITION, pos);
}
void LightPoint::setup()
{
    glLightfv(identifier, GL_AMBIENT, ambient);
    glLightfv(identifier, GL_DIFFUSE, diffuse);
    glLightfv(identifier, GL_SPECULAR, specular);
    glLightfv(identifier, GL_POSITION, pos);

    // glLightf(identifier, GL_CONSTANT_ATTENUATION, att_constant);
    // glLightf(identifier, GL_LINEAR_ATTENUATION, att_linear);
    // glLightf(identifier, GL_QUADRATIC_ATTENUATION, att_quadratic);
}

void LightPoint::enable()
{
    glEnable(identifier);
}
