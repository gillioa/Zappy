#include <string>
#include <sstream>

#include "PanelTime.hpp"
#include "CollisionEngine.hpp"

PanelTime::PanelTime(Zappy & data, sf::RenderWindow & win, Socket & sock):
m_zappy(data),
m_window(win),
windowSize(m_window.getSize()),
rectangle(sf::Vector2f(75, 225)),
rectangeAU(sf::Vector2f(75,75)),
rectangeAD(sf::Vector2f(75,75)),
m_sock(sock)
{
	rectangeAU.setPosition(sf::Vector2f(windowSize.x - 75, Settings::BeginPanelTimeY));
	rectangeAD.setPosition(sf::Vector2f(windowSize.x - 75, Settings::BeginPanelTimeY + 150));

	arrowSprite.setTexture(TextureManager::Instance().getTexture(ARROW_UP));
	arrowSprite.setPosition(sf::Vector2f(windowSize.x - 75, Settings::BeginPanelTimeY));

	timeText.setCharacterSize(20);
	timeText.setColor(Color::Time);
	timeText.setFont(TextureManager::Instance().getFont());
	timeText.setPosition(sf::Vector2f(windowSize.x - 55, Settings::BeginPanelTimeY + 100));

	arrowDownSprite.setTexture(TextureManager::Instance().getTexture(ARROW_DOWN));
	arrowDownSprite.setPosition(sf::Vector2f(windowSize.x - 75, Settings::BeginPanelTimeY + 150));

	rectangle.setFillColor(Color::PanelTime);
	rectangle.setPosition(sf::Vector2f(windowSize.x - 75, Settings::BeginPanelTimeY));
}

void PanelTime::display(SFMLMouseEvent & mouseEvent)
{
	rectangeAU.setFillColor(Color::PanelAU);
	rectangeAD.setFillColor(Color::PanelAD);

	events(mouseEvent);

	std::stringstream ss;

	ss << m_zappy.getTimeRef();


	timeText.setString(ss.str());

	m_window.draw(rectangle);
	m_window.draw(rectangeAU);
	m_window.draw(rectangeAD);
	m_window.draw(arrowSprite);
	m_window.draw(arrowDownSprite);
	m_window.draw(timeText);
}

void PanelTime::events(SFMLMouseEvent & mouseEvent)
{
	if (mouseEvent.isMouseClicked() &&
		CollisionEngine::pointVSshape( m_window, rectangeAU , mouseEvent.getX(), mouseEvent.getY()))
	{
		rectangeAU.setFillColor(Color::PanelAU_ON);
		m_zappy.sendTimeToServer(m_zappy.getTimeRef() + Settings::TimePitch, m_sock);

	}
	else if (mouseEvent.isMouseClicked() &&
		CollisionEngine::pointVSshape( m_window, rectangeAD , mouseEvent.getX(), mouseEvent.getY()))
	{
		rectangeAD.setFillColor(Color::PanelAD_ON);
		if (m_zappy.getTimeRef() > Settings::TimePitch)
			m_zappy.sendTimeToServer(m_zappy.getTimeRef() - Settings::TimePitch, m_sock);
		else
			m_zappy.sendTimeToServer(1, m_sock);
	}
}

PanelTime::~PanelTime()
{

}