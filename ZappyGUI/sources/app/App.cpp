#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>

#include "App.hpp"
#include "Login.hpp"
#include "View.hpp"
#include "Reception.hpp"
#include "Settings.hpp"

App::App():
sock("TCP")
{
}

App::~App(){}

void App::initialize()
{
	sf::ContextSettings settings;

	/* antialiasing */
	settings.antialiasingLevel = Settings::AntiAliasing;
	/* create the rendering window */
	m_window.create(
		sf::VideoMode(Settings::WindowSizeX, Settings::WindowSizeY),
		Settings::WindowTitle,
		sf::Style::Default,
		settings);
	/* settings the fps */
	m_window.setFramerateLimit(Settings::FPS);
}

void App::run()
{
	/* connexion to server */
	_connexion();
	/* display world */
	View view(m_window, m_zappy, sock);
	view.display();
    while (m_window.isOpen())
    {
    	m_window.clear();
    	_events();
    	m_window.display();
    }
    pthread_cancel(t1->native_handle());
}

void App::_events()
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		/* cross */
		if (event.type == sf::Event::Closed)
			m_window.close();
	}
}

void App::_connexion()
{
	/* default credential for testing purposes */
	std::string ip = "127.0.0.1";
	std::string port = "3535";

	/* login screen */
	Login login(m_window);
	login.getCredentials(ip, port);

	/* initialization of socket */
	sock.initSocket(ip, port);
	/* connection to server */
	sock.Connection();

	/* launching a thread for the protocol */
	Reception *recep = new Reception(sock, m_zappy);
	t1 = new std::thread(Reception::threadLaunch, recep);

	/* waiting for intialization of the base - should put a timer ? */
	while (!m_zappy.getIsSet())
		usleep(100); /* no 100% cpu */
	std::cout << "[App]\t->\tconnected to server : [" << ip << " : " << port << "]" << std::endl;
}
