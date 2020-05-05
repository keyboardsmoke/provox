#pragma once

class Window;

class DX9Renderer : public Renderer
{
public:
	DX9Renderer();

	bool Initialize(Window* window) override;

private:

};