#ifndef PANEL_TEAM_HPP

# define PANEL_TEAM_HPP

#include "Zappy.hpp"
#include "Settings.hpp"
#include "Color.hpp"
#include "TextureManager.hpp"
#include "SFMLMouseEvent.hpp"

class PanelTeam
{
public:
	PanelTeam(Zappy &, sf::RenderWindow &);
	~PanelTeam();
private:
	Zappy & m_zappy;
	sf::RenderWindow & m_window;
	unsigned int teamID;
	sf::Vector2u windowSize;
private:
	sf::Sprite arrowLeft;
	sf::Sprite arrowRight;

	sf::RectangleShape arrowLeftBloc;
	sf::RectangleShape arrowRightBloc;

	sf::RectangleShape panel;
	Team * focusedTeam;
	sf::Text teamText;
public:
	void display(SFMLMouseEvent &, Player ** focusedPlayer);
	void showArrows();
	void checkClickArrows(SFMLMouseEvent &);
	void descTeam(SFMLMouseEvent &, Player **);
	void showTeamName(Team * focusedTeam);
	void drawDescTeam(Team * focusedTeam);
	void descTeamEvents(SFMLMouseEvent & mouseEvent);
	void descTeamBlocs(SFMLMouseEvent & mouseEvent, Player **);
public:
	unsigned int oldBegin;

	sf::Sprite arrowDown;
	sf::Sprite arrowUp;

	sf::RectangleShape arrowDownBloc;
	sf::RectangleShape arrowUpBloc;

	sf::RectangleShape backgroundPlayer;
};

#endif // EOF - PanelTeam.hpp