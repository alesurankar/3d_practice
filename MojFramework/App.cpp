#include "MainWindow.h"
#include "App.h"


App::App(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
{
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
	if (wnd.kbd.KeyIsPressed('W')) {
		y--;
	}
	if (wnd.kbd.KeyIsPressed('S')) {
		y++;
	}
	if (wnd.kbd.KeyIsPressed('A')) {
		x--;
	}
	if (wnd.kbd.KeyIsPressed('D')) {
		x++;
	}
}

void App::ComposeFrame()
{
	for (int i = x; i < x + width; i++)
	{
		for (int j = y; j < y + height; j++)
		{
			gfx.PutPixel(i, j, Colors::White);
		}
	}
}