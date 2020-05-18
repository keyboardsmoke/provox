#pragma once

#include "UI/UICore.h"

class DX9Renderer;
struct IDirect3DVertexBuffer9;
struct IDirect3DIndexBuffer9;
struct IDirect3DTexture9;

class DX9UICore : public UICore
{
public:
    DX9UICore() : UICore(), m_window(nullptr), m_pDx(nullptr), m_pVB(nullptr), m_pIB(nullptr), m_vertexBufferSize(5000), m_indexBufferSize(10000), m_pFontTexture(nullptr) {}

    // Before BeginScene
    void PrepareFrame() override;

    // After PrepareFrame
    void PrepareUI() override;

    // After PrepareUI
    void FinishFrame() override;

    // Before EndScene, Present
    void PresentFrame() override;
    void Destroy() override;

protected:
    bool Initialize(Window* win, Renderer* rend) override;

private:
    bool CreateFontTexture();
    void SetupRenderState(ImDrawData* draw_data);

    Window* m_window;
    DX9Renderer* m_pDx;

    IDirect3DVertexBuffer9* m_pVB;
    IDirect3DIndexBuffer9* m_pIB;
    int m_vertexBufferSize;
    int m_indexBufferSize;
    IDirect3DTexture9* m_pFontTexture;
};
