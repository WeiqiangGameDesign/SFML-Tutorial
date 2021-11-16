#include <SFML/Graphics.hpp>
#include "Ball.h"
#include <iostream>


Ball::Ball(float radius, sf::Vector2f initLocation, sf::Vector2f ballVec)
{
	instance.setRadius(radius);
	instance.setPosition(initLocation.x, initLocation.y);
	instance.setFillColor(sf::Color::White);
	direction = ballVec;
	this->initPosition = initLocation;
	this->initDirection = direction;	

}

Ball::~Ball()
{
}

void Ball::setSpeed(float speed)
{
	this->speed = speed;
}


void Ball::move(float deltaTime)
{
	instance.setPosition(instance.getPosition() + direction * this->speed * deltaTime);
}

void Ball::reflect(float deltaY)
{
	direction = -direction;
	speed += 20.f;
	if (speed > 500.f) {
		speed -= 20.f;
	}
	direction.y += deltaY;
}

void Ball::reset()
{
	instance.setPosition(initPosition.x, initPosition.y);

	srand(time(NULL));
	//direction = initDirection;
	direction.x = -1;
	direction.y = (rand() % 21 - 10);
	direction.y /= 10.f;
	std::cout << "direction.y: " << direction.y << std::endl;
	speed = 360.f;
}

void Ball::restart()
{
	speed = 0.f;
	instance.setPosition(initPosition.x, initPosition.y);
	std::cout << initPosition.x << "," << initPosition.y << std::endl;
	srand(time(NULL));
	//direction = initDirection;
	direction.x = -1;
	direction.y = (rand() % 21 - 10);
	direction.y /= 10.f;
	std::cout << "direction.y: " << direction.y << std::endl;
}

sf::CircleShape Ball::getInstance()
{
	return instance;
}

sf::Vector2f Ball::getPosition()
{
	return instance.getPosition();
}

float Ball::getRadius()
{
	return instance.getRadius();
}
