#include "pch.h"
#include "Renderer/Renderer.h"
#include "DX9Renderer.h"
#include "Window/window.h"
#include "UI/UICore.h"
#include <algorithm>
#include <d3d9.h>

// Thanks to windows, gdiplus expects these to exist in the global namespace (as definitions)
// But I'm not letting it pollute because I use NOMINMAX. So, I define them now. Fuckin hell.
template<typename T>
static T min(T a, T b)
{
    return std::min(a, b);
}

template<typename T>
static T max(T a, T b)
{
    return std::max(a, b);
}

#include <gdiplus.h>

#pragma comment(lib, "gdiplus")

DX9Renderer::DX9Renderer()
{
    //
}

bool DX9Renderer::Initialize()
{
    IDirect3D9* dp = Direct3DCreate9(D3D_SDK_VERSION);

    if (dp == nullptr)
    {
        throw RendererException("Unable to initialize D3D9 object.");

        return false;
    }

    HWND hWnd = reinterpret_cast<HWND>(m_window->GetHandle());

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
    pp.BackBufferWidth = static_cast<UINT>(m_window->GetWidth());
    pp.BackBufferHeight = static_cast<UINT>(m_window->GetHeight());

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

    m_ui = UICore::Create(m_window, this);

    if (m_ui == nullptr)
    {
        throw RendererException("Unable to create UI.");

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

bool DX9Renderer::ProcessPixelFontSingleCharacter(DX9RendererFont* pFont, Gdiplus::Bitmap* bmp, size_t x, size_t y, size_t row, size_t col)
{
    const size_t ex = x + pFont->GetCharacterWidth();
    const size_t ey = y + pFont->GetCharacterHeight();

    for (size_t sy = y; sy < ey; ++sy)
    {
        for (size_t sx = x; sx < ex; ++sx)
        {
            Gdiplus::Color color;

            if (bmp->GetPixel(static_cast<INT>(sx), static_cast<INT>(sy), &color) != Gdiplus::Status::Ok)
            {
                return false;
            }

            // log color at stage, unless it's black
            if (color.GetValue() == 0xffffffff)
                continue;

            // 
        }
    }

    return true;
}

bool DX9Renderer::ProcessPixelFontSingleRow(DX9RendererFont* pFont, Gdiplus::Bitmap* bmp, size_t rowNumber)
{
    size_t sx = 0u;
    size_t sy = pFont->GetCharacterHeight() * rowNumber;

    size_t colNumber = 0;

    // Now, SX will begin at a character
    for (; sx < bmp->GetWidth(); sx += pFont->GetCharacterWidth())
    {
        if (!ProcessPixelFontSingleCharacter(pFont, bmp, sx, sy, rowNumber, colNumber))
        {
            return false;
        }

        ++colNumber;
    }

    return true;
}

RendererFont* DX9Renderer::CreatePixelFont(const wchar_t* path, size_t nativeCharWidth, size_t nativeCharHeight, size_t upscaleMultiplier)
{
    // The graphics file formats supported by GDI+ are BMP, GIF, JPEG, PNG, TIFF, Exif, WMF, and EMF.
    Gdiplus::Bitmap* bmp = Gdiplus::Bitmap::FromFile(path);

    if (bmp == nullptr)
    {
        throw RendererException("Unable to load bitmap file for pixel font.");

        return nullptr;
    }

    if (bmp->GetFrameDimensionsCount() > 1)
    {
        throw RendererException("The pixel font can not be loaded from an image containing more than one frame.");

        return nullptr;
    }

    const size_t bh = bmp->GetHeight();
    const size_t bw = bmp->GetWidth();

    if ((bw % nativeCharWidth) != 0)
    {
        throw RendererException("Total font width is not divisible by the native char width.");

        return nullptr;
    }

    if ((bh % nativeCharHeight) != 0)
    {
        throw RendererException("Total font height is not divisible by the native char height.");

        return nullptr;
    }

    const size_t numRows = bw / nativeCharWidth;
    const size_t numCols = bh / nativeCharHeight;

    DX9RendererFont* pNewFont = new DX9RendererFont(numRows, numCols, nativeCharWidth, nativeCharHeight);

    for (size_t r = 0; r < numRows; ++r)
    {
        if (!ProcessPixelFontSingleRow(pNewFont, bmp, r))
        {
            throw RendererException("Unable to process image row for pixel font.");

            delete pNewFont;

            return nullptr;
        }
    }

    return pNewFont;
}
