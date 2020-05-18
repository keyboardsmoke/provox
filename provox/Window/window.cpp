#include "pch.h"
#include "window.h"
#include "Win32Window.h"
#include "XLibWindow.h"

Window* Window::Create(Float x, Float y, Float width, Float height)
{
    Window* win = nullptr;

#if PROVOX_PLATFORM == PLATFORM_WINDOWS
    win = new Win32Window();
#else
    
#endif

    if (!win->Initialize(x, y, width, height))
    {
        delete win;

        return nullptr;
    }

    return win;
}
