////////////////////////////////////////
// My includes
#include "Graphics.hpp"
////////////////////////////////////////
#include <string>
class MainC
{
public:
    int initialize(HINSTANCE hInstance);

private:
    static LRESULT CALLBACK WndProc(HWND hWnd,
                                    UINT message,
                                    WPARAM wParam,
                                    LPARAM lParam);

    LRESULT CALLBACK realWndProc(HWND hWnd,
                                 UINT message,
                                 WPARAM wParam,
                                 LPARAM lParam);

    WNDCLASSEX wc;
    Camera camera{};
};

void EnableOpenGL(HWND hWnd, HDC* hDC, HGLRC* hRC);
void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC);
extern void DeleteBMP();

int MainC::initialize(HINSTANCE hInstance)
{
    MessageBox(nullptr, "start", "Dupa", MB_OK | MB_ICONEXCLAMATION);

    constexpr auto class_name = "GL tutorial";
    MSG msg;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;
    BOOL quit = FALSE;

    GLfloat WIDTH = 650;
    GLfloat HEIGHT = 450;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = this->WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = class_name;
    wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

    MessageBox(nullptr, "start 1.2", "Dupa", MB_OK | MB_ICONEXCLAMATION);

    if (!RegisterClassEx(&wc))
    {
        MessageBox(nullptr,
                   "Rejestracja okna nie powiodla sie!",
                   "Register Error",
                   MB_OK | MB_ICONEXCLAMATION);
        return 1;
    }

    MessageBox(nullptr, "start register", "Dupa", MB_OK | MB_ICONEXCLAMATION);
    // WS_OVERLAPPEDWINDOW WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX /
    // WS_CAPTION | WS_POPUPWINDOW
    hWnd = CreateWindowEx(WS_EX_CLIENTEDGE,
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

    const bool test = hWnd == nullptr;
    const std::string txt = std::to_string(test) + ":start create";
    MessageBox(nullptr, txt.c_str(), "dupa", MB_OK | MB_ICONEXCLAMATION);

    if (hWnd == nullptr)
    {
        MessageBox(nullptr,
                   "Proba utworzenia okna nie powiodla sie!",
                   "Create Error",
                   MB_ICONEXCLAMATION);
        return 1;
    }

    SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);

    // enable OpenGL for the window
    EnableOpenGL(hWnd, &hDC, &hRC);

    camera.MapCreate();
    // program main loop
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
            Display(hDC, hWnd, camera);
        }
    }

    DisableOpenGL(hWnd, hDC, hRC);

    DestroyWindow(hWnd);
    return static_cast<int>(msg.wParam);
}

////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
    MainC main;
    return main.initialize(hInstance);
}

////////////////////////////////////////

LRESULT CALLBACK MainC::WndProc(HWND hWnd,
                                UINT msg,
                                WPARAM wParam,
                                LPARAM lParam)
{
    // auto pointer = GetWindowLongPtr(hWnd, GWLP_USERDATA);
    // auto* me = reinterpret_cast<MainC*>(pointer);
    // if (me)
    // {
    //     MessageBox(nullptr, "Jest Ok", "Create Error", MB_ICONEXCLAMATION);
    //     return me->realWndProc(hWnd, msg, wParam, lParam);
    // }
    // return DefWindowProc(hWnd, msg, wParam, lParam);

    if (auto* main =
            reinterpret_cast<MainC*>(GetWindowLongPtr(hWnd, GWLP_USERDATA)))
    {
        return main->realWndProc(hWnd, msg, wParam, lParam);
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK MainC::realWndProc(HWND hWnd,
                                    UINT message,
                                    WPARAM wParam,
                                    LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        PostMessage(hWnd, WM_SIZE, wParam, lParam);
        return 0;

    case WM_CLOSE:
        DestroyWindow(hWnd);
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
        SendMessage(hWnd, WM_MOUSEMOVE, wParam, lParam);
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

            PostMessage(hWnd, WM_SIZE, wParam, lParam);
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
        camera.Refresh(hWnd);
    }
        return 0;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}

// Enable OpenGL
void EnableOpenGL(HWND hWnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int format;

    // get the device context (DC)
    *hDC = GetDC(hWnd);

    // set the pixel format for the DC
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    format = ChoosePixelFormat(*hDC, &pfd);
    SetPixelFormat(*hDC, format, &pfd);

    // create and enable the render context (RC)
    *hRC = wglCreateContext(*hDC);
    wglMakeCurrent(*hDC, *hRC);

    glPointSize(4.0f);
    glLineWidth(4.0f);
}

// Disable OpenGL
void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC)
{
    DeleteBMP();
    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(hRC);
    ReleaseDC(hWnd, hDC);
}
