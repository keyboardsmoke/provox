#include "pch.h"
#include "Renderer/Renderer.h"
#include "DX9Renderer.h"
#include "Window/window.h"
#include "UI/UICore.h"

DX9Renderer::DX9Renderer()
{
	//
}

bool DX9Renderer::Initialize(Window* window, UICore* ui)
{
	m_window = window;
	m_ui = ui;

	IDirect3D9* dp = Direct3DCreate9(D3D_SDK_VERSION);

	if (dp == nullptr)
	{
		throw RendererException("Unable to initialize D3D9 object.");

		return false;
	}

	HWND hWnd = reinterpret_cast<HWND>(window->GetHandle());

	D3DPRESENT_PARAMETERS pp = { 0 };

	pp.BackBufferCount = 1;
	pp.MultiSampleType = D3DMULTISAMPLE_NONE;
	pp.MultiSampleQuality = 0;
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pp.hDeviceWindow = hWnd;
	pp.Flags = 0;
	pp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	pp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	pp.BackBufferFormat = D3DFMT_A8R8G8B8;
	pp.EnableAutoDepthStencil = FALSE;

	pp.Windowed = TRUE;
	pp.BackBufferWidth = static_cast<UINT>(window->GetWidth());
	pp.BackBufferHeight = static_cast<UINT>(window->GetHeight());

	if (FAILED(dp->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&pp,
		&m_dev)))
	{
		throw RendererException("Unable to initialize D3D9 device.");

		return false;
	}

	return true;
}

void DX9Renderer::BeginScene()
{
	m_ui->PrepareFrame();
	m_ui->PrepareUI();
	m_ui->FinishFrame();

	if (FAILED(m_dev->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 0, 0, 0), 1.0f, 0)))
	{
		throw RendererException("Failed to clear scene");
	}

	if (FAILED(m_dev->BeginScene()))
	{
		throw RendererException("Failed to begin scene");
	}
}

void DX9Renderer::Present()
{
	if (FAILED(m_dev->Present(nullptr, nullptr, nullptr, nullptr)))
	{
		throw RendererException("Failed to present scene");
	}
}

void DX9Renderer::EndScene()
{
	m_ui->PresentFrame();

	if (FAILED(m_dev->EndScene()))
	{
		throw RendererException("Failed to end scene");
	}
}

void DX9Renderer::Release()
{
	if (m_dev)
	{
		m_dev->Release();
		m_dev = nullptr;
	}

	if (m_dp)
	{
		m_dp->Release();
		m_dp = nullptr;
	}
}