#ifndef APP_HPP

# define APP_HPP

#include <thread>
#include <SFML/Graphics.hpp>

#include "Zappy.hpp"
#include "Socket.hpp"

class App
{
public:
	App();
	~App();
public:
	void initialize();
	void run();
private:
	sf::RenderWindow m_window;
	Zappy            m_zappy;
	std::thread     *t1;
	Socket           sock;
private:
	void _events();
	void _connexion();
};

#endif // APP_HPP