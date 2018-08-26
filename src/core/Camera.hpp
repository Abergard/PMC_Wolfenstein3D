#pragma once

#define WIN32_LEAN_AND_MEAN
#define _USE_MATH_DEFINES

#include <Windows.h>
#include <cmath>
#include <gl\GLU.h>

// function
///////////////////////////////////
// globals
// variables

#define SALA1 1

class Camera
{
public:
    Camera();

    void Move(HWND hWnd, double dt);
    void Hud(HWND hWnd);
    void Refresh(HWND hWnd);
    void MapCreate();
    bool TestMap(float x, float z, bool door = false);

public:
    GLboolean EDITOR_MODE = false;

    GLfloat low_camera_speed = 10.6f;
    GLfloat max_camera_speed = 20.0f;
    GLfloat* camera_speed = &low_camera_speed;

    GLdouble camera_x = 55;
    GLdouble camera_y = 5;
    GLdouble camera_z = 35;

    GLboolean W = false;
    GLboolean S = false;
    GLboolean A = false;
    GLboolean D = false;
    GLboolean Q = false;
    GLboolean E = false;
    GLboolean SHIFT = false;
    GLboolean SPACE = false;

    GLboolean RIGHT = false;
    GLboolean LEFT = false;

    int oldMouseY = 0;
    int oldMouseX = 0;
    int mouseY = 0;
    int mouseX = 0;

    bool rightMouseClick = false;

    GLfloat x = 0;
    GLfloat y = 0;
    GLfloat z = 0;

    GLfloat alfa = 180;
    GLfloat beta = 0;

    const float DEG2RAD = M_PI / 180;

    GLsizei width;
    GLsizei height;

    ///////////////////////////////////
    // pokoje

    GLfloat xmin;
    GLfloat xmax;
    GLfloat zmin;
    GLfloat zmax;

    GLboolean DOOR = false;
    GLboolean CLOSE[4]{true, true, true, true};

    ///////////////////////////////////

    char MAPA[14][15];

    ///////////////////////////////////
};
