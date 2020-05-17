#pragma once

#include "UIWindow.h"

// Controls the user interface for ImGui, ultimately passed to the renderer

class Window;
class Renderer;

class UICoreException : public std::exception
{
public:
	UICoreException() = delete;
	UICoreException(const char* msg) : std::exception(msg) {}
};

class UICore
{
public:
	//
	static UICore* Create(Window* win, Renderer* rend);

	//
	void AddWindow(UIWindow* win);

	//
	virtual void PrepareFrame();
	virtual void PrepareUI();
	virtual void FinishFrame();
	virtual void PresentFrame();
	virtual void Destroy();

protected:
	virtual bool Initialize(Window* win, Renderer* rend) = 0;

	std::vector<UIWindow*> m_windows;
};