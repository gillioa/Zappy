#include <iostream>

#include "CollisionEngine.hpp"


/* pt vs pt */
bool CollisionEngine::pointVSPoint(sf::Vector2f & obj1, sf::Vector2f & obj2)
{
	if (obj1.x == obj2.x
		&&
		obj1.y == obj2.y)
		return true;
	return false;
}

/* pt vs rectangle shape */

bool CollisionEngine::pointVSshape( sf::RenderWindow &window, sf::RectangleShape shape, int x, int y)
{
	sf::FloatRect boundingBox = shape.getGlobalBounds();
	sf::Vector2f point;

	point = window.mapPixelToCoords(sf::Vector2i(x,y));
	if (boundingBox.contains(point))
		return true;
	return false;
}

/* pt vs sprite */

bool CollisionEngine::pointVSsprite( sf::RenderWindow &window, sf::Sprite sprite, int x, int y)
{
	sf::FloatRect boundingBox = sprite.getGlobalBounds();
	sf::Vector2f point;

	point = window.mapPixelToCoords(sf::Vector2i(x,y));
	if (boundingBox.contains(point))
		return true;
	return false;
}