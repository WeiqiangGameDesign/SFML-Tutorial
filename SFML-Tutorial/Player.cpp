#include "Player.h"
#include <iostream>

int Player::pointCount = 0;

Player::Player()
{
	name = "john";
	age = 18;
	pointCount++;
}

Player::Player(std::string defName)
{
	name = defName;
}

Player::~Player()
{
	std::cout << "~Player()" << std::endl;
}

void Player::setName(std::string newName)
{
	name = newName;
}

void Player::setAge(int newAge)
{
	age = newAge;
}

void Player::playerInfo()
{
	std::cout << "name:" << name << std::endl;
	std::cout << "age:" << age << std::endl;
	std::cout << "point:" << pointCount << std::endl;
}



/*
int main() {

	//Player p("Zoe");
	Player p;
	p.setName("Yasuo");
	p.setAge(19);
	p.playerInfo();

	return 0;
}
*/

