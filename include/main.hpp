#pragma once
#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/freeglut.h>

#include <cmath>
#include <iostream>
#include <chrono>
#include <thread>
#include <functional>

#include "LightPoint.hpp"
#include "Viewer.hpp"
#include "CelestialBody.hpp"

static int sectorCount;
static int stackCount;
static Viewer *viewer;
static LightPoint *lightPoint;

static CelestialBody *sun;
static CelestialBody *sky;

const int planetCount = 8;
CelestialBody *planets[planetCount];

typedef float point3[3];

static GLfloat pix2angle = 0.005;

enum class MouseStatus
{
	// No mouse buttons are pressed
	allUp = 0,
	// Left mouse button is pressed
	leftDown = 1,
	// Right mouse button is pressed
	rightDown = 2,
};

static MouseStatus mouseStatus = MouseStatus::allUp;

static int mousePosDiff[2] = {0, 0};
static int mousePosOld[2] = {0, 0};

void drawAxes(void);
void renderScene(void);
void init(void);
void changeSize(GLsizei horizontal, GLsizei vertical);
void mouse(int btn, int state, int x, int y);
void motion(GLsizei x, GLsizei y);
void lightControlMode();
void viewerControlMode();
void keys(unsigned char key, int x, int y);
int main(int argc, char *argv[]);
void setupMaterial();
void loadTexture(const char *fileName);
void timerStart(std::function<void(void)> func, unsigned int interval);
void update(int i);
