#ifndef VIEW_HPP__

# define VIEW_HPP__

#include <SFML/Graphics.hpp>

#include "Zappy.hpp"
#include "Socket.hpp"
#include "SFMLMouseEvent.hpp"
#include "PanelTeam.hpp"
#include "PanelTime.hpp"

class View
{
	typedef void (View::*FPTR)(sf::CircleShape &, sf::Vector2f);
public:
	View(sf::RenderWindow &, Zappy &, Socket &);
	~View();
public:
	void display();
private:
	void _display();
	void _displayBackground();
	void _displayMap();
	void _events();
	void _displayInfoCase();
	void _displayInfoPlayer();

	void _displayPanelCase();
	void _displayPanelCaseNourriture(sf::Vector2u &, unsigned int);
	void _displayPanelCaseLinemate(sf::Vector2u &, unsigned int);
	void _displayPanelCaseDeraumere(sf::Vector2u &, unsigned int);
	void _displayPanelCaseSibur(sf::Vector2u &, unsigned int);
	void _displayPanelCaseMendiane(sf::Vector2u &, unsigned int);
	void _displayPanelCasePhiras(sf::Vector2u &, unsigned int);
	void _displayPanelCaseThystame(sf::Vector2u &, unsigned int);

	void _displayPanelPlayer();
	void _displayPlayers();


	void _displayPanelTime();

	void _displayPanelTeams();

	template <typename T>
	bool onScreen(T &, sf::View &);

	void _displayEndGame();

	void _moveView(int,int);
	void _zoomView(float);
	void _rotateView(float);
	bool _detectCollision(sf::FloatRect, int , int);
	void _drawRessoucesOfCase(Case & obj);

	void _displayIncantation(Case *, std::vector<sf::Sprite> &);
	void _displayMapEvents(Case *);
private:
	Zappy & m_zappy;
	sf::RenderWindow & m_window;
	sf::View currentView;
	sf::View gameView;
	bool mouseClicked;
	SFMLMouseEvent mouseEvent;
	Case * focusedBloc;
	Player * focusedPlayer;
	sf::Font m_font;
	Socket & m_sock;
	sf::Sprite bg;
private:
	void drawNourriture(sf::CircleShape &, sf::Vector2f);
	void drawLinemate(sf::CircleShape &, sf::Vector2f);
	void drawDeraumere(sf::CircleShape &, sf::Vector2f);
	void drawSibur(sf::CircleShape &, sf::Vector2f);
	void drawMendiane(sf::CircleShape &, sf::Vector2f);
	void drawPhiras(sf::CircleShape &, sf::Vector2f);
	void drawThystame(sf::CircleShape &, sf::Vector2f);
	std::map<unsigned int, FPTR> mapFptr;
	/* gui elements */
	sf::CircleShape circleShape;
private:
	PanelTeam panelLeft;
	PanelTime panelRight;
};

const int COEFFICIENT_MOVE = 7;
const int PANELSIZE_Y      = 100;

#endif // EOF - View.hpp