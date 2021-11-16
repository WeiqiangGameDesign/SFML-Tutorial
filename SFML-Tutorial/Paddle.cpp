#include "Paddle.h"
#include <iostream>


Paddle::Paddle(float width, float height, sf::Vector2f position)
{
	sf::RectangleShape tmp(sf::Vector2f(width, height));
	instance = tmp;
	instance.setPosition(position);
}

void Paddle::setFillColor(sf::Color color)
{
	instance.setFillColor(color);
}

void Paddle::setTexture(sf::Texture texture)
{
	instance.setTexture(&texture);
}

void Paddle::resize(float width, float height)
{
	this->width = width;
	this->height = height;
	sf::Vector2f newSize(width, height);
	instance.setSize(newSize);
}


sf::Vector2f Paddle::getPosition()
{
	return position;
}

void Paddle::setPosition(sf::Vector2f newPosition)
{
	this->position = newPosition;
	instance.setPosition(newPosition);
}

void Paddle::move(sf::Vector2f newPosition)
{
	position = instance.getPosition();
	instance.move(newPosition);
}

void Paddle::move(float x, float y)
{
	position = instance.getPosition();
	instance.move(x, y);
}

sf::Vector2f Paddle::getSize()
{
	return instance.getSize();
}

sf::RectangleShape Paddle::getInstance()
{
	return instance;
}

float Paddle::getMidPoint()
{
	float res = instance.getPosition().y + instance.getSize().y / 2;
	//std::cout << "res: " << res << std::endl;
	midPoint = res;
	return res;
}

void Paddle::AIControl(Ball ball)
{
	//std::cout << ball.getPosition().y << std::endl;
	//std::cout << getMidPoint() << std::endl;
	if (ball.getPosition().y > getMidPoint() + 80.f) {
		//std::cout << "y >" << std::endl;
		move(0.f, 3.f);
		if (instance.getPosition().y < upBoundry + instance.getSize().y) {
			move(0.f, 3.f);
		}
	}
	else if(ball.getPosition().y < getMidPoint() - 80.f){
		//std::cout << "y <" << std::endl;
		move(0.f, -3.f);
		if (instance.getPosition().y > downBoundry - instance.getSize().y) {
			move(0.f, -3.f);
		}
	}
	else {

	}
}

void Paddle::regularMove(float deltaTime)
{
	//std::cout << "regularMoving"<< std::endl;

	//std::cout << "regularMoving" << instance.getPosition().y << std::endl;
	instance.setPosition(instance.getPosition() + direction * this->speed * deltaTime);
	if (instance.getPosition().y <= 0) {
		direction.y = 1;
	}
	else if(instance.getPosition().y >= downBoundry - instance.getSize().y){

		std::cout << downBoundry << std::endl;
		std::cout << instance.getSize().y << std::endl;
		//std::cout << instance.getPosition().y << "," << downBoundry - instance.getSize().y << std::endl;
		direction.y = -1;
	}
}

void Paddle::powerUp(bool ok)
{
	if (ok)
		resize(instance.getSize().x, 360.f);
}




void Paddle::setBoundry(float up, float down)
{
	//std::cout << up << "," << downBoundry << std::endl;
	upBoundry = up;
	downBoundry = down;
}



