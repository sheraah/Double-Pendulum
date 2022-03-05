#pragma once
#include "sfLine.h"
#define PI 3.14159265359


class Pendulum
{

private:

	float p1_vel = 0;
	float p2_vel = 0;
	float p1_ac = 0;
	float p2_ac = 0;
	float p1_x = 0;
	float p1_y = 0;
	float p2_x = 0;
	float p2_y = 0;
	float p1_ang = PI / 4;
	float p2_ang = PI / 8;

	std::vector<sf::Vector2f> PointsFortracing;

public:
	Pendulum(const sf::Vector2f& PendulumPos, const float& gravitiy, const float& r1, const float& r2, const float& m1, const float& m2,
		const bool& DrawTracingLines = 1);

	sf::Vector2f PendulumPos;

	bool DrawTracingLines;

	float gravity;

	float r1;
	float r2;

	float m1;
	float m2;

	void update();
	void render(sf::RenderTarget& window);

};

