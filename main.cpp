#include "Pendulum.h"
#include "Slider.h"

constexpr float WIDTH = 1500;
constexpr float HEIGHT = 1080;
constexpr bool drawTraceLines = 1;

const std::string FontPath = "Fonts/Font1.ttf";
sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Double Pendulum", sf::Style::Close);
sf::Event evnt;
sf::Font font;

int main()
{
	sf::Vector2f windowSize = sf::Vector2f(float(window.getSize().x), float(window.getSize().y));

	font.loadFromFile(FontPath);

	Pendulum pend({ windowSize.x / 2, 200 }, 1, 200, 200, 50, 50, drawTraceLines);
	Slider r1_slider({ 100, 15 }, { windowSize.x - 200, 100 }, sf::Color::Green, "r1", { 1, 15 }, 4, font);

	Slider r2_slider({ 100, 15 }, { windowSize.x - 200, 150 }, sf::Color::Green, "r2", { 1, 15 }, 4, font);

	Slider m1_slider({ 100, 15 }, { windowSize.x - 200, 200 }, sf::Color::Yellow, "m1", { 1, 10 }, 4, font);

	Slider m2_slider({ 100, 15 }, { windowSize.x - 200, 250 }, sf::Color::Yellow, "m2", { 1, 10 }, 4, font);

	Slider grav_slider({ 100, 15 }, { windowSize.x - 200, 300 }, sf::Color::Cyan, "gravity", { 0, 20 }, 1, font);

	pend.r1 = r1_slider.getValue() * 30;
	pend.r2 = r2_slider.getValue() * 30;
	pend.m1 = m1_slider.getValue() * 10;
	pend.m2 = m2_slider.getValue() * 10;

	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			r1_slider.update(sf::Mouse::getPosition(window));
			pend.r1 = r1_slider.getValue() * 30;
			r2_slider.update(sf::Mouse::getPosition(window));
			pend.r2 = r2_slider.getValue() * 30;
			m1_slider.update(sf::Mouse::getPosition(window));
			pend.m1 = m1_slider.getValue() * 10;
			m2_slider.update(sf::Mouse::getPosition(window));
			pend.m2 = m2_slider.getValue() * 10;
			grav_slider.update(sf::Mouse::getPosition(window));
			pend.gravity = grav_slider.getValue();
		}

		pend.update();

		window.clear(sf::Color::White);

		pend.render(window);
		r1_slider.render(window);
		r2_slider.render(window);
		m1_slider.render(window);
		m2_slider.render(window);
		grav_slider.render(window);

		window.display();


	}

}