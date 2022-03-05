#include "Pendulum.h"

Pendulum::Pendulum(const sf::Vector2f& PendulumPos, const float& gravity, const float& r1, const float& r2,
	const float& m1, const float& m2, const bool& DrawTracingLines)
	:PendulumPos(PendulumPos), gravity(gravity), r1(r1), r2(r2), m1(m1), m2(m2), DrawTracingLines(DrawTracingLines)
{

}


void Pendulum::update()
{
	float Num1 = -gravity * (2 * m1 + m2) * sin(p1_ang);
	float Num2 = -m2 * gravity * sin(p1_ang - 2 * p2_ang);
	float Num3 = -2 * sin(p1_ang - p2_ang) * m2 * (pow(p2_vel, 2) * r2 + pow(p1_vel, 2) * r1 * cos(p1_ang - p2_ang));
	float Den = r1 * (2 * m1 + m2 - m2 * cos(2 * p1_ang - 2 * p2_ang));
	p1_ac = (Num1 + Num2 + Num3) / Den;

	Num1 = 2 * sin(p1_ang - p2_ang);
	Num2 = pow(p1_vel, 2) * r1 * (m1 + m2) + gravity * (m1 + m2) * cos(p1_ang);
	Num3 = pow(p2_vel, 2) * r2 * m2 * cos(p1_ang - p2_ang);
	Den = r2 * (2 * m1 + m2 - m2 * cos(2 * p1_ang - 2 * p2_ang));
	p2_ac = (Num1 * (Num2 + Num3)) / Den;

	p1_x = PendulumPos.x + r1 * sin(p1_ang);
	p1_y = PendulumPos.y + r1 * cos(p1_ang);

	p2_x = p1_x + r2 * sin(p2_ang);
	p2_y = p1_y + r2 * cos(p2_ang);

	p1_vel += p1_ac;
	p2_vel += p2_ac;
	p1_ang += p1_vel;
	p2_ang += p2_vel;

	PointsFortracing.push_back({ p2_x, p2_y });
}

void Pendulum::render(sf::RenderTarget& window)
{
	window.draw(sfLine(PendulumPos, { p1_x, p1_y }, sf::Color::Black, 3.f));
	window.draw(sfLine({ p1_x, p1_y }, { p2_x, p2_y }, sf::Color::Black, 3.f));

	sf::CircleShape  a;
	a.setFillColor(sf::Color::Black);
	a.setRadius(m1 / 2);
	a.setPosition(p1_x - a.getRadius(), p1_y - a.getRadius());
	window.draw(a);
	a.setRadius(m2 / 2);
	a.setPosition(p2_x - a.getRadius(), p2_y - a.getRadius());
	window.draw(a);



	if (DrawTracingLines && PointsFortracing.size() > 1)
	{
		for (size_t i = 0; i < PointsFortracing.size() - 1; i++)
		{
			window.draw(sfLine(PointsFortracing[i], PointsFortracing[i + 1], sf::Color::Black, 2.f));
		}
	}
}

