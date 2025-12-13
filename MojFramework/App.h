#pragma once
#include "Graphics.h"
#include "CubeScreenTransformer.h"
#include "NDCScreenTransformer.h"
#include "Cube.h"
#include "FrameTimer.h"
#include "Mat.h"
#include "MyScene.h"
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
	std::unique_ptr<MyScene> scene;
};