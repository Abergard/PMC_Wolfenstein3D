////////////////////////////////////////
// My includes
#include "Graphics.hpp"
////////////////////////////////////////

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
};

void EnableOpenGL(HWND hWnd, HDC* hDC, HGLRC* hRC);
void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC);
extern void DeleteBMP();

////////////////////////////////////////
extern GLboolean EDITOR_MODE;

extern GLboolean W;
extern GLboolean S;
extern GLboolean A;
extern GLboolean D;
extern GLboolean Q;
extern GLboolean E;
extern GLboolean SHIFT;
extern GLboolean RIGHT;
extern GLboolean LEFT;
extern GLboolean SPACE;

extern int oldMouseY;
extern int oldMouseX;
extern int mouseY;
extern int mouseX;

extern bool rightMouseClick;

extern GLfloat alfa;
extern GLfloat beta;

extern GLdouble camera_y;

int MainC::initialize(HINSTANCE hInstance)
{
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

    if (hWnd == nullptr)
    {
        MessageBox(nullptr,
                   "Proba utworzenia okna nie powiodla sie!",
                   "Create Error",
                   MB_ICONEXCLAMATION);
        return 1;
    }

    // enable OpenGL for the window
    EnableOpenGL(hWnd, &hDC, &hRC);

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
            Display(hDC, hWnd);
        }
    }

    DisableOpenGL(hWnd, hDC, hRC);

    DestroyWindow(hWnd);
    return msg.wParam;
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

    auto* pState =
        reinterpret_cast<MainC*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    return pState->realWndProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK MainC::realWndProc(HWND hWnd,
                                    UINT message,
                                    WPARAM wParam,
                                    LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        MapCreate();
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
            SPACE = true;
            break;

        case VK_RIGHT:
            RIGHT = true;
            break;

        case VK_LEFT:
            LEFT = true;
            break;

        case 'Q':
            if (EDITOR_MODE)
                Q = true;
            break;

        case 'E':
            if (EDITOR_MODE)
                E = true;
            break;

        case 'W':
            W = true;
            break;

        case 'S':
            S = true;
            break;

        case 'A':
            A = true;
            break;

        case 'D':
            D = true;
            break;

        case VK_SHIFT:
            SHIFT = true;
            break;

        case VK_RETURN:
            if (EDITOR_MODE)
            {
                // alfa = 180;
                beta = 0;

                camera_y = 5;
                // camera_z = 25;

                EDITOR_MODE = false;
            }
            else
                EDITOR_MODE = true;
            break;
        }
    }
        return 0;

    case WM_KEYUP:
    {
        switch (wParam)
        {

        case VK_RIGHT:
            RIGHT = false;
            break;

        case VK_LEFT:
            LEFT = false;
            break;

        case 'W':
            W = false;
            break;
        case 'S':
            S = false;
            break;
        case 'A':
            A = false;
            break;
        case 'D':
            D = false;
            break;
        case 'Q':
            Q = false;
            break;
        case 'E':
            E = false;
            break;
        case VK_SHIFT:
            SHIFT = false;
            break;
        }
    }
        return 0;

    case WM_RBUTTONDOWN:
    {
        rightMouseClick = true;
        mouseX = LOWORD(lParam);
        mouseY = HIWORD(lParam);
        SendMessage(hWnd, WM_MOUSEMOVE, wParam, lParam);
    }
        return 0;

    case WM_RBUTTONUP:
        rightMouseClick = false;
        return 0;

    case WM_MOUSEMOVE:
    {
        if (rightMouseClick && EDITOR_MODE)
        {
            // save old mouse coordinates
            oldMouseX = mouseX;
            oldMouseY = mouseY;

            // get mouse coordinates from Windows
            mouseX = LOWORD(lParam);
            mouseY = HIWORD(lParam);

            int diff_x = mouseX - oldMouseX;
            int diff_y = mouseY - oldMouseY;

            alfa += diff_x / 1.7;
            if (EDITOR_MODE)
                beta += diff_y / 1.7;

            PostMessage(hWnd, WM_SIZE, wParam, lParam);
        }
    }
        return 0;

    case WM_SETCURSOR:
    {
        if (EDITOR_MODE)
            SetCursor(wc.hCursor);
        else
            SetCursor(nullptr);
    }
        return TRUE;

    case WM_SIZE:
    {
        Refresh(hWnd);
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
