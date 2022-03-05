#pragma once
#include<SFML/Graphics.hpp>


class Slider
{
private:
	std::pair<int, int> MinMaxValue;
	sf::Color SliderBarColor = sf::Color::White;
	sf::Color SliderButtonColor = sf::Color::Black;
	sf::Color TextColor = sf::Color::Black;
	sf::RectangleShape SliderBar;
	sf::RectangleShape SliderButton;
	float CurrValue;
	sf::Font font;
	sf::Text text;
	std::string textStr;

public:
	Slider(const sf::Vector2f& Size, const sf::Vector2f& Pos,const sf::Color& SliderBarColor, const std::string& Text, 
		const std::pair<int, int>& MinMaxValue, const float& CurrentValue, const sf::Font& font);

	const int& getValue() const { return CurrValue; };

	void setSize(const sf::Vector2f& Size);
	void setPos(const sf::Vector2f& Pos);
	void setSliderBarColor(const sf::Color& color) { SliderBar.setFillColor(color); };
	void setButtonColor(const sf::Color& color) { SliderButton.setFillColor(color); };
	void setTextColor(const sf::Color& color) { TextColor = color; };

	void update(const sf::Vector2i& MousePos);
	void render(sf::RenderTarget& window);


};

