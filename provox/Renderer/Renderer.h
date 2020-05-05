#pragma once

class Window;
class Renderer
{
public:

	enum class Type
	{
		DX9,
		DX10,
		DX11,
		GL,
	};

	static Renderer* Create(Type type);

	virtual bool Initialize(Window* window) = 0;
};