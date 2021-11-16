#pragma once

#include "SFML/Graphics.hpp"


#define MAX_NUM_OF_ITEMS 3

class Menu {

public:
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow &window);
	void draw(sf::RenderWindow &window, bool close);
	void MoveUp();
	void MoveDown();
	int getPressedItem();

private:
	int selectedItemIndex = 0;
	sf::Font font;
	sf::Text menu[MAX_NUM_OF_ITEMS];

};
