#include "MainWindow.h"
#include "App.h"


App::App(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	cube(1.0f),
	rct(1.0)
{}

void App::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void App::UpdateModel()
{
	int speed = 1;
	if (wnd.kbd.KeyIsPressed(VK_SPACE)) {
		speed = 3;
	}
	if (wnd.kbd.KeyIsPressed('W')) {
		y-=speed;
	}
	if (wnd.kbd.KeyIsPressed('S')) {
		y+=speed;
	}
	if (wnd.kbd.KeyIsPressed('A')) {
		x-=speed;
	}
	if (wnd.kbd.KeyIsPressed('D')) {
		x+=speed;
	}
}

void App::ComposeFrame()
{
	//gfx.DrawLine(Vec2{ x - width, y - width }, Vec2{ x + width, y - width }, Colors::Red);
	//gfx.DrawLine(Vec2{ x + width, y - width }, Vec2{ x + width, y + width }, Colors::Green);
	//gfx.DrawLine(Vec2{ x + width, y + width }, Vec2{ x - width, y + width }, Colors::Yellow);
	//gfx.DrawLine(Vec2{ x - width, y + width }, Vec2{ x - width, y - width }, Colors::Blue);
	
	/*auto lines = cube.GetLines();
	for (auto& v : lines.vertices)
	{
		cst.Transform(v);
	}
	for (auto i = lines.indices.cbegin(),
		end = lines.indices.cend();
		i != end; std::advance(i, 2))
	{
		gfx.DrawLine(lines.vertices[*i], lines.vertices[*std::next(i)], Colors::White);
	}*/

	auto lines2 = rct.GetLines();
	for (auto& v : lines2.vert2)
	{
		v += {0.2f, 0.2f};
		cst.Transform2(v);
	}
	for (auto i = lines2.ind2.cbegin(),
		end = lines2.ind2.cend();
		i != end; std::advance(i, 2))
	{
		gfx.DrawLine(lines2.vert2[*i], lines2.vert2[*std::next(i)], Colors::White);
	}


	auto lines = cube.GetLines();
	for (auto& v : lines.vertices)
	{
		v += {0.0f, 0.0f, 1.0f};
		cst.Transform(v);
	}
	for (auto i = lines.indices.cbegin(),
		end = lines.indices.cend();
		i != end; std::advance(i, 2))
	{
		gfx.DrawLine(lines.vertices[*i], lines.vertices[*std::next(i)], Colors::Blue);
	}
}