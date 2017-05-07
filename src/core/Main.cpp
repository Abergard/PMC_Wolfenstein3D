#define WIN32_LEAN_AND_MEAN
#define _USE_MATH_DEFINES

#include <Windows.h>
#include <exception>
#include <gl/GLU.h>
#include <gl/gl.h>
#include <string>

#include "Window.hpp"
#include "Graphics.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) try
{
    Window window{hInstance};
    Graphics graphics;
    MSG msg;
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                return static_cast<int>(msg.wParam);
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            graphics.Display(window, window.get_camera());
        }
    }
}
catch (const Window::InitializeError& ex)
{
    MessageBox(nullptr,
               (std::string("Exception: ") + ex.what()).c_str(),
               "Window Initialize Error",
               MB_OK | MB_ICONEXCLAMATION);
    return 1;
}
