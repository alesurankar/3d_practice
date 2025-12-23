#include "MainWindow.h"
#include "App.h"


App::App(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
{
	scene = std::make_unique<Scene>(gfx);
}

void App::Go()
{
	gfx.BeginFrame(Colors::MakeRGB(30, 30, 30));
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void App::UpdateModel()
{
	const float dt = ft.Mark();

	scene->Update(wnd.kbd, wnd.mouse, dt);
}

void App::ComposeFrame()
{
	scene->BindAndDraw();
}