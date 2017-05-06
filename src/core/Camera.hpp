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

struct Camera
{
    GLboolean EDITOR_MODE = false;

    GLfloat low_camera_speed = 0.6f;
    GLfloat max_camera_speed = 1.0f;
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

    Camera() : MAPA{}
    {
        memset(MAPA, 0, sizeof(MAPA[0][0]) * 14 * 15);
    }

    void Move(HWND hWnd)
    {
        float tmpz;
        float tmpx;

        if (SPACE)
        {
            tmpz = (*camera_speed) * cos(DEG2RAD * alfa) * cos(DEG2RAD * beta);
            tmpx = sin(DEG2RAD * alfa) * cos(DEG2RAD * beta) * (*camera_speed);

            TestMap(camera_x + tmpx * 10, camera_z - tmpz * 10, true);
            SPACE = false;
        }

        if (RIGHT)
        {
            alfa += 2;
        }

        if (LEFT)
        {
            alfa -= 2;
        }

        if (W)
        {
            tmpz = (*camera_speed) * cos(DEG2RAD * alfa) * cos(DEG2RAD * beta);

            if (EDITOR_MODE || TestMap(camera_x, camera_z - tmpz * 10))
                camera_z -= tmpz;

            tmpx = sin(DEG2RAD * alfa) * cos(DEG2RAD * beta) * (*camera_speed);

            if (EDITOR_MODE || TestMap(camera_x + tmpx * 10, camera_z))
                camera_x += tmpx;

            // camera_y -= sin(DEG2RAD*beta) * (*camera_speed);
        }

        if (S)
        {
            tmpz = (*camera_speed) * cos(DEG2RAD * alfa) * cos(DEG2RAD * beta);

            if (EDITOR_MODE || TestMap(camera_x, camera_z + tmpz * 10))
                camera_z += tmpz;

            tmpx = sin(DEG2RAD * alfa) * cos(DEG2RAD * beta) * (*camera_speed);

            if (EDITOR_MODE || TestMap(camera_x - tmpx * 10, camera_z))
                camera_x -= tmpx;
        }

        if (A)
        {
            tmpz = (*camera_speed) * cos(DEG2RAD * (alfa + 90)) *
                   cos(DEG2RAD * (beta));

            if (EDITOR_MODE || TestMap(camera_x, camera_z + tmpz * 10))
                camera_z += tmpz;

            tmpx = sin(DEG2RAD * (alfa + 90)) * cos(DEG2RAD * (beta)) *
                   (*camera_speed);

            if (EDITOR_MODE || TestMap(camera_x - tmpx * 10, camera_z))
                camera_x -= tmpx;
        }

        if (D)
        {
            tmpz = (*camera_speed) * cos(DEG2RAD * (alfa + 90)) *
                   cos(DEG2RAD * (beta));

            if (EDITOR_MODE || TestMap(camera_x, camera_z - tmpz * 10))
                camera_z -= tmpz;

            tmpx = sin(DEG2RAD * (alfa + 90)) * cos(DEG2RAD * (beta)) *
                   (*camera_speed);

            if (EDITOR_MODE || TestMap(camera_x + tmpx * 10, camera_z))
                camera_x += tmpx;
        }

        if (Q)
        {
            camera_y += (*camera_speed);
        }

        if (E)
        {
            camera_y -= (*camera_speed);
        }
        if (SHIFT)
        {
            camera_speed = &max_camera_speed;
        }
        else
        {
            camera_speed = &low_camera_speed;
        }
        Refresh(hWnd);
    }

    void Hud(HWND hWnd)
    {
        // glDisable(GL_DEPTH_TEST);
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();

        RECT rcClient;

        GetClientRect(hWnd, &rcClient);

        width = rcClient.right - rcClient.left;
        height = rcClient.bottom - rcClient.top;

        glOrtho(0, width, height, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    void Refresh(HWND hWnd)
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glViewport(0, 0, width, height);

        // glFrustum( - 0.05 * width / 800.0f , 0.05 * width / 800.0f, - 0.0375
        // * height / 600.0f, 0.0375 * height / 600.0f , 0.1, 1500.0 );
        glFrustum(-0.05 * width / 650.0f,
                  0.05 * width / 650.0f,
                  -0.0375 * height / 450.0f,
                  0.0375 * height / 450.0f,
                  0.05,
                  1500.0);

        x = camera_x + sin(DEG2RAD * alfa) * cos(DEG2RAD * beta);
        y = camera_y - sin(DEG2RAD * beta);
        z = camera_z - cos(DEG2RAD * alfa) * cos(DEG2RAD * beta);

        gluLookAt(camera_x, camera_y, camera_z, x, y, z, 0, 1, 0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    // 0 pusto, 1 drzwi, 2 sciana
    void MapCreate()
    {
        for (int i = 1; i < 13; ++i)
        {
            MAPA[i][0] = 2; // zaznaczenie  ian
            MAPA[i][14] = 2;
            for (int k = 1; k < 14; ++k) // zaznaczenie gdzie mozna chodzic
            {
                MAPA[i][k] = 0;
            }
        }
        for (int i = 0; i < 15; ++i)
        {
            MAPA[0][i] = 2;
            MAPA[13][i] = 2;
        }
        for (int i = 4; i < 13; ++i)
        {
            MAPA[i][5] = 2;
            MAPA[i][9] = 2;
        }
        for (int i = 1; i < 5; ++i)
        {
            MAPA[4][i] = 2;
            MAPA[8][i] = 2;
            MAPA[4][i + 9] = 2;
            MAPA[8][i + 9] = 2;
        }

        MAPA[6][5] = 1;
        MAPA[11][5] = 1;

        MAPA[6][9] = 1;
        MAPA[11][9] = 1;

        //MessageBox(NULL, "MAPA stworzona", NULL, NULL);
    }

    inline bool TestMap(float x, float z, bool door = false)
    {

        if (door == true)
        {
            /*
            MAPA[6][5] = 1;
            MAPA[11][5] = 1;

            MAPA[6][9] = 1;
            MAPA[11][9] = 1;
            */

            int test_x = (int)(x + 10) / 10;
            int test_z = (int)(z - 10) / 10;
            if ((test_x == 6 && test_z == 5) ||
                (test_x == 11 && test_z == 5) || // 0 2
                (test_x == 6 && test_z == 9) ||
                (test_x == 11 && test_z == 9)) // 1 3
            {
                int whichDoor = 0;
                whichDoor += (test_x == 6 ? 0 : 2);
                whichDoor += (test_z == 5 ? 0 : 1);
                CLOSE[whichDoor] = !CLOSE[whichDoor];
                MAPA[test_x][test_z] = CLOSE[whichDoor];
                return true;
            }
            else
                return false;
        }
        else
        {
            if (MAPA[(int)(x + 10) / 10][(int)(z - 10) / 10] == 0)
                return true;
            else
                return false;
        }
    }
};
