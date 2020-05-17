// game.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "game.h"

    // 

    /*int gui::center_window(HWND parent_window, int width, int height)
{
    GetClientRect(parent_window, &rect);
    rect.left = (rect.right/2) - (width/2);
    rect.top = (rect.bottom/2) - (height/2);
    return 0;
}
*/

bool GetCenterScreen(AABB2D<Float>* rect)
{
    const Float dw = (GetSystemMetrics(SM_CXSCREEN)) / 2.0f;
    const Float dh = (GetSystemMetrics(SM_CYSCREEN)) / 2.0f;

    const Float mx = dw - (rect->GetWidth() / Float(2.0f));
    const Float my = dh - (rect->GetHeight() / Float(2.0f));

    rect->SetX(mx);
    rect->SetY(my);

    return true;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    AABB2D<Float> screenPos;

    screenPos.SetX(0.0f);
    screenPos.SetY(0.0f);
    screenPos.SetWidth(1600.0f);
    screenPos.SetHeight(900.0f);

    if (!GetCenterScreen(&screenPos))
    {
        MessageBox(nullptr, TEXT("Unable to determine window start position."), TEXT("ERROR"), MB_OK);
        return -1;
    }

    Window* win = Window::Create(screenPos.GetX(), screenPos.GetY(), screenPos.GetWidth(), screenPos.GetHeight());

    if (!win)
    {
        MessageBox(nullptr, TEXT("Unable to create window."), TEXT("ERROR"), MB_OK);
        return -1;
    }

    Renderer* rend = Renderer::Create(win, Renderer::Type::DX9);

    if (!rend)
    {
        MessageBox(nullptr, TEXT("Unable to create renderer."), TEXT("ERROR"), MB_OK);
        return -1;
    }

    rend->GetUI()->AddWindow(new UIStatsWindow);

    while (true)
    {
        if (!win->MessageLoop())
            break;

        rend->BeginScene();
        rend->EndScene();
        rend->Present();
    }

    return 0;
}