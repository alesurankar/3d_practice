#pragma once
#include "Graphics.h"
#include "CubeScreenTransformer.h"
#include "NDCScreenTransformer.h"
#include "Cube.h"
#include "FrameTimer.h"

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
	float a = 0.0f;
	float b = 0.0f;
	int width = 12;
	int height = 12;
	CubeScreenTransformer cst;
	Cube cube;
	Rct rct;
	IndexedLineList2 lines2;
	IndexedLineList lines;
};