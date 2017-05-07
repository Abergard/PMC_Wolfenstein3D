#pragma once

#define WIN32_LEAN_AND_MEAN
#define _USE_MATH_DEFINES

#include <Windows.h>
#include <stdexcept>

#include "Objectclass.hpp"
#include "Camera.hpp"

class Window
{
public:
    class InitializeError : public std::runtime_error
    {
        using std::runtime_error::runtime_error;
    };
    Window(HINSTANCE hInstance);
    ~Window();

    void uninitialize();
    void swapBuffer();

    HWND get_id() const;
    Camera& get_camera();

private:
    LRESULT CALLBACK realWndProc(HWND hWnd,
                                 UINT message,
                                 WPARAM wParam,
                                 LPARAM lParam);

    void enableOpenGL();
    void disableOpenGL();

    WNDCLASSEX wc;
    Camera camera{};
    Objectclass objectclass;

    HWND window;
    HDC device_context;
    HGLRC render_context;
};
