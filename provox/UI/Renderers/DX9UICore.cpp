#include "pch.h"
#include "UI/UICore.h"
#include "UI/Renderers/DX9UICore.h"
#include "Window/Window.h"
#include "Renderer/Renderer.h"
#include "Renderer/DX9Renderer/DX9Renderer.h"
#include <d3d9.h>

struct CUSTOMVERTEX
{
    float    pos[3];
    D3DCOLOR col;
    float    uv[2];
};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

bool DX9UICore::Initialize(Window* win, Renderer* rend)
{
    m_window = win;

    if (!UICore::Initialize(win, rend))
    {
        throw UICoreException("Unable to initialize UI core.");

        return false;
    }

    DX9Renderer* dx = dynamic_cast<DX9Renderer*>(rend);

    if (dx == nullptr)
    {
        throw UICoreException("Renderer type is DX9, but unable to retrieve interface.");

        return false;
    }

    m_pDx = dx;

    // Win32 initialization used to be here, but I feel this is more useful in the Window class...
    if (!win->InitializeUI())
    {
        throw UICoreException("Unable to initialize Window class UI.");

        return false;
    }

    // ImGui initialization
    ImGuiIO& io = ImGui::GetIO();
    io.BackendRendererName = "DX9UICore";

    // We can honor the ImDrawCmd::VtxOffset field, allowing for large meshes.
    io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;

    // Add reference to device
    dx->GetDevice()->AddRef();

    return true;
}

void DX9UICore::PrepareFrame()
{
    // Before BeginScene
    if (!m_pFontTexture)
    {
        if (!CreateFontTexture())
        {
            throw UICoreException("Unable to initialize font texture.");

            return;
        }
    }

    m_window->StartUIFrame();

    UICore::PrepareFrame();
}

void DX9UICore::PrepareUI()
{
    UICore::PrepareUI();
}

void DX9UICore::FinishFrame()
{
    UICore::FinishFrame();
}

void DX9UICore::PresentFrame()
{
    UICore::PresentFrame();

    ImDrawData* draw_data = ImGui::GetDrawData();

    // Avoid rendering when minimized
    if (draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f)
        return;

    // Create and grow buffers if needed
    if (!m_pVB || m_vertexBufferSize < draw_data->TotalVtxCount)
    {
        if (m_pVB) { m_pVB->Release(); m_pVB = nullptr; }
        m_vertexBufferSize = draw_data->TotalVtxCount + 5000;
        if (m_pDx->GetDevice()->CreateVertexBuffer(m_vertexBufferSize * sizeof(CUSTOMVERTEX), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &m_pVB, nullptr) < 0)
            return;
    }
    if (!m_pIB || m_indexBufferSize < draw_data->TotalIdxCount)
    {
        if (m_pIB) { m_pIB->Release(); m_pIB = nullptr; }
        m_indexBufferSize = draw_data->TotalIdxCount + 10000;
        if (m_pDx->GetDevice()->CreateIndexBuffer(m_indexBufferSize * sizeof(ImDrawIdx), D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, sizeof(ImDrawIdx) == 2 ? D3DFMT_INDEX16 : D3DFMT_INDEX32, D3DPOOL_DEFAULT, &m_pIB, NULL) < 0)
            return;
    }

    // Backup the DX9 state
    IDirect3DStateBlock9* d3d9_state_block = NULL;
    if (m_pDx->GetDevice()->CreateStateBlock(D3DSBT_ALL, &d3d9_state_block) < 0)
        return;

    // Backup the DX9 transform (DX9 documentation suggests that it is included in the StateBlock but it doesn't appear to)
    D3DMATRIX last_world, last_view, last_projection;
    m_pDx->GetDevice()->GetTransform(D3DTS_WORLD, &last_world);
    m_pDx->GetDevice()->GetTransform(D3DTS_VIEW, &last_view);
    m_pDx->GetDevice()->GetTransform(D3DTS_PROJECTION, &last_projection);

    // Copy and convert all vertices into a single contiguous buffer, convert colors to DX9 default format.
    // FIXME-OPT: This is a waste of resource, the ideal is to use imconfig.h and
    //  1) to avoid repacking colors:   #define IMGUI_USE_BGRA_PACKED_COLOR
    //  2) to avoid repacking vertices: #define IMGUI_OVERRIDE_DRAWVERT_STRUCT_LAYOUT struct ImDrawVert { ImVec2 pos; float z; ImU32 col; ImVec2 uv; }
    CUSTOMVERTEX* vtx_dst;
    ImDrawIdx* idx_dst;
    if (m_pVB->Lock(0, (UINT)(draw_data->TotalVtxCount * sizeof(CUSTOMVERTEX)), (void**)&vtx_dst, D3DLOCK_DISCARD) < 0)
        return;
    if (m_pIB->Lock(0, (UINT)(draw_data->TotalIdxCount * sizeof(ImDrawIdx)), (void**)&idx_dst, D3DLOCK_DISCARD) < 0)
        return;
    for (int n = 0; n < draw_data->CmdListsCount; n++)
    {
        const ImDrawList* cmd_list = draw_data->CmdLists[n];
        const ImDrawVert* vtx_src = cmd_list->VtxBuffer.Data;
        for (int i = 0; i < cmd_list->VtxBuffer.Size; i++)
        {
            vtx_dst->pos[0] = vtx_src->pos.x;
            vtx_dst->pos[1] = vtx_src->pos.y;
            vtx_dst->pos[2] = 0.0f;
            vtx_dst->col = (vtx_src->col & 0xFF00FF00) | ((vtx_src->col & 0xFF0000) >> 16) | ((vtx_src->col & 0xFF) << 16);     // RGBA --> ARGB for DirectX9
            vtx_dst->uv[0] = vtx_src->uv.x;
            vtx_dst->uv[1] = vtx_src->uv.y;
            vtx_dst++;
            vtx_src++;
        }
        memcpy(idx_dst, cmd_list->IdxBuffer.Data, cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx));
        idx_dst += cmd_list->IdxBuffer.Size;
    }
    m_pVB->Unlock();
    m_pIB->Unlock();
    m_pDx->GetDevice()->SetStreamSource(0, m_pVB, 0, sizeof(CUSTOMVERTEX));
    m_pDx->GetDevice()->SetIndices(m_pIB);
    m_pDx->GetDevice()->SetFVF(D3DFVF_CUSTOMVERTEX);

    // Setup desired DX state
    SetupRenderState(draw_data);

    // Render command lists
    // (Because we merged all buffers into a single one, we maintain our own offset into them)
    int global_vtx_offset = 0;
    int global_idx_offset = 0;
    ImVec2 clip_off = draw_data->DisplayPos;
    for (int n = 0; n < draw_data->CmdListsCount; n++)
    {
        const ImDrawList* cmd_list = draw_data->CmdLists[n];
        for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
        {
            const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
            if (pcmd->UserCallback != NULL)
            {
                // User callback, registered via ImDrawList::AddCallback()
                // (ImDrawCallback_ResetRenderState is a special callback value used by the user to request the renderer to reset render state.)
                if (pcmd->UserCallback == ImDrawCallback_ResetRenderState)
                    SetupRenderState(draw_data);
                else
                    pcmd->UserCallback(cmd_list, pcmd);
            }
            else
            {
                const RECT r = { (LONG)(pcmd->ClipRect.x - clip_off.x), (LONG)(pcmd->ClipRect.y - clip_off.y), (LONG)(pcmd->ClipRect.z - clip_off.x), (LONG)(pcmd->ClipRect.w - clip_off.y) };
                const LPDIRECT3DTEXTURE9 texture = (LPDIRECT3DTEXTURE9)pcmd->TextureId;
                m_pDx->GetDevice()->SetTexture(0, texture);
                m_pDx->GetDevice()->SetScissorRect(&r);
                m_pDx->GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, pcmd->VtxOffset + global_vtx_offset, 0, (UINT)cmd_list->VtxBuffer.Size, pcmd->IdxOffset + global_idx_offset, pcmd->ElemCount / 3);
            }
        }
        global_idx_offset += cmd_list->IdxBuffer.Size;
        global_vtx_offset += cmd_list->VtxBuffer.Size;
    }

    // Restore the DX9 transform
    m_pDx->GetDevice()->SetTransform(D3DTS_WORLD, &last_world);
    m_pDx->GetDevice()->SetTransform(D3DTS_VIEW, &last_view);
    m_pDx->GetDevice()->SetTransform(D3DTS_PROJECTION, &last_projection);

    // Restore the DX9 state
    d3d9_state_block->Apply();
    d3d9_state_block->Release();
}

void DX9UICore::Destroy()
{
    if (m_pDx->GetDevice() != nullptr)
    {
        if (m_pVB) { m_pVB->Release(); m_pVB = nullptr; }
        if (m_pIB) { m_pIB->Release(); m_pIB = nullptr; }
        
        if (m_pFontTexture) 
        { 
            m_pFontTexture->Release(); 
            m_pFontTexture = nullptr; 
            ImGui::GetIO().Fonts->TexID = nullptr; 
        }
    }

    if (!m_window->ShutdownUI())
    {
        throw UICoreException("Unable to shutdown Window class UI.");
    }

    UICore::Destroy();
}

bool DX9UICore::CreateFontTexture()
{
    // Build texture atlas
    ImGuiIO& io = ImGui::GetIO();
    unsigned char* pixels;
    int width, height, bytes_per_pixel;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height, &bytes_per_pixel);

    // Upload texture to graphics system
    m_pFontTexture = nullptr;

    if (m_pDx->GetDevice()->CreateTexture(width, height, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pFontTexture, NULL) < 0)
    {
        return false;
    }

    D3DLOCKED_RECT tex_locked_rect;
    if (m_pFontTexture->LockRect(0, &tex_locked_rect, NULL, 0) != D3D_OK)
    {
        return false;
    }

    for (int y = 0; y < height; y++)
    {
        memcpy((unsigned char*)tex_locked_rect.pBits + tex_locked_rect.Pitch * y, pixels + (width * bytes_per_pixel) * y, (width * bytes_per_pixel));
    }

    m_pFontTexture->UnlockRect(0);

    // Store our identifier
    io.Fonts->TexID = (ImTextureID)m_pFontTexture;

    return true;
}

void DX9UICore::SetupRenderState(ImDrawData* draw_data)
{
    // Setup viewport
    D3DVIEWPORT9 vp;
    vp.X = vp.Y = 0;
    vp.Width = (DWORD)draw_data->DisplaySize.x;
    vp.Height = (DWORD)draw_data->DisplaySize.y;
    vp.MinZ = 0.0f;
    vp.MaxZ = 1.0f;
    m_pDx->GetDevice()->SetViewport(&vp);

    // Setup render state: fixed-pipeline, alpha-blending, no face culling, no depth testing, shade mode (for gradient)
    m_pDx->GetDevice()->SetPixelShader(NULL);
    m_pDx->GetDevice()->SetVertexShader(NULL);
    m_pDx->GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    m_pDx->GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
    m_pDx->GetDevice()->SetRenderState(D3DRS_ZENABLE, FALSE);
    m_pDx->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    m_pDx->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
    m_pDx->GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
    m_pDx->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    m_pDx->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    m_pDx->GetDevice()->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
    m_pDx->GetDevice()->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
    m_pDx->GetDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);
    m_pDx->GetDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
    m_pDx->GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    m_pDx->GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
    m_pDx->GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    m_pDx->GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    m_pDx->GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
    m_pDx->GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    m_pDx->GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

    // Setup orthographic projection matrix
    // Our visible imgui space lies from draw_data->DisplayPos (top left) to draw_data->DisplayPos+data_data->DisplaySize (bottom right). DisplayPos is (0,0) for single viewport apps.
    // Being agnostic of whether <d3dx9.h> or <DirectXMath.h> can be used, we aren't relying on D3DXMatrixIdentity()/D3DXMatrixOrthoOffCenterLH() or DirectX::XMMatrixIdentity()/DirectX::XMMatrixOrthographicOffCenterLH()
    {
        float L = draw_data->DisplayPos.x + 0.5f;
        float R = draw_data->DisplayPos.x + draw_data->DisplaySize.x + 0.5f;
        float T = draw_data->DisplayPos.y + 0.5f;
        float B = draw_data->DisplayPos.y + draw_data->DisplaySize.y + 0.5f;
        D3DMATRIX mat_identity = { { { 1.0f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 0.0f, 1.0f } } };
        D3DMATRIX mat_projection =
        { { {
            2.0f / (R - L),   0.0f,         0.0f,  0.0f,
            0.0f,         2.0f / (T - B),   0.0f,  0.0f,
            0.0f,         0.0f,         0.5f,  0.0f,
            (L + R) / (L - R),  (T + B) / (B - T),  0.5f,  1.0f
        } } };
        m_pDx->GetDevice()->SetTransform(D3DTS_WORLD, &mat_identity);
        m_pDx->GetDevice()->SetTransform(D3DTS_VIEW, &mat_identity);
        m_pDx->GetDevice()->SetTransform(D3DTS_PROJECTION, &mat_projection);
    }
}