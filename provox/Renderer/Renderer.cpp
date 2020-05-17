#include "pch.h"
#include "Renderer.h"
#include "DX9Renderer/DX9Renderer.h"
#include "Window/Window.h"

Renderer* Renderer::Create(Window* window, Type type)
{
	Renderer* renderer = nullptr;

	if (type == Type::DX9)
	{
		renderer = new DX9Renderer();
	}
	else if (type == Type::DX10)
	{
		throw RendererException("DX10 renderer not yet supported.");
	}
	else if (type == Type::DX11)
	{
		throw RendererException("DX11 renderer not yet supported.");
	}
	else if (type == Type::DX12)
	{
		throw RendererException("DX12 renderer not yet supported.");
	}
	else if (type == Type::Vulkan)
	{
		throw RendererException("Vulkan renderer not yet supported.");
	}
	else if (type == Type::GL)
	{
		throw RendererException("OpenGL renderer not yet supported.");
	}

	if (renderer != nullptr)
	{
		renderer->m_window = window;

		if (!renderer->Initialize())
		{
			throw RendererException("Unable to initialize renderer.");

			delete renderer;

			renderer = nullptr;
		}
	}

	return renderer;
}