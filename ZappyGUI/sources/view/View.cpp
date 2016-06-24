#include <iostream>
#include <string>
#include <sstream>

#include "View.hpp"
#include "CollisionEngine.hpp"
#include "TextureManager.hpp"
#include "Settings.hpp"
#include "CollisionEngine.hpp"

View::View(sf::RenderWindow & win, Zappy & zappy, Socket & sock) :
m_zappy(zappy),
m_window(win),
currentView(win.getView()),
gameView(m_window.getView()),
focusedBloc(0),
focusedPlayer(0),
m_font(TextureManager::Instance().getFont()),
m_sock(sock),
bg(TextureManager::Instance().getTexture(BACKGROUND)),
circleShape(15),
panelLeft(zappy, win),
panelRight(zappy, win, sock)
{
//	bg.setTexture(
	mapFptr[Nourriture] = &View::drawNourriture;
	mapFptr[Linemate] = &View::drawLinemate;
	mapFptr[Deraumere] = &View::drawDeraumere;
	mapFptr[Sibur] = &View::drawSibur;
	mapFptr[Mendiane] = &View::drawMendiane;
	mapFptr[Phiras] = &View::drawPhiras;
	mapFptr[Thystame] = &View::drawThystame;
}

View::~View() {}

void View::display()
{
	while (m_window.isOpen())
    {
    	_events();
    	/* clear the window */
    	m_window.clear();
    	/* display elements*/
    	_displayBackground();
    	m_window.setView(gameView);
    	_display();
    	m_window.setView(m_window.getDefaultView());
    	panelRight.display(mouseEvent);
    	panelLeft.display(mouseEvent, &focusedPlayer);
    	_displayInfoCase();
    	_displayInfoPlayer();
    	if (m_zappy.getEndGame())
    		_displayEndGame();
    	m_window.display();
    	mouseEvent.reset();
    }
}


void View::_display()
{
	_displayMap();
	_displayPlayers();
}

void View::_displayEndGame()
{
	m_window.setView(m_window.getDefaultView());
	sf::Text text;
	sf::Vector2u windowSize = m_window.getSize();
	const std::string & teamName = m_zappy.getWinnerTeam();
	std::stringstream ss;

	ss << "Victoire de : " << teamName;
	text.setFont(TextureManager::Instance().getFont());
	text.setCharacterSize(40);
	text.setPosition(windowSize.x / 2 - (ss.str().size() / 2) * 20,20);
	text.setColor(sf::Color::Black);
	text.setString(ss.str());
	m_window.draw(text);
	m_window.setView(gameView);
}

void View::_events()
{
	sf::Event event;
	mouseClicked = false;

	while (m_window.pollEvent(event))
	{
		/* cross */
		if (event.type == sf::Event::Closed)
			m_window.close();
		/* click */
		if (event.type == sf::Event::MouseButtonPressed)
			mouseEvent.update(m_window, event);
	}
	/* arrows */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		_moveView(-COEFFICIENT_MOVE,0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		_moveView(COEFFICIENT_MOVE,0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		_moveView(0,-COEFFICIENT_MOVE);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		_moveView(0,COEFFICIENT_MOVE);
	/* zoom */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
		_zoomView(1.03);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
		_zoomView(0.97);

}

void View::_moveView(int x, int y) { gameView.move(x,y); }
void View::_zoomView(float x)      { gameView.zoom(x);   }
void View::_rotateView(float x) { gameView.setRotation(gameView.getRotation() + x); }

bool View::_detectCollision(sf::FloatRect boundingBox, int x, int y)
{

	sf::Vector2f point(x, y);
	if (boundingBox.contains(point))
	{
		return true;
	}
	return false;
}

void View::_displayBackground()
{
	m_window.setView(m_window.getDefaultView());
	m_window.draw(bg);
}

template <typename T>
bool View::onScreen(T & tile, sf::View & gameView)
{
	sf::FloatRect boundingBox = tile.getGlobalBounds();
	sf::FloatRect viewPort;

    viewPort.left   = gameView.getCenter().x - gameView.getSize().x/2.f;
    viewPort.top    = gameView.getCenter().y - gameView.getSize().y/2.f;
    viewPort.width  = gameView.getSize().x;
    viewPort.height = gameView.getSize().y;

	if (viewPort.intersects(boundingBox))
		return true;
	return false;
}

void View::_displayIncantation(Case * i, std::vector<sf::Sprite> & v)
{
	if (i->getIncantationIsSet())
	{
		sf::Sprite spriteSun;
		spriteSun.setTexture(TextureManager::Instance().getTexture(SUN_SMALL));
		spriteSun.setPosition(sf::Vector2f(i->getShape().getPosition().x + 12, i->getShape().getPosition().y + 12));
		spriteSun.setOrigin(sf::Vector2f( spriteSun.getOrigin().x + 25, spriteSun.getOrigin().y + 25));
		spriteSun.rotate(i->getIncRotation());
		i->updateIncLevel();
		v.push_back(spriteSun);
	}
}

void View::_displayMapEvents(Case * i)
{
	if (mouseEvent.isMouseClicked() &&
		CollisionEngine::pointVSshape( m_window, i->getShape(), mouseEvent.getX(), mouseEvent.getY()))
	{
		if (focusedBloc)
			focusedBloc->unFocusShape();
		focusedBloc = i;
		i->focusShape();
	}
}

void View::_displayMap()
{
	Map & zappyMap = m_zappy.getMap();
	const std::vector<Case *> & zappyMapDetail = zappyMap.getVectCase();
	std::vector<sf::Sprite> v;

	for (auto &i : zappyMapDetail)
	{
		const sf::RectangleShape & a = i->getShape();
		if (!onScreen(a, gameView))
			continue;
		_displayMapEvents(i);
		_displayIncantation(i, v);
		m_window.draw(i->getShape());
		_drawRessoucesOfCase(*i);
	}
	for (auto &s : v)
		m_window.draw(s);
}

void View::_drawRessoucesOfCase(Case & obj)
{
	sf::CircleShape shape(2);

	sf::Vector2f posShape = obj.getShape().getPosition();
	posShape.x += 2;
	posShape.y += 2;

	for ( auto &i : obj.getRessources())
		(i.second) ? (this->*mapFptr[i.first])(shape, posShape) : (void)i.second;
}

void View::_displayInfoPlayer()
{
	if (!focusedPlayer)
		return;
	_displayPanelPlayer();
}

void View::_displayPanelPlayer()
{
	sf::View currentView    = m_window.getView();
	sf::View defaultView    = m_window.getDefaultView();
	sf::Vector2u windowSize = m_window.getSize();
	std::stringstream ss;
	sf::Sprite sprite;


	sprite.setTexture( TextureManager::Instance().getTexture(BIG_PLAYER) );
	sprite.setPosition( sf::Vector2f(windowSize.x - 450, windowSize.y - PANELSIZE_Y));
	ss << "id\t:\t" << focusedPlayer->getId() << "\n";
	ss << "lvl\t:\t" << focusedPlayer->getLevel() << "\n";
	ss << "x/y\t:\t" << focusedPlayer->getX() << "/" << focusedPlayer->getY() << "\n";
	ss << "action:\t:\t" << focusedPlayer->getStringAction() << std::endl;
	ss << "broadcast message:\t" << focusedPlayer->getBroadCastMsg() << "\n";
	m_window.setView(defaultView);
	/* affichage */

	sf::Text text;

	text.setFont(m_font);
	text.setCharacterSize(Settings::SizeTextLegendPlayer);
	text.setColor(sf::Color(34,49,63));

	text.setPosition(sf::Vector2f(windowSize.x - 380,windowSize.y - PANELSIZE_Y + 5));
	text.setString(ss.str());
	m_window.draw(text);
	m_window.draw(sprite);

	/* inventory */
	sf::CircleShape circle(15);



	std::map<eRessources, unsigned int> const inventory = focusedPlayer->getRessource();

	/* circle settings */

	ss.str("");
	text.setCharacterSize(18);

	ss << inventory.at(Linemate);
	text.setString(ss.str());
	circle.setPosition(sf::Vector2f(windowSize.x - 200, windowSize.y - PANELSIZE_Y + 10));
	circle.setFillColor(Color::Linemate);
	text.setPosition(sf::Vector2f(windowSize.x - 190, windowSize.y - PANELSIZE_Y + 12));
	m_window.draw(circle);
	m_window.draw(text);

	ss.str("");

	ss << inventory.at(Deraumere);
	text.setString(ss.str());
	circle.setPosition(sf::Vector2f(windowSize.x - 170, windowSize.y - PANELSIZE_Y + 10));
	circle.setFillColor(Color::Deraumere);
	text.setPosition(sf::Vector2f(windowSize.x - 160, windowSize.y - PANELSIZE_Y + 12));
	m_window.draw(circle);
	m_window.draw(text);

	ss.str("");

	ss << inventory.at(Sibur);
	text.setString(ss.str());
	circle.setPosition(sf::Vector2f(windowSize.x - 140, windowSize.y - PANELSIZE_Y + 10));
	circle.setFillColor(Color::Sibur);
	text.setPosition(sf::Vector2f(windowSize.x - 130, windowSize.y - PANELSIZE_Y + 12));
	m_window.draw(circle);
	m_window.draw(text);

	ss.str("");

	ss << inventory.at(Phiras);
	text.setString(ss.str());
	circle.setPosition(sf::Vector2f(windowSize.x - 200, windowSize.y - PANELSIZE_Y + 40));
	circle.setFillColor(Color::Phiras);
	text.setPosition(sf::Vector2f(windowSize.x - 190, windowSize.y - PANELSIZE_Y + 42));
	m_window.draw(circle);
	m_window.draw(text);

	ss.str("");

	ss << inventory.at(Thystame);
	text.setString(ss.str());
	circle.setPosition(sf::Vector2f(windowSize.x - 170, windowSize.y - PANELSIZE_Y + 40));
	circle.setFillColor(Color::Thystame);
	text.setPosition(sf::Vector2f(windowSize.x - 160, windowSize.y - PANELSIZE_Y + 42));
	m_window.draw(circle);
	m_window.draw(text);

	ss.str("");

	ss << inventory.at(Mendiane);
	text.setString(ss.str());
	circle.setPosition(sf::Vector2f(windowSize.x - 140, windowSize.y - PANELSIZE_Y + 40));
	circle.setFillColor(Color::Mendiane);
	text.setPosition(sf::Vector2f(windowSize.x - 130, windowSize.y - PANELSIZE_Y + 42));
	m_window.draw(circle);
	m_window.draw(text);

	m_window.setView(currentView);
}

void View::_displayInfoCase()
{
	sf::RectangleShape panelShape;

	m_window.setView(m_window.getDefaultView());
	sf::Vector2u windowSize = m_window.getSize();
	panelShape.setFillColor(sf::Color(238,238,238,150));
	panelShape.setSize(sf::Vector2f(windowSize.x, PANELSIZE_Y));
	panelShape.setPosition(sf::Vector2f(0,windowSize.y - PANELSIZE_Y));
	m_window.draw(panelShape);
	m_window.setView(gameView);
	if (!focusedBloc)
		return;
	_displayPanelCase();
}

void View::_displayPanelCase()
{
	sf::View currentView    = m_window.getView();
	sf::View defaultView    = m_window.getDefaultView();
	sf::Vector2u windowSize = m_window.getSize();
	sf::Sprite caseSprite;

	sf::CircleShape circleShape(15);

	std::map<eRessources, unsigned int> & ressourcesOfBloc = focusedBloc->getRessources();

	caseSprite.setTexture(TextureManager::Instance().getTexture(BIG_CASE) );
	caseSprite.setPosition( sf::Vector2f(25, windowSize.y - PANELSIZE_Y + 10));


	m_window.setView(defaultView);

	/* informations */ /* a passer en tpf */
	_displayPanelCaseNourriture(windowSize, ressourcesOfBloc[Nourriture]);
	_displayPanelCaseLinemate(windowSize, ressourcesOfBloc[Linemate]);
	_displayPanelCaseDeraumere(windowSize, ressourcesOfBloc[Deraumere]);
	_displayPanelCaseSibur(windowSize, ressourcesOfBloc[Sibur]);
	_displayPanelCaseMendiane(windowSize, ressourcesOfBloc[Mendiane]);
	_displayPanelCasePhiras(windowSize, ressourcesOfBloc[Phiras]);
	_displayPanelCaseThystame(windowSize, ressourcesOfBloc[Thystame]);

	m_window.draw(caseSprite);

	m_window.setView(currentView);
}


void View::_displayPlayers()
{
  m_zappy.lock();
  const std::list<Team *> teams = m_zappy.getTeam();
  
  sf::Sprite sprite;
  sf::Sprite eggSprite;

  sprite.setTexture( TextureManager::Instance().getTexture(PLAYER_SPRITE) );


  for (auto &t : teams)
    {
    	const std::list<Egg*> & eggsOfTeam = t->getEggs();
    	for (auto &e : eggsOfTeam)
    	{
    		Case * objCase = m_zappy.getMap().atCoords(e->getX(), e->getY());
    		if (e->getStat() == Eclot)
    			eggSprite.setTexture( TextureManager::Instance().getTexture(EGG_SMALL_CRACK) );
    		else
    			eggSprite.setTexture( TextureManager::Instance().getTexture(EGG_SMALL) );
    		sprite.setTexture( TextureManager::Instance().getTexture(PLAYER_SPRITE) );
    		eggSprite.setPosition(sf::Vector2f(objCase->getShape().getPosition().x, objCase->getShape().getPosition().y - 5));
    		m_window.draw(eggSprite);
    	}


    	const std::list<Player *> & playersOfTeam = t->getPlayers();
    	for (auto &i : playersOfTeam)
    	{
    		Case * objCase = m_zappy.getMap().atCoords(i->getX(), i->getY());
    		sf::RectangleShape shapeRect =  objCase->getShape();
    		sf::Vector2f positionCase = shapeRect.getPosition();
    		sprite.setPosition(sf::Vector2f(positionCase.x, positionCase.y -30));
    		sprite.setTextureRect(sf::IntRect(0,(i->getOrientation() - 1) * 48,31,48));  
    		if (mouseEvent.isMouseClicked() &&
    			CollisionEngine::pointVSsprite( m_window, sprite, mouseEvent.getX(), mouseEvent.getY()))
    		{
    			focusedPlayer = i;
    		}
    		if (i->getCurrentAction() == Broadcast)
    		{
    			unsigned int bcLvl = i->getBroadCastLevel();
    			unsigned int opacity = bcLvl * ((255 / Settings::SizeBroadCast + 1) + 1);

    			if (opacity > 255)
    				opacity = 255;
    			sf::CircleShape broadCastShape(bcLvl);

    			broadCastShape.setPosition(sf::Vector2f(positionCase.x - bcLvl + 12, positionCase.y - bcLvl + 12));
    			broadCastShape.setFillColor(sf::Color( 52 , 73  , 94, 255 - opacity));

    			m_window.draw(broadCastShape);
    		}
    		i->updateBroadCastLevel();
    		sprite.setColor(t->getTeamColor());
    		m_window.draw(sprite);
    	}
    }
    m_zappy.unlock();
}
