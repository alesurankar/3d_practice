#pragma once
#include "Graphics.h"
#include "FrameTimer.h"
#include "Scene.h"
#include "Scene2.h"
#include "Scene3.h"
#include <memory>

class App
{
public:
	App(class MainWindow& wnd);
	App(const App&) = delete;
	App& operator=(const App&) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
private:
	MainWindow& wnd;
	Graphics gfx;
	FrameTimer ft;
	float time = 0.0f;
	std::unique_ptr<Scene3> scene;
};