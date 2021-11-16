#pragma once
#include <SFML/Graphics.hpp>


class PointCounter {

public:
	PointCounter(sf::Vector2f position);
	sf::Text text;

	void AddPoint();

	void draw(sf::RenderWindow& window);

	int getPoints();

	void restart();

private:

	int points = 0;
	sf::Font font;

};

