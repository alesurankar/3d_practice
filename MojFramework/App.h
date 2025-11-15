#pragma once
#include "Graphics.h"
#include "CubeScreenTransformer.h"
#include "NDCScreenTransformer.h"
#include "Cube.h"
#include "FrameTimer.h"
#include "Mat.h"

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
	float x = 0.0f;
	float y = 0.0f;
	float z = 2.0f;
	int width = 12;
	int height = 12;
	CubeScreenTransformer cst;
	Cube cube;
	IndexedLineList lines;
	static constexpr float dTheta = PI;
	float theta_x = 0.0f;
	float theta_y = 0.0f;
	float theta_z = 0.0f;
};