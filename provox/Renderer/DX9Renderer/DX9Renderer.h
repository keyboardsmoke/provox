#pragma once

class Window;

#include <d3d9.h>

class DX9Renderer : public Renderer
{
public:
	DX9Renderer();

	bool Initialize(Window* window, UICore* ui) override;
	Type GetType() override { return Type::DX9; }
	void BeginScene() override;
	void Present() override;
	void EndScene() override;
	void Release() override;

	IDirect3D9* GetD3D() { return m_dp; }
	IDirect3DDevice9* GetDevice() { return m_dev; }

private:
	Window* m_window;
	UICore* m_ui;

	IDirect3D9* m_dp;
	IDirect3DDevice9* m_dev;
	IDirect3DSwapChain9* m_swapchain;
};