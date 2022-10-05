#include "BWindow.h"

BWindow::BWindow() {

}

BWindow::~BWindow() {

}

LRESULT BWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int BWindow::Run(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    m_hInstance = hInstance;

    this->registerWndClass();
    this->createWindow();
    this->showWindow(nCmdShow);
    this->messageLoop();
    
    return 0;
}

int BWindow::messageLoop()
{
    MSG msg;

    memset(&msg, 0, sizeof(msg));

    this->StartUp();

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            MainLoop();
        }
    }

    this->CleanUp();

    return (int)msg.wParam;
}

void BWindow::registerWndClass() {
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = BWindow::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_hInstance;
    wcex.hIcon = LoadIcon(m_hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = TEXT("GameFramework");
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    RegisterClassExW(&wcex);

}

void BWindow::createWindow() {
    m_hWnd = CreateWindowW(TEXT("GameFramework"), TEXT("BounceGum"), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, WINSIZEX, WINSIZEY, nullptr, nullptr, m_hInstance, nullptr);
}

void BWindow::showWindow(int nCmdShow)
{
    ShowWindow(m_hWnd, nCmdShow);
}

HWND BWindow::GetWndHandle()
{
    return m_hWnd;
}

HINSTANCE BWindow::GetInstanceHandle()
{
    return m_hInstance;
}
