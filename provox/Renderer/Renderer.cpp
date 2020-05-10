#include "pch.h"
#include "Renderer.h"
#include "DX9Renderer/DX9Renderer.h"
#include "Window/Window.h"

Renderer* Renderer::Create(Type type)
{
	if (type == Type::DX9)
	{
		return new DX9Renderer();
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

	return nullptr;
}