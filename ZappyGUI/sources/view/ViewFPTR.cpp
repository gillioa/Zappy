#include "View.hpp"

void View::drawNourriture(sf::CircleShape & shape, sf::Vector2f newPos)
{
	shape.setFillColor(Color::Nourriture);
	shape.setPosition(newPos);
	m_window.draw(shape);
}

void View::drawLinemate(sf::CircleShape & shape, sf::Vector2f newPos)
{
	shape.setFillColor(Color::Linemate);

	newPos.x += Settings::CoeffRessources;
	shape.setPosition(newPos);
	m_window.draw(shape);
}

void View::drawDeraumere(sf::CircleShape & shape, sf::Vector2f newPos)
{
	shape.setFillColor(Color::Deraumere);

	newPos.y += Settings::CoeffRessources;
	shape.setPosition(newPos);
	m_window.draw(shape);
}

void View::drawSibur(sf::CircleShape & shape, sf::Vector2f newPos)
{
	shape.setFillColor(Color::Sibur);

	newPos.x += Settings::CoeffRessources;
	newPos.y += Settings::CoeffRessources;
	shape.setPosition(newPos);
	m_window.draw(shape);
}

void View::drawMendiane(sf::CircleShape & shape, sf::Vector2f newPos)
{
	shape.setFillColor(Color::Mendiane);

	newPos.x += Settings::CoeffRessources * 1;
	newPos.y += Settings::CoeffRessources * 2;
	shape.setPosition(newPos);
	m_window.draw(shape);
}

void View::drawPhiras(sf::CircleShape & shape, sf::Vector2f newPos)
{
	shape.setFillColor(Color::Phiras);

	newPos.x += Settings::CoeffRessources * 2;
	shape.setPosition(newPos);
	m_window.draw(shape);
}

void View::drawThystame(sf::CircleShape & shape, sf::Vector2f newPos)
{
	shape.setFillColor(Color::Thystame);

	newPos.x += Settings::CoeffRessources * 2;
	newPos.y += Settings::CoeffRessources * 2;
	shape.setPosition(newPos);
	m_window.draw(shape);
}