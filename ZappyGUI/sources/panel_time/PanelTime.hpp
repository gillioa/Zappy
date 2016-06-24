#ifndef PANEL_TIME_HPP

# define PANEL_TIME_HPP

#include "Zappy.hpp"
#include "Settings.hpp"
#include "Color.hpp"
#include "TextureManager.hpp"
#include "SFMLMouseEvent.hpp"

class PanelTime
{
public:
	PanelTime(Zappy &, sf::RenderWindow &, Socket &);
	~PanelTime();
	void display(SFMLMouseEvent & mouseEvent);
private:
	Zappy & m_zappy;
	sf::RenderWindow & m_window;
	sf::Vector2u windowSize;

	sf::RectangleShape rectangle;
	sf::RectangleShape rectangeAU;
	sf::RectangleShape rectangeAD;

	sf::Sprite arrowSprite;

	Socket & m_sock;
	sf::Text timeText;
	sf::Sprite arrowDownSprite;
private:
	void events(SFMLMouseEvent & mouseEvent);
};

#endif // EOF - PanelTime.hpp