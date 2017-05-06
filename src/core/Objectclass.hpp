#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl\GLU.h>

struct Objectclass
{
    GLuint loadBMP_custom(const char* imagepath, int numberOfTexture);
    void DeleteBMP();

    void ChooseBMP(int numberOfTexture);
};
