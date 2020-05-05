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

    //
    Window* win = Window::Create(0, 0, 640, 480);

    if (!win)
    {
        MessageBox(nullptr, TEXT("Unable to create window."), TEXT("ERROR"), MB_OK);
        return -1;
    }

    while (true)
    {
        if (!win->MessageLoop())
            break;
    }

    return 0;
}