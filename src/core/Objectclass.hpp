#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl\GLU.h>

GLuint loadBMP_custom(const char* imagepath, int numberOfTexture);
void DeleteBMP();

void ChooseBMP(int numberOfTexture);

/////////////////////////////////////////
class OBJECT_CUBE
{
private:
    /////////////////////////////////////////
    float x, y, z;
    float R, G, B;
    float width;
    float length;
    float height;

    float door_x;
    float door_z;

    /////////////////////////////////////////
    void CreateWall();
    void CreateBars();

public:
    /////////////////////////////////////////
    OBJECT_CUBE(float x,
                float y,
                float z,
                float widht,
                float length,
                float height,
                float R,
                float G,
                float B,
                bool door);
    OBJECT_CUBE(float x,
                float y,
                float z,
                float widht,
                float length,
                float height,
                float R,
                float G,
                float B);
    ~OBJECT_CUBE();

    void CreateDoor(bool front);
    void Move(bool);
};
