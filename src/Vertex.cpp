#include "Vertex.hpp"
#include <cmath>

Vertex::Vertex()
{
    this->normal = new Vector3f();
}

Vertex::~Vertex()
{
    delete this->normal;
}

Vertex::Vertex(float x, float y, float z)
{
    Vertex();
    this->x = x;
    this->y = y;
    this->z = z;
}

float Vertex::getMagnitude()
{
    return sqrt(x * x + y * y + z * z);
}

void Vertex::normalize()
{
    float magnitude = getMagnitude();
    x = x / magnitude;
    y = y / magnitude;
    z = z / magnitude;
}

void Vertex::setNormal(GLfloat x, GLfloat y, GLfloat z)
{
    this->normal->set(x, y, z);
}

void Vertex::setTexturePos(GLfloat x, GLfloat y)
{
    this->texturePos[0] = x;
    this->texturePos[1] = y;
}

void Vertex::setPos(GLfloat x, GLfloat y, GLfloat z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}
