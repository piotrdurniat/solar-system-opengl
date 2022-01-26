#include <Viewer.hpp>
#define _USE_MATH_DEFINES
#include <cmath>

Viewer::Viewer()
{
    pos[0] = 0.0;
    pos[1] = 0.0;
    pos[2] = 0.0;

    theta = M_PI / 2;
    phi = M_PI / 4;
    r = 14;
}

void Viewer::thetaAdd(GLfloat x)
{
    theta = theta + x;
}

void Viewer::phiAdd(GLfloat x)
{
    if (phi + x < M_PI / 2 && phi + x > -M_PI / 2)
    {
        phi = phi + x;
    }
}

void Viewer::rAdd(GLfloat x)
{
    if (r + x > 0)
    {
        r = r + x;
    }
}

void Viewer::updatePos()
{
    pos[0] = r * cos(theta) * cos(phi);
    pos[1] = r * sin(phi);
    pos[2] = r * sin(theta) * cos(phi);
    gluLookAt(pos[0], pos[1], pos[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
