#include "pch.h"
#include "window.h"
#include "win32.h"
#include "xlib.h"

Window* Window::Create(uint16 x, uint16 y, uint16 width, uint16 height)
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