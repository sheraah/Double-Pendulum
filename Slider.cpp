#include "Slider.h"

Slider::Slider(const sf::Vector2f& Size, const sf::Vector2f& Pos, const sf::Color& SliderBarColor, const std::string& Text,
	const std::pair<int, int>& MinMaxValue, const float& CurrentValue, const sf::Font& font)
	:MinMaxValue(MinMaxValue), CurrValue(CurrentValue), font(font), textStr(Text), SliderBarColor(SliderBarColor)
{
	setSize(Size);

	SliderBar.setFillColor(SliderBarColor);
	SliderButton.setFillColor(SliderButtonColor);;
	text.setFont(this->font);
	text.setString(textStr);
	text.setFillColor(TextColor);
	setPos(Pos);

	float OneValueWidth = (SliderBar.getSize().x - SliderButton.getSize().x) / (MinMaxValue.second - MinMaxValue.first + 1);
	SliderButton.setPosition(SliderBar.getPosition().x + SliderButton.getSize().x / 2 + OneValueWidth * (CurrValue - MinMaxValue.first),
		SliderButton.getPosition().y);
}

void Slider::setSize(const sf::Vector2f& Size)
{
	SliderBar.setSize(Size);
	SliderButton.setSize({ Size.y, Size.y });
	text.setCharacterSize(SliderButton.getSize().x * 2);
}

void Slider::setPos(const sf::Vector2f& Pos)
{
	float Differ = SliderButton.getPosition().x - SliderBar.getPosition().x;

	SliderBar.setPosition(Pos);
	SliderButton.setPosition(Pos.x + Differ, Pos.y);
}

void Slider::update(const sf::Vector2i& MousePos)
{

	if (MousePos.x <= SliderBar.getPosition().x + SliderButton.getSize().x / 2) return;
	if (MousePos.x > SliderBar.getPosition().x + SliderBar.getSize().x - SliderButton.getSize().x / 2) return;
	if (MousePos.y < SliderBar.getPosition().y - SliderBar.getSize().y) return;
	if (MousePos.y > SliderBar.getPosition().y + SliderBar.getSize().y * 2) return;

	SliderButton.setPosition(MousePos.x - SliderButton.getSize().x / 2, SliderButton.getPosition().y);

	float OneValueWidth = (SliderBar.getSize().x - SliderButton.getSize().x) / (MinMaxValue.second - MinMaxValue.first + 1);
	float CurrValuePos = MousePos.x - SliderBar.getPosition().x - SliderButton.getSize().x / 2;

	int count = 0;
	for (float i = 0; i <= SliderBar.getSize().x - SliderButton.getSize().x; i += OneValueWidth)
	{
		count++;

		if (CurrValuePos <= i)
			break;
	}

	int Differ = 1 - MinMaxValue.first;

	CurrValue = count - Differ - 1;
}

void Slider::render(sf::RenderTarget& window)
{
	window.draw(SliderBar);
	window.draw(SliderButton);

	text.setString(textStr);
	text.setPosition(SliderBar.getPosition().x - text.getGlobalBounds().width - text.getCharacterSize(), SliderBar.getPosition().y -
		text.getGlobalBounds().height / 3);
	window.draw(text);

	text.setString(std::to_string(int(CurrValue)));
	text.setPosition(SliderBar.getPosition().x + SliderBar.getSize().x + text.getGlobalBounds().width + text.getCharacterSize(),
		SliderBar.getPosition().y - text.getGlobalBounds().height / 3);

	window.draw(text);
}
