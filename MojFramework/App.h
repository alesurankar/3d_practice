#pragma once
#include "Graphics.h"

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
	int x = 20;
	int y = 20;
	int width = 12;
	int height = 12;
};