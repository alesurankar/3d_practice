#include "MainWindow.h"
#include "App.h"
#include "SpecularPhongPointScene.h"


App::App(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
{
	scenes.push_back(std::make_unique<SpecularPhongPointScene>(gfx,
		IndexedTriangleList<SpecularPhongPointScene::Vertex>::LoadNormals("models\\suzanne.obj")));
	curScene = scenes.begin();
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
	(*curScene)->Update(wnd.kbd, wnd.mouse, dt);
}

void App::ComposeFrame()
{
	(*curScene)->Draw();
}