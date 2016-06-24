#include <iostream>
#include <string>

#include "SFMLMouseEvent.hpp"

SFMLMouseEvent::SFMLMouseEvent():
mouseClicked(false)
{
}

SFMLMouseEvent::~SFMLMouseEvent() { }

void SFMLMouseEvent::update(sf::RenderWindow & window, sf::Event event)
{
	mouseEvent = event;
	mouseClicked = false;
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
			_x = pixelPos.x;
			_y = pixelPos.y;
			mouseClicked = true;
		}
	}
}

bool SFMLMouseEvent::isMouseClicked() const { return mouseClicked; }
int SFMLMouseEvent::getX() const { return _x; }
int SFMLMouseEvent::getY() const { return _y; }

void SFMLMouseEvent::reset() { mouseClicked = false; }