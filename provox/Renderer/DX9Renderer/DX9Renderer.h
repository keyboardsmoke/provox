#pragma once

class Window;

// Forward declarations
class DX9Renderer;

namespace Gdiplus
{
	class Bitmap;
}

// Class definitions

class DX9Character
{
public:
	DX9Character() = delete;
	DX9Character(size_t width, size_t height)
	{
		// m_data = new unsigned int[width][height];
	}

private:
	
};

class DX9RendererFont : public RendererFont
{
public:
	DX9RendererFont() = delete;
	DX9RendererFont(size_t rows, size_t cols, size_t charWidth, size_t charHeight) :
		RendererFont(rows, cols, charWidth, charHeight) {}

protected:
	std::vector<DX9Character> m_characters;
};

struct IDirect3D9;
struct IDirect3DDevice9;

class DX9Renderer : public Renderer
{
public:
	DX9Renderer();

	bool Initialize() override;
	Type GetType() override { return Type::DX9; }
	void BeginScene() override;
	void Present() override;
	void EndScene() override;
	void Release() override;

	RendererFont* CreatePixelFont(const wchar_t* path, size_t nativeCharWidth, size_t nativeCharHeight, size_t upscaleMultiplier) override;

	IDirect3D9* GetD3D() { return m_dp; }
	IDirect3DDevice9* GetDevice() { return m_dev; }

private:
	bool ProcessPixelFontSingleCharacter(DX9RendererFont* pFont, Gdiplus::Bitmap* bmp, size_t x, size_t y, size_t row, size_t col);
	bool ProcessPixelFontSingleRow(DX9RendererFont* pFont, Gdiplus::Bitmap* bmp, size_t rowNumber);

	IDirect3D9* m_dp;
	IDirect3DDevice9* m_dev;
};