#pragma once

class Window;

#include <d3d9.h>

class DX9Renderer : public Renderer
{
public:
	DX9Renderer();

	bool Initialize(Window* window) override;

private:
	IDirect3D9* m_dp;
	IDirect3DDevice9* m_dev;
	IDirect3DSwapChain9* m_swapchain;
};