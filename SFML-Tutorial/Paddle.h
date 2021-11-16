#pragma once
#include "SFML/Graphics.hpp"
#include "Ball.h"


class Paddle {

public:

	Paddle(float width, float height, sf::Vector2f position);

	void setFillColor(sf::Color color);

	void setTexture(sf::Texture texture);

	void resize(float width, float height);

	sf::Vector2f getPosition();

	void setPosition(sf::Vector2f newPosition);

	void move(sf::Vector2f newPosition);

	void move(float x, float y);

	sf::Vector2f getSize();

	sf::RectangleShape getInstance();

	float getMidPoint();

	void AIControl(Ball ball);

	void setBoundry(float up, float down);

	sf::RectangleShape instance;

	void regularMove(float deltaTime);

	float speed = 80.f;

	sf::Vector2f direction = sf::Vector2f(0, 1);

	void powerUp(bool ok);


private:

	float width;
	float height;
	float midPoint;

	float upBoundry;
	float downBoundry;


	sf::Vector2f position;


};
