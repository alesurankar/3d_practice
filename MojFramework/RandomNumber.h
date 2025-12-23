#pragma once
#include <random>

class RandomNumber
{
public:
	RandomNumber()
		:
		rng(rd())
	{}
	float RndFloat(float low_end, float high_end)
	{
		std::uniform_real_distribution<float> dist(low_end, high_end);
		return dist(rng);
	}
	int RndInt(int low_end, int high_end)
	{
		std::uniform_int_distribution<int> dist(low_end, high_end);
		return dist(rng);
	}
	Vec2 RndVec2(float low_end, float high_end)
	{
		return Vec2(
			RndFloat(low_end, high_end), 
			RndFloat(low_end, high_end));
	}
	Vei2 RndVei2(int low_end, int high_end)
	{
		return Vei2(
			RndInt(low_end, high_end),
			RndInt(low_end, high_end));
	}
	Vec3 RndVec3(float low_end, float high_end)
	{
		return Vec3(
			RndFloat(low_end, high_end), 
			RndFloat(low_end, high_end), 
			RndFloat(low_end, high_end));
	}
	Vei3 RndVei3(int low_end, int high_end)
	{
		return Vei3(
			RndInt(low_end, high_end),
			RndInt(low_end, high_end),
			RndInt(low_end, high_end));
	}
private:
	std::random_device rd;
	std::mt19937 rng;
};