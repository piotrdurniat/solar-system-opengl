#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/freeglut.h>
#include <fstream>

class Texture
{
private:
    GLbyte *pBytes;
    GLint ImWidth, ImHeight, ImComponents;
    GLenum ImFormat;

public:
    void load(const char *fileName);

    void set();

    static GLbyte *LoadTGAImage(const char *FileName, GLint *ImWidth, GLint *ImHeight, GLint *ImComponents, GLenum *ImFormat);
};

#endif
