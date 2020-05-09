#include "pch.h"
#include <Windows.h>
#include "window.h"
#include "win32.h"

#define PROVOX_WINDOW_NAME L"provox"
#define PROVOX_CLASS_NAME L"provox"

Win32Window::Win32Window()
{

}

Rect<Float> Win32Window::GetRect()
{
	return m_rect;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

bool Win32Window::Initialize(Float x, Float y, Float w, Float h)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = GetModuleHandle(nullptr);
	wcex.hIcon = nullptr;
	wcex.hCursor = nullptr;
	wcex.hbrBackground = (HBRUSH)(GetStockObject(BLACK_BRUSH));
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = PROVOX_CLASS_NAME;
	wcex.hIconSm = nullptr;

	if (RegisterClassEx(&wcex) == 0)
	{
		return false;
	}

	HWND hWnd = CreateWindow(
		PROVOX_CLASS_NAME, PROVOX_WINDOW_NAME,
		// Disable these in windowed mode
		((WS_OVERLAPPEDWINDOW) & ~(WS_MAXIMIZEBOX)) & ~(WS_THICKFRAME),
		static_cast<int>(x), 
		static_cast<int>(y), 
		static_cast<int>(w),
		static_cast<int>(h),
		nullptr,
		nullptr,
		nullptr,
		nullptr);

	m_handle = hWnd;

	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	return true;
}

bool Win32Window::MessageLoop()
{
    MSG msg;

    if (GetMessage(&msg, nullptr, 0, 0) != FALSE)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        return true;
    }

    return false;
}