#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl\GLU.h>
#include <gl/gl.h>

#include "Window.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
    Window window;
    if (window.initialize(hInstance))
    {
        return 1;
    }

    BOOL quit = FALSE;
    MSG msg;
    while (!quit)
    {
        // check for messages
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            // handle or dispatch messages
            if (msg.message == WM_QUIT)
            {
                quit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            Display(window, window.get_camera());
        }
    }
    window.uninitialize();
    return static_cast<int>(msg.wParam);
}
