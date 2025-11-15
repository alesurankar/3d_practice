#include "MainWindow.h"
#include "App.h"


App::App(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	cube(1.0f),
	rct(1.0f)
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
	const float dt = ft.Mark();
	float speed = 1.0f;
	if (wnd.kbd.KeyIsPressed(VK_SPACE)) {
		speed = 3.0f;
	}
	if (wnd.kbd.KeyIsPressed('W')) {
		y -= speed * dt;
	}
	if (wnd.kbd.KeyIsPressed('S')) {
		y += speed * dt;
	}
	if (wnd.kbd.KeyIsPressed('A')) {
		x -= speed * dt;
	}
	if (wnd.kbd.KeyIsPressed('D')) {
		x += speed * dt;
	}

	//Rectangle
	lines2 = rct.GetLines();
	for (auto& v : lines2.vert2)
	{
		v += {x, y};
		cst.Transform2(v);
	}

	//Cube
	lines = cube.GetLines();
	for (auto& v : lines.vertices)
	{
		v += {0.0f, 0.0f, 1.0f};
		cst.Transform(v);
	}
}

void App::ComposeFrame()
{
	// Rectangle
	for (auto i = lines2.ind2.cbegin(),
		end = lines2.ind2.cend();
		i != end; std::advance(i, 2))
	{
		gfx.DrawLine(lines2.vert2[*i], lines2.vert2[*std::next(i)], Colors::White);
	}

	//Cube
	for (auto i = lines.indices.cbegin(),
		end = lines.indices.cend();
		i != end; std::advance(i, 2))
	{
		gfx.DrawLine(lines.vertices[*i], lines.vertices[*std::next(i)], Colors::Blue);
	}
}