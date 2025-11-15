#include "MainWindow.h"
#include "App.h"


App::App(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	cube(1.0f)
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
	const float dt = ft.Mark();
	float speed = 1.0f * dt;
	if (wnd.kbd.KeyIsPressed(VK_SPACE)) {
		speed = 3.0f * dt;
	}
	if (wnd.kbd.KeyIsPressed('W')) {
		y += speed;
	}
	if (wnd.kbd.KeyIsPressed('S')) {
		y -= speed;
	}
	if (wnd.kbd.KeyIsPressed('A')) {
		x -= speed;
	}
	if (wnd.kbd.KeyIsPressed('D')) {
		x += speed;
	}
	if (wnd.kbd.KeyIsPressed('Q')) {
		theta_z = wrap_angle(theta_z + dTheta * speed);
	}
	if (wnd.kbd.KeyIsPressed('E')) {
		theta_z = wrap_angle(theta_z - dTheta * speed);
	}

	const Mat3 rot =
		Mat3::RotationX(theta_x) *
		Mat3::RotationY(theta_y) *
		Mat3::RotationZ(theta_z);

	lines = cube.GetLines();
	for (auto& v : lines.vertices) {
		v *= rot;
		v += {x, y, 1.0f};
		cst.Transform(v);
	}
}

void App::ComposeFrame()
{
	for (auto i = lines.indices.cbegin(),
		end = lines.indices.cend();
		i != end; std::advance(i, 2))
	{
		gfx.DrawLine(lines.vertices[*i], lines.vertices[*std::next(i)], Colors::Blue);
	}
}