#pragma once

class Window;
class UICore;

class RendererException : public std::exception
{
public:
	RendererException() = delete;
	RendererException(const char* msg) : std::exception(msg) {}
};

class Renderer
{
public:

	enum class Type
	{
		DX9,
		DX10,
		DX11,
		DX12,
		Vulkan,
		GL,
	};

	static Renderer* Create(Type type);

	// Render steps
	virtual bool Initialize(Window* window, UICore* ui) = 0;
	virtual Type GetType() = 0;
	virtual void BeginScene() = 0;
	virtual void Present() = 0;
	virtual void EndScene() = 0;
	virtual void Release() = 0;

	// Stuff for adding textures/models/voxels/etc here
};