#ifndef COLOR_HPP__

# define COLOR_HPP__

#include <SFML/Graphics.hpp>

class Color
{
public:
	/* map */
	static sf::Color Case;
	static sf::Color CaseFocus;
	/* pierres */
	static sf::Color Nourriture;
	static sf::Color Linemate;
	static sf::Color Deraumere;
	static sf::Color Sibur;
	static sf::Color Mendiane;
	static sf::Color Phiras;
	static sf::Color Thystame;
	/* panelTime */
	static sf::Color PanelTime;
	static sf::Color Time;
	static sf::Color PanelAU;
	static sf::Color PanelAD;
	static sf::Color PanelAU_ON;
	static sf::Color PanelAD_ON;
	/* panel teams */
	static sf::Color PanelTeam;
	static sf::Color PanelTeamArrowOn;
public:
	/* divers */
	static sf::Color BroadcastInColor;
	static sf::Color BroadcastOutLineColor;
};

#endif // EOF - Color.hpp