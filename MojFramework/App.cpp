#include "MainWindow.h"
#include "App.h"


App::App(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
{
	scene = std::make_unique<MyScene>();
}

void App::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void App::UpdateModel()
{
	const float dt = ft.Mark();

	// update scene
	scene->Update(wnd.kbd, wnd.mouse, dt);
}

void App::ComposeFrame()
{
	// draw scene
	scene->Draw(gfx);
}