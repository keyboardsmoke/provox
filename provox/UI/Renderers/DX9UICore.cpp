#include "pch.h"
#include "UI/UICore.h"
#include "UI/Renderers/DX9UICore.h"
#include "Renderer/Renderer.h"
#include "Renderer/DX9Renderer/DX9Renderer.h"

bool DX9UICore::Initialize(Window* win, Renderer* rend)
{
    DX9Renderer* dx = dynamic_cast<DX9Renderer*>(rend);

    if (dx == nullptr)
    {
        throw UICoreException("Renderer type is DX9, but unable to retrieve interface.");

        return false;
    }

    // Win32 initialization used to be here, but I feel this is more useful in the Window class...

    // ImGui initialization
    ImGuiIO& io = ImGui::GetIO();
    io.BackendRendererName = "DX9UICore";

    // We can honor the ImDrawCmd::VtxOffset field, allowing for large meshes.
    io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;

    // Add reference to the device
    dx->GetDevice()->AddRef();

    // ImGui_ImplWin32_Init(win->GetHandle());
    // ImGui_ImplDX9_Init(dx->GetDevice());

    return true;
}

void DX9UICore::PrepareFrame()
{
    // Before BeginScene
    // ImGui_ImplDX9_NewFrame();
    // ImGui_ImplWin32_NewFrame();

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

    // ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

void DX9UICore::Destroy()
{
    // ImGui_ImplDX9_Shutdown();
    // ImGui_ImplWin32_Shutdown();

    UICore::Destroy();
}