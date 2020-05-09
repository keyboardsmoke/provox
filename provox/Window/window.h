#pragma once

#include <exception>

class WindowException : public std::exception
{
public:
	WindowException() = delete;
	WindowException(const char* msg) : std::exception(msg) {}
};

class Window
{
public:
	static Window* Create(Float x, Float y, Float width, Float height);

	virtual bool Initialize(Float x, Float y, Float w, Float h) = 0;
	virtual bool MessageLoop() = 0;

	virtual Rect<Float> GetRect() = 0;

	Float GetX() { return GetRect().x; }
	Float GetY() { return GetRect().y; }
	Float GetWidth() { return GetRect().w; }
	Float GetHeight() { return GetRect().h; }

	void* GetHandle() { return m_handle; }

protected:
	void* m_handle;
};