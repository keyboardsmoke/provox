#pragma once

template<typename T>
class Rect
{
public:
	Rect() : x(), y(), w(), h() {}
	Rect(T x, T y, T width, T height) : x(x), y(y), w(width), h(height) {}

	T x, y, w, h;
};