#pragma once

#include <Windows.h>

#include "Graphics.hpp"
#include "Objectclass.hpp"

class Window
{
public:
    int initialize(HINSTANCE hInstance);
    void uninitialize();
    void swapBuffer();

    HWND get_id() const;
    Camera& get_camera();

private:
    LRESULT CALLBACK realWndProc(HWND hWnd,
                                 UINT message,
                                 WPARAM wParam,
                                 LPARAM lParam);

    void EnableOpenGL();
    void DisableOpenGL();

    WNDCLASSEX wc;
    Camera camera{};
    Objectclass objectclass;

    HWND window;
    HDC device_context;
    HGLRC render_context;
};
