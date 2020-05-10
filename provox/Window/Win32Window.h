#pragma once

class Win32Window : public Window
{
public:
	Win32Window();

	bool Initialize(Float x, Float y, Float w, Float h) override;
	bool MessageLoop() override;

	Rect<Float> GetRect() override;

private:
	Rect<Float> m_rect;

	HWND GetHwnd() { return reinterpret_cast<HWND>(this->GetHandle()); }
};