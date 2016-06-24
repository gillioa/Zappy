#ifndef SFML_MOUSE_EVENT_HPP

# define SFML_MOUSE_EVENT_HPP

#include <SFML/Graphics.hpp>

class SFMLMouseEvent
{
public:
	SFMLMouseEvent();
	~SFMLMouseEvent();
	void update(sf::RenderWindow &, sf::Event);
	bool isMouseClicked() const;
	int getX() const;
	int getY() const;
	void reset();
private:
	sf::Event mouseEvent;
	bool mouseClicked;
	int _x;
	int _y;
};

#endif // EOF - SFMLMouseEvent.hpp