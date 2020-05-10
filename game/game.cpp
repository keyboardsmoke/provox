// game.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "game.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    Renderer* rend = Renderer::Create(Renderer::Type::DX9);

    Window* win = Window::Create(0.0f, 0.0f, 640.0f, 480.0f);

    if (!win)
    {
        MessageBox(nullptr, TEXT("Unable to create window."), TEXT("ERROR"), MB_OK);
        return -1;
    }

    if (!rend->Initialize(win))
    {
        MessageBox(nullptr, TEXT("Unable to initialize renderer."), TEXT("ERROR"), MB_OK);
        return -1;
    }

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