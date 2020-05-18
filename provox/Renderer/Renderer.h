#pragma once

class Window;
class UICore;

class RendererException : public std::exception
{
public:
    RendererException() = delete;
    RendererException(const char* msg) : std::exception(msg) {}
};

class RendererFont
{
public:
    RendererFont() = delete;
    RendererFont(size_t rows, size_t cols, size_t charWidth, size_t charHeight) :
        m_numRows(rows), m_numCols(cols), m_charWidth(charWidth), m_charHeight(charHeight) {}

    size_t GetNumRows() { return m_numRows; }
    size_t GetNumColumns() { return m_numCols; }
    size_t GetCharacterWidth() { return m_charWidth; }
    size_t GetCharacterHeight() { return m_charHeight; }

protected:
    size_t m_numRows;
    size_t m_numCols;
    size_t m_charWidth;
    size_t m_charHeight;
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

    static Renderer* Create(Window* window, Type type);

    // Render steps
    virtual bool Initialize() = 0;
    virtual Type GetType() = 0;
    virtual void BeginScene() = 0;
    virtual void Present() = 0;
    virtual void EndScene() = 0;
    virtual void Release() = 0;

    // 
    virtual RendererFont* CreatePixelFont(const wchar_t* path, size_t nativeCharWidth, size_t nativeCharHeight, size_t upscaleMultiplier) = 0;

    // Getters
    UICore* GetUI() { return m_ui; }

    // Stuff for adding textures/models/voxels/etc here
protected:
    Window* m_window;
    UICore* m_ui;
};
