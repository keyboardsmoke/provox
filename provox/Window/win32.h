#pragma once

class Win32Window : public Window
{
public:
	Win32Window();

	bool Initialize(uint16 x, uint16 y, uint16 w, uint16 h) override;
	bool MessageLoop() override;
};