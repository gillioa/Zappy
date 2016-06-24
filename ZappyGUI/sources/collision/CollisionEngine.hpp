#ifndef COLLISION_ENGINE_HPP__

# define COLLISION_ENGINE_HPP__

#include <SFML/Graphics.hpp>

/* collision functions - global bounds*/
namespace CollisionEngine
{
	bool pointVSPoint(sf::Vector2f &, sf::Vector2f &); /* =) */

	/* rectangle shape */
	bool pointVSshape(sf::RenderWindow &, sf::RectangleShape ,int , int);
	/* sprite */
	bool pointVSsprite(sf::RenderWindow &, sf::Sprite ,int , int);
}

#endif // EOF - CollisionEnfine.hpp