#include "Sphere.hpp"

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

Sphere::Sphere(int sectorCount, int stackCount, GLfloat radius)
{

    this->sectorCount = sectorCount;
    this->stackCount = stackCount;

    this->radius = radius;

    setupVerticesOnPlane();
    transformVertices();
    // calculateNormals();
    this->drawNormals = drawNormals;
}

void Sphere::setDrawNormals(bool drawNormals)
{
    this->drawNormals = drawNormals;
}

void Sphere::transformVertices()
{
    float lengthInv = 1.0f / radius;

    float sectorStep = 2 * M_PI / (sectorCount - 1);
    float stackStep = M_PI / (stackCount - 1);

    for (int i = 0; i < stackCount; ++i)
    {
        float stackAngle = M_PI / 2 - i * stackStep; // starting from pi/2 to -pi/2
        float xy = radius * cosf(stackAngle);        // r * cos(u)
        float z = radius * sinf(stackAngle);         // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for (int j = 0; j < sectorCount; ++j)
        {
            float sectorAngle = j * sectorStep; // starting from 0 to 2pi

            // vertex position
            float x = xy * cosf(sectorAngle); // r * cos(u) * cos(v)
            float y = xy * sinf(sectorAngle); // r * cos(u) * sin(v)

            vertices[i][j]->setPos(x, y, z);

            // normalized vertex normal
            float nx = x * lengthInv;
            float ny = y * lengthInv;
            float nz = z * lengthInv;
            vertices[i][j]->setNormal(nx, ny, nz);
            // addNormal(nx, ny, nz);

            // // vertex tex coord between [0, 1]
            float s = (float)j / (sectorCount - 1);
            float t = (float)i / (stackCount - 1);
            vertices[i][j]->setTexturePos(s, t);
        }
    }
}

void Sphere::setupVerticesOnPlane()
{
    vertices = new Vertex **[stackCount];

    for (int i = 0; i < stackCount; ++i)
    {
        vertices[i] = new Vertex *[sectorCount];

        for (int j = 0; j < sectorCount; ++j)
        {
            float x = (float)i / (stackCount - 1);
            float y = (float)j / (sectorCount - 1);

            vertices[i][j] = new Vertex(x, y, 0.0f);
            vertices[i][j]->setNormal(x, y, 0.0f);
            vertices[i][j]->setTexturePos(x, y);
        }
    }
}

void Sphere::printVertices()
{
    for (int i = 0; i < stackCount; ++i)
    {
        for (int j = 0; j < sectorCount; ++j)
        {
            Vertex *vertex = vertices[i][j];
            printVertex(vertex);
        }
    }
}

void Sphere::printVertex(Vertex *vertex)
{
    std::cout << "x: " << vertex->x << ", y: " << vertex->y << ", z: " << vertex->z << "\n";
}

void Sphere::displayVertices()
{
    glBegin(GL_POINTS);

    glColor3ub(255, 255, 255);

    for (int i = 0; i < stackCount; ++i)
    {
        for (int j = 0; j < sectorCount; ++j)
        {
            Vertex *vertex = vertices[i][j];
            glVertex3f(vertex->x, vertex->y, vertex->z);
        }
    }
    glEnd();
}

void Sphere::drawNormal(Vertex *v)
{
    Vector3f *n = v->normal;

    // Red drawing color
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);

    glVertex3f(v->x, v->y, v->z);
    glVertex3f(v->x + n->x, v->y + n->y, v->z + n->z);

    glEnd();
}

void Sphere::addVertex(Vertex *v)
{
    glColor3ub(255, 255, 255);

    Vector3f *normal = v->normal;

    glNormal3f(normal->x, normal->y, normal->z);

    glTexCoord2fv(v->texturePos);
    glVertex3f(v->x, v->y, v->z);
}

void Sphere::displayMesh(GLenum mode)
{

    for (int i = 0; i < stackCount - 1; ++i)
    {
        for (int j = 0; j < sectorCount - 1; ++j)
        {

            // this vertex
            int x1 = i;
            int y1 = j;
            Vertex *vertex1 = vertices[x1][y1];

            // top neighbor
            int x2 = (i + 1) % stackCount;
            int y2 = j;
            Vertex *vertex2 = vertices[x2][y2];

            // top-right neighbor
            int x3 = (i + 1) % sectorCount;
            int y3 = j + 1;
            Vertex *vertex3 = vertices[x3][y3];

            // right neighbor

            int x4 = i;
            int y4 = j + 1;
            Vertex *vertex4 = vertices[x4][y4];

            if (drawNormals)
            {
                drawNormal(vertices[i][j]);
            }

            glBegin(mode);

            addVertex(vertex1);
            addVertex(vertex2);
            addVertex(vertex3);
            addVertex(vertex1);
            addVertex(vertex4);
            addVertex(vertex3);

            glEnd();
        }
    }
}

void Sphere::display()
{
    switch (displayMode)
    {
    case DisplayMode::vertices:
        displayVertices();
        break;
    case DisplayMode::mesh:
        displayMesh(GL_LINE_STRIP);
        break;
    case DisplayMode::filledTriangles:
        displayMesh(GL_TRIANGLE_STRIP);
        break;
    }
}

void Sphere::setDisplayMode(DisplayMode mode)
{
    this->displayMode = mode;
}
