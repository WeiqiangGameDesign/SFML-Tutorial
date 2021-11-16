#pragma once
#include <string>


class Player {

private:
	std::string name;
	int age;
	static int pointCount;

public:
	Player();

	Player(std::string defName);

	~Player();

	void setName(std::string newName);
	void setAge(int newAge);
	void playerInfo();

};
