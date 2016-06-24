#include <sstream>

#include "View.hpp"

void View::_displayPanelCaseNourriture(sf::Vector2u & windowSize, unsigned int nb)
{
	sf::CircleShape circleShape(15);
	sf::Text text;
	std::stringstream ss;

	text.setFont(m_font);
	text.setCharacterSize(Settings::SizeTextLegendRessources);
	text.setColor(Color::Nourriture);
	text.setPosition( sf::Vector2f(110, windowSize.y - PANELSIZE_Y + 55) );

	text.setString("Nourriture");

	circleShape.setFillColor(Color::Nourriture);
	circleShape.setPosition(sf::Vector2f(125, windowSize.y - PANELSIZE_Y + 25) );

	m_window.draw(circleShape);
	m_window.draw(text);

	ss << nb;

	text.setString(ss.str());
	text.setColor(sf::Color::Black);
	text.setPosition(sf::Vector2f(136, windowSize.y - PANELSIZE_Y + 30) );
	m_window.draw(text);
}

void View::_displayPanelCaseLinemate(sf::Vector2u & windowSize, unsigned int nb)
{
	sf::CircleShape circleShape(15);
	sf::Text text;
	std::stringstream ss;

	text.setFont(m_font);
	text.setCharacterSize(Settings::SizeTextLegendRessources);
	text.setColor(Color::Linemate);
	text.setPosition( sf::Vector2f(148, windowSize.y - PANELSIZE_Y + 5) );

	text.setString("Linemate");

	circleShape.setFillColor(Color::Linemate);
	circleShape.setPosition(sf::Vector2f(160, windowSize.y - PANELSIZE_Y + 25) );

	m_window.draw(circleShape);
	m_window.draw(text);

	ss << nb;

	text.setString(ss.str());
	text.setColor(sf::Color::Black);
	text.setPosition(sf::Vector2f(171, windowSize.y - PANELSIZE_Y + 30) );
	m_window.draw(text);
}

void View::_displayPanelCaseDeraumere(sf::Vector2u &windowSize , unsigned int nb)
{
	sf::CircleShape circleShape(15);
	sf::Text text;
	std::stringstream ss;

	text.setFont(m_font);
	text.setCharacterSize(Settings::SizeTextLegendRessources);
	text.setColor(Color::Deraumere);
	text.setPosition( sf::Vector2f(180, windowSize.y - PANELSIZE_Y + 55) );

	text.setString("Deraumere");

	circleShape.setFillColor(Color::Deraumere);
	circleShape.setPosition(sf::Vector2f(195, windowSize.y - PANELSIZE_Y + 25) );

	m_window.draw(circleShape);
	m_window.draw(text);

	ss << nb;

	text.setString(ss.str());
	text.setColor(sf::Color::Black);
	text.setPosition(sf::Vector2f(206, windowSize.y - PANELSIZE_Y + 30) );
	m_window.draw(text);
}

void View::_displayPanelCaseSibur(sf::Vector2u &windowSize, unsigned int nb)
{
	sf::CircleShape circleShape(15);
	sf::Text text;
	std::stringstream ss;

	text.setFont(m_font);
	text.setCharacterSize(Settings::SizeTextLegendRessources);
	text.setColor(Color::Sibur);
	text.setPosition( sf::Vector2f(228, windowSize.y - PANELSIZE_Y + 5) );

	text.setString("Sibur");

	circleShape.setFillColor(Color::Sibur);
	circleShape.setPosition(sf::Vector2f(230, windowSize.y - PANELSIZE_Y + 25) );

	m_window.draw(circleShape);
	m_window.draw(text);

	ss << nb;

	text.setString(ss.str());
	text.setColor(sf::Color::Black);
	text.setPosition(sf::Vector2f(241, windowSize.y - PANELSIZE_Y + 30) );
	m_window.draw(text);
}

void View::_displayPanelCaseMendiane(sf::Vector2u &windowSize, unsigned int nb)
{
	sf::CircleShape circleShape(15);
	sf::Text text;
	std::stringstream ss;

	text.setFont(m_font);
	text.setCharacterSize(Settings::SizeTextLegendRessources);
	text.setColor(Color::Mendiane);
	text.setPosition( sf::Vector2f(256, windowSize.y - PANELSIZE_Y + 55) );

	text.setString("Mendiane");

	circleShape.setFillColor(Color::Mendiane);
	circleShape.setPosition(sf::Vector2f(265, windowSize.y - PANELSIZE_Y + 25) );

	m_window.draw(circleShape);
	m_window.draw(text);

	ss << nb;

	text.setString(ss.str());
	text.setColor(sf::Color::Black);
	text.setPosition(sf::Vector2f(276, windowSize.y - PANELSIZE_Y + 30) );
	m_window.draw(text);
}

void View::_displayPanelCasePhiras(sf::Vector2u &windowSize, unsigned int nb)
{
	sf::CircleShape circleShape(15);
	sf::Text text;
	std::stringstream ss;


	text.setFont(m_font);
	text.setCharacterSize(Settings::SizeTextLegendRessources);
	text.setColor(Color::Phiras);
	text.setPosition( sf::Vector2f(298, windowSize.y - PANELSIZE_Y + 5) );

	text.setString("Phiras");

	circleShape.setFillColor(Color::Phiras);
	circleShape.setPosition(sf::Vector2f(300, windowSize.y - PANELSIZE_Y + 25) );

	m_window.draw(circleShape);
	m_window.draw(text);

	ss << nb;

	text.setString(ss.str());
	text.setColor(sf::Color::Black);
	text.setPosition(sf::Vector2f(311, windowSize.y - PANELSIZE_Y + 30) );
	m_window.draw(text);
}

void View::_displayPanelCaseThystame(sf::Vector2u & windowSize, unsigned int nb)
{
	sf::CircleShape circleShape(15);
	sf::Text text;
	std::stringstream ss;

	text.setFont(m_font);
	text.setCharacterSize(Settings::SizeTextLegendRessources);
	text.setColor(Color::Thystame);
	text.setPosition( sf::Vector2f(325, windowSize.y - PANELSIZE_Y + 55) );

	text.setString("Thystame");

	circleShape.setFillColor(Color::Thystame);
	circleShape.setPosition(sf::Vector2f(335, windowSize.y - PANELSIZE_Y + 25) );

	m_window.draw(circleShape);
	m_window.draw(text);

	ss << nb;

	text.setString(ss.str());
	text.setColor(sf::Color::Black);
	text.setPosition(sf::Vector2f(346, windowSize.y - PANELSIZE_Y + 30) );
	m_window.draw(text);
}
