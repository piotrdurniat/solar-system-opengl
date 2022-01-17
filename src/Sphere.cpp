#include "Sphere.hpp"

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

Sphere::Sphere(int n, bool drawNormals)
{
    this->n = n;

    setupVerticesOnPlane();
    transformVertices();
    calculateNormals();
    invertHalfOfTheNormals();
    this->drawNormals = drawNormals;
}

void Sphere::transformVertices()
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            Vertex *vertex = vertices[i][j];
            float u = vertex->x;
            float v = vertex->y;

            vertex->x = (-90.0 * pow(u, 5) + 225.0 * pow(u, 4) - 270.0 * pow(u, 3) + 180.0 * pow(u, 2) - 45.0 * u) * cos(M_PI * v);
            vertex->y = (160.0 * pow(u, 4) - 320.0 * pow(u, 3) + 160.0 * pow(u, 2));
            vertex->z = (-90.0 * pow(u, 5) + 225.0 * pow(u, 4) - 270.0 * pow(u, 3) + 180.0 * pow(u, 2) - 45.0 * u) * sin(M_PI * v);
        }
    }
}

void Sphere::calculateNormals()
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            Vector3f *normal = vertices[i][j]->normal;
            float u = normal->x;
            float v = normal->y;

            float x_u = (-450.0 * pow(u, 4) + 900.0 * pow(u, 3) - 810.0 * pow(u, 2) + 360.0 * u - 45.0) * cos(M_PI * v);
            float x_v = M_PI * (90.0 * pow(u, 5) - 225.0 * pow(u, 4) + 270.0 * pow(u, 3) - 180.0 * pow(u, 2) + 45.0 * u) * sin(M_PI * v);
            float y_u = 640.0 * pow(u, 3) - 960.0 * pow(u, 2) + 320.0 * u;
            float y_v = 0.0;
            float z_u = (-450.0 * pow(u, 4) + 900.0 * pow(u, 3) - 810.0 * pow(u, 2) + 360.0 * u - 45.0) * sin(M_PI * v);
            float z_v = -M_PI * (90.0 * pow(u, 5) - 225.0 * pow(u, 4) + 270.0 * pow(u, 3) - 180.0 * pow(u, 2) + 45.0 * u) * cos(M_PI * v);

            normal->x = y_u * z_v - z_u * y_v;
            normal->y = z_u * x_v - x_u * z_v;
            normal->z = x_u * y_v - y_u * x_v;

            if (normal->x == 0.0 && normal->y == 0.0 && normal->z == 0)
            {
                Vertex *v = vertices[i][j];
                if (v->y == 0.0)
                {
                    normal->y = -1.0;
                }
                else
                {
                    normal->y = 1.0;
                }
            }

            normal->normalize();
        }
    }
}

void Sphere::setupVerticesOnPlane()
{
    vertices = new Vertex **[n];

    for (int i = 0; i < n; ++i)
    {
        vertices[i] = new Vertex *[n];

        for (int j = 0; j < n; ++j)
        {
            float x = (float)i / (n - 1);
            float y = (float)j / (n - 1);

            vertices[i][j] = new Vertex(x, y, 0.0f);
            vertices[i][j]->setNormal(x, y, 0.0f);
            vertices[i][j]->setTexturePos(x, y);
        }
    }
}

void Sphere::printVertices()
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
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

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
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
    Vector3f *normal = v->normal;

    glNormal3f(normal->x, normal->y, normal->z);

    glTexCoord2fv(v->texturePos);
    glVertex3f(v->x, v->y, v->z);
}

void Sphere::displayMesh(GLenum mode)
{

    glColor3ub(255, 255, 255);

    for (int j = 0; j < n - 1; ++j)
    {
        for (int i = 0; i < n; ++i)
        {

            // this vertex
            int x1 = i;
            int y1 = j;
            Vertex *vertex1 = vertices[x1][y1];

            // top neighbor
            int x2 = (i + 1) % n;
            int y2 = j;
            Vertex *vertex2 = vertices[x2][y2];

            // top-right neighbor
            int x3 = (i + 1) % n;
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
            // glColor3ub(255, 255, 255);

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

    // Fill in the missing column
    {
        for (int i = 0; i < n; ++i)
        {
            // this vertex
            int x1 = i;
            int y1 = n - 1;
            Vertex *vertex1 = vertices[x1][y1];

            // top neighbor
            // int x2 = i + 1;
            int x2 = (i + 1) % n;
            int y2 = n - 1;
            Vertex *vertex2 = vertices[x2][y2];

            // top-right neighbor
            int x3 = n - i - 1;
            int y3 = 0;
            Vertex *vertex3 = vertices[x3][y3];

            // right neighbor
            int x4 = (n - i) % n;
            int y4 = 0;
            Vertex *vertex4 = vertices[x4][y4];

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
    glTranslatef(0, -5, 0);

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

void Sphere::invertHalfOfTheNormals()
{
    for (int i = n / 2; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            Vector3f *normal = vertices[i][j]->normal;
            if (normal->y != -1 && normal->y != 1)
            {
                normal->invert();
            }
        }
    }
}
