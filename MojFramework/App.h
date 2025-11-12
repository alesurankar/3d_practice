#pragma once
#include "Graphics.h"
#include <memory>
#include <vector>
#include "Scene.h"
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
	/********************************/
	/*  Moje Funkcije               */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  Moji Parametri              */
	FrameTimer ft;
	std::vector<std::unique_ptr<Scene>> scenes;
	std::vector<std::unique_ptr<Scene>>::iterator curScene;
	/********************************/
};