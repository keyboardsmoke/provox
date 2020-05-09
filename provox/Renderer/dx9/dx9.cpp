#include "pch.h"
#include "Renderer/Renderer.h"
#include "dx9.h"
#include "Window/window.h"

DX9Renderer::DX9Renderer()
{
	//
}

bool DX9Renderer::Initialize(Window* window)
{
	IDirect3D9* dp = Direct3DCreate9(D3D_SDK_VERSION);

	if (dp == nullptr)
	{
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
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&pp,
		&m_dev)))
	{
		return false;
	}

	return false;
}

/*   pp.BackBufferCount= 1;  //We only need a single back buffer

   pp.MultiSampleType=D3DMULTISAMPLE_NONE; //No multi-sampling

   pp.MultiSampleQuality=0;                //No multi-sampling

   pp.SwapEffect = D3DSWAPEFFECT_DISCARD;  // Throw away previous frames, we don't need them

   pp.hDeviceWindow=wnd;  //This is our main (and only) window

   pp.Flags=0;            //No flags to set

   pp.FullScreen_RefreshRateInHz=D3DPRESENT_RATE_DEFAULT; //Default Refresh Rate

   pp.PresentationInterval=D3DPRESENT_INTERVAL_DEFAULT;   //Default Presentation rate

   pp.BackBufferFormat=format;      //Display format

   pp.EnableAutoDepthStencil=FALSE; //No depth/stencil buffer*/