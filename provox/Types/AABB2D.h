#pragma once

#include "Vector2D.h"

template<typename T>
class AABB2D
{
public:
	AABB2D() : m_min(0.0F, 0.0F), m_max(0.0F, 0.0F) {}
	AABB2D(const Vector2D<T>& min, const Vector2D<T>& max) : m_min(min), m_max(max) {}
	AABB2D(const Float X, const Float Y, const Float W, const Float H) :
		m_min(X, Y), m_max(X + W, Y + H) {}

	T GetX()
	{
		return Min().x;
	}

	T GetY()
	{
		return Min().y;
	}

	T GetWidth()
	{
		return m_max.x - m_min.x;
	}

	T GetHeight()
	{
		return m_max.y - m_min.y;
	}

	void SetX(T x)
	{
		m_max.x -= m_min.x;
		m_min.x = x;
		m_max.x += m_min.x;
	}

	void SetY(T y)
	{
		m_max.y -= m_min.y;
		m_min.y = y;
		m_max.y += m_min.y;
	}

	void SetWidth(T width)
	{
		m_max.x = (m_min.x + width);
	}

	void SetHeight(T height)
	{
		m_max.y = (m_min.y + height);
	}

	Vector2D<T>& Min()
	{
		return m_min;
	}

	Vector2D<T>& Max()
	{
		return m_max;
	}

	AABB2D operator+(const Vector2D<T>& pt) const
	{
		AABB2D a;
		a.m_min = m_min + pt;
		a.m_max = m_max + pt;
		return a;
	}

	AABB2D operator-(const Vector2D<T>& pt) const
	{
		AABB2D a;
		a.m_min = m_min - pt;
		a.m_max = m_max - pt;
		return a;
	}

private:
	Vector2D<T> m_min;
	Vector2D<T> m_max;
};