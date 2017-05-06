#include "Window.hpp"

int Window::initialize(HINSTANCE hInstance)
{
    constexpr auto class_name = "GL tutorial";

    GLfloat WIDTH = 650;
    GLfloat HEIGHT = 450;

    auto wndProc =
        [](HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
            if (auto* main = reinterpret_cast<Window*>(
                    GetWindowLongPtr(window, GWLP_USERDATA)))
            {
                return main->realWndProc(window, message, wParam, lParam);
            }
            return DefWindowProc(window, message, wParam, lParam);
        };

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = wndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = class_name;
    wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

    if (!RegisterClassEx(&wc))
    {
        MessageBox(nullptr,
                   "Rejestracja okna nie powiodla sie!",
                   "Register Error",
                   MB_OK | MB_ICONEXCLAMATION);
        return 1;
    }

    // WS_OVERLAPPEDWINDOW WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX /
    // WS_CAPTION | WS_POPUPWINDOW
    window = CreateWindowEx(WS_EX_CLIENTEDGE,
                            class_name,
                            "MagicBox",
                            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                            CW_USEDEFAULT,
                            CW_USEDEFAULT,
                            WIDTH,
                            HEIGHT,
                            nullptr,
                            nullptr,
                            hInstance,
                            nullptr);

    if (window == nullptr)
    {
        MessageBox(nullptr,
                   "Proba utworzenia okna nie powiodla sie!",
                   "Create Error",
                   MB_ICONEXCLAMATION);
        return 1;
    }

    SetWindowLongPtr(window, GWLP_USERDATA, (LONG_PTR)this);
    camera.MapCreate();
    EnableOpenGL();
    return 0;
}

HWND Window::get_id() const
{
    return window;
}

void Window::swapBuffer()
{
    SwapBuffers(device_context);
}

Camera& Window::get_camera()
{
    return camera;
}

LRESULT CALLBACK Window::realWndProc(HWND window,
                                     UINT message,
                                     WPARAM wParam,
                                     LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        PostMessage(window, WM_SIZE, wParam, lParam);
        return 0;

    case WM_CLOSE:
        DestroyWindow(window);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            break;

        case VK_SPACE:
            camera.SPACE = true;
            break;

        case VK_RIGHT:
            camera.RIGHT = true;
            break;

        case VK_LEFT:
            camera.LEFT = true;
            break;

        case 'Q':
            if (camera.EDITOR_MODE)
                camera.Q = true;
            break;

        case 'E':
            if (camera.EDITOR_MODE)
                camera.E = true;
            break;

        case 'W':
            camera.W = true;
            break;

        case 'S':
            camera.S = true;
            break;

        case 'A':
            camera.A = true;
            break;

        case 'D':
            camera.D = true;
            break;

        case VK_SHIFT:
            camera.SHIFT = true;
            break;

        case VK_RETURN:
            if (camera.EDITOR_MODE)
            {
                // camera.alfa = 180;
                camera.beta = 0;

                camera.camera_y = 5;
                // camera_z = 25;

                camera.EDITOR_MODE = false;
            }
            else
                camera.EDITOR_MODE = true;
            break;
        }
    }
        return 0;

    case WM_KEYUP:
    {
        switch (wParam)
        {

        case VK_RIGHT:
            camera.RIGHT = false;
            break;

        case VK_LEFT:
            camera.LEFT = false;
            break;

        case 'W':
            camera.W = false;
            break;
        case 'S':
            camera.S = false;
            break;
        case 'A':
            camera.A = false;
            break;
        case 'D':
            camera.D = false;
            break;
        case 'Q':
            camera.Q = false;
            break;
        case 'E':
            camera.E = false;
            break;
        case VK_SHIFT:
            camera.SHIFT = false;
            break;
        }
    }
        return 0;

    case WM_RBUTTONDOWN:
    {
        camera.rightMouseClick = true;
        camera.mouseX = LOWORD(lParam);
        camera.mouseY = HIWORD(lParam);
        SendMessage(window, WM_MOUSEMOVE, wParam, lParam);
    }
        return 0;

    case WM_RBUTTONUP:
        camera.rightMouseClick = false;
        return 0;

    case WM_MOUSEMOVE:
    {
        if (camera.rightMouseClick && camera.EDITOR_MODE)
        {
            // save old mouse coordinates
            camera.oldMouseX = camera.mouseX;
            camera.oldMouseY = camera.mouseY;

            // get mouse coordinates from Windows
            camera.mouseX = LOWORD(lParam);
            camera.mouseY = HIWORD(lParam);

            int diff_x = camera.mouseX - camera.oldMouseX;
            int diff_y = camera.mouseY - camera.oldMouseY;

            camera.alfa += diff_x / 1.7;
            if (camera.EDITOR_MODE)
                camera.beta += diff_y / 1.7;

            PostMessage(window, WM_SIZE, wParam, lParam);
        }
    }
        return 0;

    case WM_SETCURSOR:
    {
        if (camera.EDITOR_MODE)
            SetCursor(wc.hCursor);
        else
            SetCursor(nullptr);
    }
        return TRUE;

    case WM_SIZE:
    {
        camera.Refresh(window);
    }
        return 0;

    default:
        return DefWindowProc(window, message, wParam, lParam);
    }
}

void Window::uninitialize()
{
    DisableOpenGL();
    DestroyWindow(window);
}

// Enable OpenGL
void Window::EnableOpenGL()
{
    PIXELFORMATDESCRIPTOR pfd;
    int format;

    // get the device device_context (DC)
    device_context = GetDC(window);

    // set the pixel format for the DC
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    format = ChoosePixelFormat(device_context, &pfd);
    SetPixelFormat(device_context, format, &pfd);

    // create and enable the render device_context (RC)
    render_context = wglCreateContext(device_context);
    wglMakeCurrent(device_context, render_context);

    glPointSize(4.0f);
    glLineWidth(4.0f);
}

void Window::DisableOpenGL()
{
    objectclass.DeleteBMP();
    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(render_context);
    ReleaseDC(window, device_context);
}
