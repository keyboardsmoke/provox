#pragma once

#include "UI/UICore.h"

class DX9UICore : public UICore
{
private:
	bool Initialize(Window* win, Renderer* rend) override;

public:
	// Before BeginScene
	void PrepareFrame() override;

	// After PrepareFrame
	void PrepareUI() override;

	// After PrepareUI
	void FinishFrame() override;

	// Before EndScene, Present
	void PresentFrame() override;
	void Destroy() override;
};