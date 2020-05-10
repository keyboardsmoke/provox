#include "pch.h"
#include "types.h"
#include "UICore.h"
#include "Window/window.h"
#include "Renderer/Renderer.h"
#include "Renderer/DX9Renderer/DX9Renderer.h"

#include "UI/Renderers/DX9UICore.h"

// #include "examples/imgui_impl_win32.h"
// #include "examples/imgui_impl_dx9.h"

UICore* UICore::Create(Window* win, Renderer* rend)
{
    UICore* core = nullptr;

    if (rend->GetType() == Renderer::Type::DX9)
    {
        DX9Renderer* dx = dynamic_cast<DX9Renderer*>(rend);

        core = new DX9UICore();
    }

    if (core != nullptr)
    {
        if (!core->Initialize(win, rend))
        {
            throw UICoreException("Unable to initialize core for type.");
        }
    }

    return core;
}

bool UICore::Initialize(Window* win, Renderer* rend)
{
    // Applies to any renderer
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

	if (rend->GetType() == Renderer::Type::DX9)
	{

	}

    throw UICoreException("Unsupported UI core renderer mode.");

    return false;
}

void UICore::AddWindow(UIWindow* win)
{
    m_windows.push_back(win);
}

void UICore::PrepareFrame()
{
    ImGui::NewFrame();
}

void UICore::PrepareUI()
{
    for (auto* win : m_windows)
    {
        win->Render();
    }
}

void UICore::FinishFrame()
{
    ImGui::EndFrame();
}

void UICore::PresentFrame()
{
    ImGui::Render();
}

void UICore::Destroy()
{
    ImGui::DestroyContext();
}