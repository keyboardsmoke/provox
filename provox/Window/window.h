#pragma once

class Window
{
public:
	static Window* Create(uint16 x, uint16 y, uint16 width, uint16 height);

	virtual bool Initialize(uint16 x, uint16 y, uint16 w, uint16 h) = 0;
	virtual bool MessageLoop() = 0;

	void* GetHandle() { return m_handle; }

protected:
	void* m_handle;
};