#ifndef SPHERE_H
#define SPHERE_H

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glut.h>

#include "Vertex.hpp"
#include "DisplayMode.hpp"

class Sphere
{
private:
    int n = 20;
    DisplayMode displayMode = DisplayMode::mesh;
    bool drawNormals;

    // 2d Array holding the vertices of the model:
    Vertex ***vertices;

public:
    Sphere(int n, bool drawNormals);
    // Translate the vertices according to a given formula to form an egg shape
    void transformVertices();
    // Sets up a 2d plain consisting of n x n vertices.
    // Each coordinate (x, y, z) has a value >= 0 and <= 1.
    void setupVerticesOnPlane();
    // prints the position of all the vertices to the standard output
    void printVertices();
    void printVertex(Vertex *v);
    void displayVertices();
    void addVertex(Vertex *v);
    void displayMesh(GLenum mode);
    void display();
    void setDisplayMode(DisplayMode mode);
    void calculateNormals();
    void invertHalfOfTheNormals();
    void drawNormal(Vertex *v);
};

#endif
