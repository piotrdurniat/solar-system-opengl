#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glut.h>
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

    /*************************************************************************************/
    // Funkcja wczytuje dane obrazu zapisanego w formacie TGA w pliku o nazwie
    // FileName, alokuje pamięć i zwraca wskaźnik (pBits) do bufora w którym
    // umieszczone są dane.
    // Ponadto udostępnia szerokość (ImWidth), wysokość (ImHeight) obrazu
    // tekstury oraz dane opisujące format obrazu według specyfikacji OpenGL
    // (ImComponents) i (ImFormat).
    // Jest to bardzo uproszczona wersja funkcji wczytującej dane z pliku TGA.
    // Działa tylko dla obrazów wykorzystujących 8, 24, or 32 bitowy kolor.
    // Nie obsługuje plików w formacie TGA kodowanych z kompresją RLE.
    /*************************************************************************************/
    static GLbyte *LoadTGAImage(const char *FileName, GLint *ImWidth, GLint *ImHeight, GLint *ImComponents, GLenum *ImFormat);
};

#endif
