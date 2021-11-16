#pragma once

#include "SFML/Graphics.hpp"


class Ball {

public:
	Ball(float radius, sf::Vector2f initLocation, sf::Vector2f ballVec);
	~Ball();

	void setSpeed(float speed);

	void move(float deltaTime);
	void reflect(float deltaY);
	void reset();
	void restart();

	sf::CircleShape getInstance();
	sf::Vector2f getPosition();
	sf::Vector2f direction;
	float getRadius();
	sf::CircleShape instance;
	int lastTouch = 0;

private:

	float speed;
	sf::Vector2f initPosition;
	sf::Vector2f initDirection;
};
