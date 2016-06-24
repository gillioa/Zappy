#include <iostream>
#include <string>

#include "TextureManager.hpp"
#include "Login.hpp"

Login::Login(sf::RenderWindow & win) :
m_window(win),
m_position(0)
{
	m_rect_position.push_back(sf::Vector2f(511,254));
	m_rect_position.push_back(sf::Vector2f(512,383));

	/* position, size, color  */
	auto matique = std::make_tuple(sf::Vector2f(511,254), sf::Vector2f(576,62), sf::Color(150, 50, 250, 0));
	m_rects.push_back( matique );

	matique = std::make_tuple(sf::Vector2f(512,383), sf::Vector2f(576,62), sf::Color(150, 50, 250, 0));

	m_rects.push_back( matique );

	matique = std::make_tuple(sf::Vector2f(707,511), sf::Vector2f(380,60), sf::Color(150,150,150,0));
	m_rects.push_back( matique );
}

Login::~Login()
{
}

void Login::getCredentials(std::string & ip, std::string & port)
{
	sf::Sprite background(TextureManager::Instance().getTexture(LOGIN_SCREEN));
	while (m_window.isOpen())
    {
    	m_window.clear();
    	m_window.draw(background);
    	if (!_events(ip, port))
    		return;
    	_display();
    }
}

bool Login::_events(std::string & ip, std::string & port)
{
	sf::Event event;
	std::string str;
	sf::Text text;

	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window.close();
		if (m_position == 2 && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
		{
			/* try to connect to server */
			ip = m_ip;
			port = m_port;			
			return false;
		}
		_retrieveChar(event);
		_moveCursor(event);
	}
	return true;
}

void Login::_moveCursor(sf::Event & event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
			case sf::Keyboard::Up:
			_updatePosition(SUP);
			break;
			case sf::Keyboard::Down:
			_updatePosition(SDOWN);
			break;
			default:
			break;
		}
	}
}

void Login::_retrieveChar(sf::Event & event)
{
	if (event.type != sf::Event::TextEntered)
		return;
	if (event.text.unicode == 13)
		return;
	std::string & str = _getStringFromPosition();
	if (m_position == 2)
	{

		return;
	}
	if (event.text.unicode < 128)
	{
		if (static_cast<char>(event.text.unicode) == '\b')
		{
			if (str.size() > 0)
				str.pop_back();
		}
		else
			str += static_cast<char>(event.text.unicode);
	}
}

std::string & Login::_getStringFromPosition()
{
	if (m_position == 0)
		return m_ip;
	return m_port;
}

void Login::_display()
{
	_displayBackground();
	_displayUserInputs();
	_displayStrings();
	m_window.display();
}

void Login::_displayBackground()
{
	sf::RectangleShape rectangle(sf::Vector2f(120, 50));

	auto matique = m_rects[m_position];

	std::get<1>(matique);

	rectangle.setPosition( std::get<0>(matique) );
	rectangle.setSize( std::get<1>(matique) );
	rectangle.setFillColor( std::get<2>(matique));
	rectangle.setOutlineThickness(2);
	rectangle.setOutlineColor(sf::Color(250, 150, 100));

	m_window.draw(rectangle);
}

void Login::_displayStrings()
{
	unsigned int coefficient = 0;

	sf::Text text;

	sf::Vector2u winSize = m_window.getSize();
	(void)winSize;
	text.setFont(TextureManager::Instance().getFont());
	text.setColor(sf::Color(50,50,50));
	text.setCharacterSize(45);

	for (auto &i : m_affichage)
	{
		text.setString(i);
		text.setPosition(sf::Vector2f(325,250 + coefficient * 130));
		m_window.draw(text);
		coefficient += 1;
	}
}

void Login::_displayUserInputs()
{
	sf::Text text;
	text.setFont(TextureManager::Instance().getFont());
	text.setColor(sf::Color(50,50,50));
	text.setCharacterSize(45);

	/* draw ip */
	text.setString(m_ip);
	text.setPosition(525, 255);
	m_window.draw(text);

	/* draw port */

	text.setString(m_port);
	text.setPosition(525, 383);
	m_window.draw(text);
}

void Login::_updatePosition(e_direction dir)
{
	if (dir == SDOWN)
	{
		m_position += 1;
		if (m_position >= m_rects.size())
			m_position = 0;
	}
	else
	{
		if (m_position > 0)
			m_position -= 1;
		else
			m_position = m_rects.size() - 1;
	}
}