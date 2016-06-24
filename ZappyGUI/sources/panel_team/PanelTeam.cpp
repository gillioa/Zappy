#include <string>
#include <sstream>

#include "PanelTeam.hpp"
#include "Settings.hpp"
#include "Color.hpp"
#include "TextureManager.hpp"
#include "SFMLMouseEvent.hpp"
#include "CollisionEngine.hpp"

/* must be default view to work properly */
PanelTeam::PanelTeam(Zappy &data, sf::RenderWindow & win):
m_zappy(data),
m_window(win),
teamID(0),
arrowLeftBloc(sf::Vector2f(50,50)),
arrowRightBloc(sf::Vector2f(50,50)),
panel(sf::Vector2f(Settings::PanelTeamX, windowSize.y - Settings::PanelSizeY)),
focusedTeam(0),
oldBegin(0),
arrowDownBloc(sf::Vector2f(175,30)),
arrowUpBloc(sf::Vector2f(175,30)),
backgroundPlayer(sf::Vector2f(175, Settings::PanelTeamSizeBlocPlayer - 10))
{
	/* background of arrows */
	arrowLeftBloc.setFillColor(sf::Color(0,0,0,0));
	arrowRightBloc.setFillColor(sf::Color(0,0,0,0));
	arrowLeftBloc.setPosition(sf::Vector2f(0,50));
	arrowRightBloc.setPosition(sf::Vector2f(Settings::PanelTeamX - 50, 50));
	/* arrows */
	arrowLeft.setTexture(TextureManager::Instance().getTexture(ARROW_LEFT));
	arrowLeft.setPosition(sf::Vector2f(0,50));
	arrowRight.setTexture(TextureManager::Instance().getTexture(ARROW_RIGHT));
	arrowRight.setPosition(sf::Vector2f(Settings::PanelTeamX - 50, 50));
	/* global panel */
	panel.setFillColor(Color::PanelTeam);
	panel.setPosition(sf::Vector2f(0,0));
	/* scroll players */
	arrowUpBloc.setPosition(sf::Vector2f(10,280));
	arrowDownBloc.setPosition(sf::Vector2f(10,530));;
	arrowUp.setTexture(TextureManager::Instance().getTexture(ARROW_UP_SMALL));
	arrowUp.setPosition(sf::Vector2f(Settings::PanelTeamX / 2 - 15,280));
	arrowDown.setTexture(TextureManager::Instance().getTexture(ARROW_DOWN_SMALL));
	arrowDown.setPosition(sf::Vector2f(Settings::PanelTeamX / 2 - 15,530));
}

PanelTeam::~PanelTeam(){}

void PanelTeam::display(SFMLMouseEvent & mouseEvent, Player ** focusedPlayer)
{
	focusedTeam = m_zappy.getTeamById(teamID);
	windowSize = m_window.getSize();

	m_window.draw(panel);
	showArrows();
	checkClickArrows(mouseEvent);
	drawDescTeam(focusedTeam);
	descTeam(mouseEvent, focusedPlayer);
}

void PanelTeam::showArrows()
{
	m_window.draw(arrowLeftBloc);
	m_window.draw(arrowRightBloc);
	m_window.draw(arrowLeft);
	m_window.draw(arrowRight);
}

void PanelTeam::checkClickArrows(SFMLMouseEvent & mouseEvent)
{
	arrowLeftBloc.setFillColor(sf::Color(0,0,0,0));
	arrowRightBloc.setFillColor(sf::Color(0,0,0,0));
	if (mouseEvent.isMouseClicked() &&
		CollisionEngine::pointVSshape( m_window, arrowLeftBloc , mouseEvent.getX(), mouseEvent.getY()))
	{
		arrowLeftBloc.setFillColor(Color::PanelTeamArrowOn);
		if (teamID > 0)
			teamID -= 1;
		else
			teamID = m_zappy.getTeam().size() - 1;
	}
	else if (mouseEvent.isMouseClicked() &&
		CollisionEngine::pointVSshape( m_window, arrowRightBloc , mouseEvent.getX(), mouseEvent.getY()))
	{
		if (teamID < m_zappy.getTeam().size() - 1)
			teamID += 1;
		else
			teamID = 0;
		arrowRightBloc.setFillColor(Color::PanelTeamArrowOn);
	}
}

void PanelTeam::showTeamName(Team * focusedTeam)
{
	/* init */
	teamText.setString(focusedTeam->getTeamName());
	teamText.setFont(TextureManager::Instance().getFont());
	teamText.setCharacterSize(18);
	teamText.setPosition(sf::Vector2f(50,60));
	/* draw */
	m_window.draw(teamText);
}

void PanelTeam::drawDescTeam(Team * focusedTeam)
{
	if (!focusedTeam)
		return;
	std::stringstream ss;

	ss
	<< focusedTeam->getPlayers().size() << " players" << std::endl
	<< focusedTeam->getEggs().size()    << " oeufs"   << std::endl
	<< focusedTeam->getMaxLevel()       << " niveau max" << std::endl;
	teamText.setString(ss.str());
	teamText.setPosition(sf::Vector2f(50,130));

	m_window.draw(teamText);
}

void PanelTeam::descTeamEvents(SFMLMouseEvent & mouseEvent)
{
	if (mouseEvent.isMouseClicked() &&
		CollisionEngine::pointVSshape( m_window, arrowUpBloc , mouseEvent.getX(), mouseEvent.getY()))
	{
		if (oldBegin > 0)
			--oldBegin;
		arrowUpBloc.setFillColor(Color::PanelTeamArrowOn);
	}
	else if (mouseEvent.isMouseClicked() &&
		CollisionEngine::pointVSshape( m_window, arrowDownBloc , mouseEvent.getX(), mouseEvent.getY()))
	{
		++oldBegin;
		arrowDownBloc.setFillColor(Color::PanelTeamArrowOn);
	}
}

void PanelTeam::descTeamBlocs(SFMLMouseEvent & mouseEvent, Player ** focusedPlayer)
{
	std::list<Player *> playersOfTeam = focusedTeam->getPlayers();
	std::stringstream ss;
	unsigned int coeff = 0;
	unsigned int maxPlayerDisplayed = Settings::PanelTeamPlayerDisplayed;
	unsigned int begin = oldBegin;
	bool playerToDraw = false;

	for (auto &i : playersOfTeam)
	{
		if (begin > 0)
		{
			--begin;
			continue;
		}
		playerToDraw = true;
		if (maxPlayerDisplayed == 0)
			break;
		ss.str("");
		ss
		<< "ID  :" << i->getId() << std::endl
		<< "LVL :" << i->getLevel() << std::endl;
		teamText.setPosition(20,325 + coeff * Settings::PanelTeamSizeBlocPlayer);
		backgroundPlayer.setPosition(10,320 + coeff * Settings::PanelTeamSizeBlocPlayer);
		teamText.setString(ss.str());
		backgroundPlayer.setFillColor(sf::Color(0,0,0,110));
		if (mouseEvent.isMouseClicked() &&
			CollisionEngine::pointVSshape( m_window, backgroundPlayer , mouseEvent.getX(), mouseEvent.getY()))
		{
			*focusedPlayer = i;
			backgroundPlayer.setFillColor(sf::Color(0,0,0,180));
		}

		m_window.draw(backgroundPlayer);
		m_window.draw(teamText);
		++coeff;
		--maxPlayerDisplayed;
	}
	if (!playerToDraw)
	{
		if (oldBegin > 0)
			--oldBegin;
	}
}

void PanelTeam::descTeam(SFMLMouseEvent & mouseEvent, Player ** focusedPlayer)
{
	if (!focusedTeam)
		return;

	std::stringstream ss;
	showTeamName(focusedTeam);
	ss.str("");

	ss << "Players list" << std::endl << std::endl;
	teamText.setPosition(20,250);
	teamText.setString(ss.str());
	m_window.draw(teamText);

	arrowUpBloc.setFillColor(sf::Color(0,0,0,0));
	arrowDownBloc.setFillColor(sf::Color(0,0,0,0));

	descTeamEvents(mouseEvent);
	m_window.draw(arrowUpBloc);
	m_window.draw(arrowDownBloc);
	m_window.draw(arrowUp);
	m_window.draw(arrowDown);
	descTeamBlocs(mouseEvent, focusedPlayer);
	sf::RectangleShape teamColor(sf::Vector2f(25,25));

	teamColor.setPosition(sf::Vector2f(10,130));
	teamColor.setFillColor(focusedTeam->getTeamColor());
	m_window.draw(teamColor);
	(void)focusedPlayer;
}