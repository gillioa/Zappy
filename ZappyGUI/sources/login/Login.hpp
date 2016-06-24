#ifndef LOGIN_HPP__

# define LOGIN_HPP__

#include <tuple>
#include <SFML/Graphics.hpp>

class Login
{
public:
	typedef enum e_direction { SUP, SDOWN } e_direction;
	Login(sf::RenderWindow &);
	~Login();
public:
	void getCredentials(std::string &, std::string &);
private:
	sf::RenderWindow &   m_window;
	std::string          m_ip;
	std::string          m_port;
	const std::vector<std::string>    m_affichage =
	{
		"IP :",
		"Port :"
	};
	unsigned int m_position;
	std::vector<sf::Vector2f> m_rect_position;
	std::vector< std::tuple<sf::Vector2f, sf::Vector2f, sf::Color> > m_rects;
private:
	bool _events(std::string &, std::string &);
	void _updatePosition(e_direction);
	void _display();
	void _displayUserInputs();
	void _displayStrings();
	void _displayBackground();
	void _retrieveChar(sf::Event &);
	std::string & _getStringFromPosition();
	void _moveCursor(sf::Event &);
};

#endif // EOF - Login.hpp