#pragma once

class Win32Window : public Window
{
public:
    Win32Window();

    bool Initialize(Float x, Float y, Float w, Float h) override;
    bool InitializeUI() override;
    void StartUIFrame() override;
    bool ShutdownUI() override;
    bool MessageLoop() override;

    AABB2D<Float> GetRect() override;

    void UpdateUIMousePos();
    bool UpdateUICursor();

    AABB2D<Float> m_rect;

    // UI variables
    int64 m_time;
    int64 m_ticksPerSecond;
    ImGuiMouseCursor m_lastMouseCursor;

    HWND GetHwnd() { return reinterpret_cast<HWND>(this->GetHandle()); }
};
