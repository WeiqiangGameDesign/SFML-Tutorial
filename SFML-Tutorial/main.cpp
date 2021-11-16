#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "CollisionDetectUtil.h"
#include "Menu.h"
#include "Paddle.h"
#include "Ball.h"
#include "PointCounter.h"




/*
is-a relationship
composition has-a <-> part-of

	Destructor
*/

//static CollisionDetectUtil colUtil;

enum States {
	MENU_STATE,
	PLAY_COMPUTER,
	PLAY_HUMAN,
	RESULT,
	QUIT
};

int main()
{
	int gameMode = MENU_STATE;
	// setup the window
	float winWidth = 2500.f;
	float winHeight = 1500.f;
	sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "SFML works!");
	//window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	// set pop sound
	sf::SoundBuffer popBuffer;
	if (!popBuffer.loadFromFile("./audios/pop.ogg")) {
		std::cout << "fail to load pop.ogg" << std::endl;
		return -1;
	}

	sf::Sound popSound;
	popSound.setBuffer(popBuffer);

	// set score sound
	sf::SoundBuffer scoreBuffer;
	if (!scoreBuffer.loadFromFile("./audios/score.ogg")) {
		std::cout << "fail to load score.ogg" << std::endl;
		return -1;
	}

	sf::Sound scoreSound;
	scoreSound.setBuffer(scoreBuffer);

	sf::SoundBuffer powerBuffer;
	if (!powerBuffer.loadFromFile("./audios/Powerup.wav")) {
		std::cout << "fail to load power.wav" << std::endl;
		return -1;
	}


	sf::Sound powerUpSound;
	powerUpSound.setBuffer(powerBuffer);

	int winner = 0;
	int firstTime = 0;
	// setup Menu
	Menu menu(window.getSize().x, window.getSize().y);
	bool closeMenu = false;

	// setup Clock
	sf::Clock clock;

	// setup result
	sf::Text resText;
	sf::Font resFont;
	if (!resFont.loadFromFile("./fonts/open-sans/OpenSans-Light.ttf")) {
		std::cout << "resfont load error" << std::endl;
	}
	resText.setFont(resFont);
	resText.setPosition(winWidth / 2 - 360.f, winHeight / 2);

	// setup objects
	/*
	sf::Texture bgTexture;
	if (!bgTexture.loadFromFile("./images/football.jpg")) {
		std::cout << "fail to load image football.jgp" << std::endl;
		return EXIT_FAILURE;
	}
	sf::Sprite sprite;
	sf::Vector2u size = bgTexture.getSize();
	sf::Vector2u winSize = window.getSize();
	float ScaleX = (float)winWidth / size.x;
	float ScaleY = (float)winHeight / size.y;     //Calculate scale.
	sprite.setTexture(bgTexture);
	sprite.setScale(ScaleX + 1, ScaleY + 1);
	sprite.setOrigin(size.x / 2, size.y / 2);
	*/


	// setup point counter
	PointCounter leftCounter(sf::Vector2f(winWidth / 2 - 300.f, 100.f));
	PointCounter rightCounter(sf::Vector2f(winWidth / 2 + 100.f, 100.f));


	bool ok = true;
	int lastMode = MENU_STATE;
	// setup ball 

	//sf::CircleShape ball(8.f);
	//ball.setPosition(winWidth / 2, winHeight / 2);
	//ball.setFillColor(sf::Color::White);
	//ball.setTexture(&ballTexture);
	float ballSpeed = 360.f;

	sf::Vector2f ballVec(1.f, .2f);

	sf::Vector2f initLocation(winWidth / 2.f, winHeight / 2.f);
	Ball ball(15.f, initLocation, ballVec);
	//ball.setSpeed(0.f);
	ball.setSpeed(360.f);

	// setup ball texture
	sf::Texture ballTexture;
	//ballTexture.setSmooth(true);
	//ballTexture.setRepeated(true);
	ballTexture.loadFromFile("./images/suntexture.jpg");
	ball.instance.setTexture(&ballTexture);

	// setup left player 
	float leftWidth = 12.f;
	float leftHeight = 240.f;
	Paddle leftPlayer(leftWidth, leftHeight, sf::Vector2f(50.f, winHeight / 2 - leftHeight / 2));
	leftPlayer.setFillColor(sf::Color::White);


	// setup middle line
	float midWidth = 6.f;
	float midHeight = winHeight;
	sf::RectangleShape midLine(sf::Vector2f(midWidth, midHeight));
	midLine.setFillColor(sf::Color::White);
	midLine.setPosition(sf::Vector2f(winWidth / 2.f - midLine.getSize().x / 2.f, 0));

	float midObstacleWidth = 24.f;
	float midObstacleHeight = 120.f;
	Paddle midObstacle(midObstacleWidth, midObstacleHeight, (sf::Vector2f(winWidth / 2 , 0)));
	midObstacle.setFillColor(sf::Color::Yellow);
	midObstacle.setPosition(sf::Vector2f(winWidth / 2.f - midObstacle.getSize().x / 2.5f, 0));


	// setup right player
	float rightWidth = 12.f;
	float rightHeight = 240.f;
	Paddle rightPlayer(rightWidth, rightHeight, sf::Vector2f(winWidth - 50.f, winHeight / 2 - rightHeight / 2));
	rightPlayer.setFillColor(sf::Color::White);


	Paddle powerUp(320.f, 120.f, sf::Vector2f(winWidth / 2.f + 150.f, 600.f));
	powerUp.setFillColor(sf::Color::Green);



	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::Resized) {

			}
			if (event.type == sf::Event::KeyPressed) {
				if (gameMode == MENU_STATE) {
					switch (event.key.code)
					{
					case sf::Keyboard::Up:
					case sf::Keyboard::W:
						menu.MoveUp();
						break;
					case sf::Keyboard::Down:
					case sf::Keyboard::S:
						menu.MoveDown();
						break;
					case sf::Keyboard::Return:
					case sf::Keyboard::Space:
						switch (menu.getPressedItem())
						{
						case 0:
							std::cout << "Play COMPUTER pressed" << std::endl;
							closeMenu = true;
							lastMode = MENU_STATE;
							gameMode = PLAY_COMPUTER;
							break;
						case 1:
							std::cout << "Play Human" << std::endl;
							closeMenu = true;
							lastMode = MENU_STATE;
							gameMode = PLAY_HUMAN;
							break;
						case 2:
							window.close();
							break;
						}
						break;
					default:
						break;
					}
				}
			}
		}

		// window scale set up
		sf::View view;
		auto windowSize = window.getSize();
		view.reset(sf::FloatRect(0.f, 0.f, windowSize.x, windowSize.y));
		window.setView(view);

		if (gameMode == MENU_STATE) {
			/*
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
					menu.MoveUp();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
					menu.MoveDown();
				}
			*/
			//std::cout << "game is not started" << std::endl;
			firstTime = 0;
		}
		else if (gameMode == PLAY_COMPUTER) {

			// reset mid line & left & right
			midLine.setPosition(sf::Vector2f(window.getSize().x / 2, 0));

			if (firstTime == 0) {
				clock.restart();
				firstTime++;
			}
			float delta_s = clock.getElapsedTime().asSeconds();
			clock.restart();
			ball.move(delta_s);
			//std::cout << "ball is moving" << std::endl;

			auto ballPosition = ball.getPosition();
			/*

				// ball position & movement
				//std::cout << delta_s << std::endl;

				ballPosition += ballVec * ballSpeed * delta_s;

				ball.setPosition(ballPosition);

			*/

			//bool isCollided = colUtil.isBoxCirlcleIntersected(leftPlayer, ball);
			bool isCollidedLeft = CollisionDetectUtil::isBoxCirlcleIntersected(leftPlayer.getInstance(), ball.getInstance());
			bool isCollidedRight = CollisionDetectUtil::isBoxCirlcleIntersected(rightPlayer.getInstance(), ball.getInstance());
			bool isCollidedMidObstacle = CollisionDetectUtil::isBoxCirlcleIntersected(midObstacle.getInstance(), ball.getInstance());
			bool isCollidedPowerUp = CollisionDetectUtil::isBoxCirlcleIntersected(powerUp.getInstance(), ball.getInstance());
			if (isCollidedLeft) {
				std::cout << "CollidedLeft!" << std::endl;
				ball.reflect(delta_s);
				ball.lastTouch = 1;
				popSound.play();
				//ball.direction.x = -ball.direction.x * 1.1f;
				float tmp = ball.getPosition().y - leftPlayer.getMidPoint();
				//std::cout << "tmp" << tmp << std::endl;
				if (tmp > 0) {
					ball.direction.y += tmp * 0.01f;
				}
				else {
					ball.direction.y += tmp * 0.01f;
				}
				isCollidedLeft = false;
			}
			else if (isCollidedRight) {
				std::cout << "CollidedRight!" << std::endl;
				//ball.direction.x = -ball.direction.x * 1.1f;
				ball.reflect(delta_s);
				ball.lastTouch = 2;
				popSound.play();
				float tmp = ball.getPosition().y - rightPlayer.getMidPoint();
				//std::cout << "tmp" << tmp << std::endl;
				if (tmp > 0) {
					ball.direction.y += tmp * 0.01f;
				}
				else {
					ball.direction.y += tmp * 0.01f;
				}
				isCollidedRight = false;
			}
			else if (isCollidedMidObstacle) {
				std::cout << "CollidedMidObstacle!" << std::endl;
				//ball.direction.x = -ball.direction.x * 1.1f;
				ball.direction.x = -ball.direction.x;
				popSound.play();
				isCollidedMidObstacle = false;
			}
			else if (isCollidedPowerUp) {
				if (ball.lastTouch == 1) {
					leftPlayer.powerUp(ok);
					if(ok)
						powerUpSound.play();
					powerUp.setFillColor(sf::Color::Black);
					ok = false;
				}
				else if (ball.lastTouch == 2) {
					rightPlayer.powerUp(ok);
					if(ok)
						powerUpSound.play();
					powerUp.setFillColor(sf::Color::Black);
					ok = false;
				}
			}


			if (ballPosition.x > window.getSize().x - ball.getRadius() / 2) {
				std::cout << "bounce2Left!" << std::endl;
				//ball.direction.x = -ball.direction.x;
				leftCounter.AddPoint();
				scoreSound.play();
				midObstacle.instance.setPosition(sf::Vector2f(midObstacle.instance.getPosition().x, 0));
				if (leftCounter.getPoints() == 5) {
					winner = 0;
					lastMode = PLAY_COMPUTER;
					gameMode = RESULT;
					ball.restart();
					leftCounter.restart();
					rightCounter.restart();
				}
				ball.reset();
			}
			else if (ballPosition.x < ball.getRadius() / 2) {
				std::cout << "bounce2Right!" << std::endl;
				//ball.direction.x = -ball.direction.x;
				rightCounter.AddPoint();
				scoreSound.play();
				midObstacle.instance.setPosition(sf::Vector2f(midObstacle.instance.getPosition().x, 0));
				//std::cout << rightCounter.getPoints() << std::endl;
				if (rightCounter.getPoints() == 5) {
					winner = 1;
					lastMode = PLAY_COMPUTER;
					gameMode = RESULT;
					ball.restart();
					leftCounter.restart();
					rightCounter.restart();
				}
				ball.reset();
			}
			else if (ballPosition.y < ball.getRadius() / 2) {
				std::cout << "bounce2Top!" << std::endl;
				ball.direction.y = -ball.direction.y;
				popSound.play();
			}
			else if (ballPosition.y > window.getSize().y - ball.getRadius() / 2) {
				std::cout << "bounce2Bottom!" << std::endl;
				ball.direction.y = -ball.direction.y;
				popSound.play();
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				auto position = leftPlayer.getPosition();
				leftPlayer.move(0.f, -8.f);
				if (leftPlayer.getPosition().y < 0.f) {
					leftPlayer.move(0.f, 8.f);
					std::cout << "stop!" << std::endl;
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				auto position = leftPlayer.getPosition();
				leftPlayer.move(0.f, 8.f);
				if (leftPlayer.getPosition().y > winHeight - leftPlayer.getSize().y) {
					leftPlayer.move(0.f, -8.f);
				}
			}

			if (delta_s > 0) {
				rightPlayer.setBoundry(0, winHeight);
				rightPlayer.AIControl(ball);
				// mid Obstacle
				midObstacle.setBoundry(0, winHeight);
				midObstacle.regularMove(delta_s);
			}

			/*
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				auto position = rightPlayer.getPosition();
				rightPlayer.move(0.f, -8.f);
				if (rightPlayer.getPosition().y < 0.f) {
					rightPlayer.move(0.f, 8.f);
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				auto position = rightPlayer.getPosition();
				rightPlayer.move(0.f, 8.f);
				if (rightPlayer.getPosition().y > winHeight - rightPlayer.getSize().y) {
					rightPlayer.move(0.f, -8.f);
				}
			}
			*/


			/*
			sf::Clock clock;

			sf::Time elapsed1 = clock.getElapsedTime();
			std::cout << elapsed1.asMilliseconds() << std::endl;
			clock.restart();

			sf::Time elapsed2 = clock.getElapsedTime();
			std::cout << elapsed2.asMicroseconds() << std::endl;

			*/

			window.clear();
			window.draw(midLine);
			window.draw(midObstacle.getInstance());
			leftCounter.draw(window);
			rightCounter.draw(window);
			window.draw(leftPlayer.getInstance());
			window.draw(rightPlayer.getInstance());
			window.draw(powerUp.getInstance());
			window.draw(ball.getInstance());

		}
		else if (gameMode == PLAY_HUMAN) {

			// reset mid line & left & right
			midLine.setPosition(sf::Vector2f(window.getSize().x / 2, 0));

			if (firstTime == 0) {
				clock.restart();
				firstTime++;
			}
			float delta_s = clock.getElapsedTime().asSeconds();
			clock.restart();
			ball.move(delta_s);
			//std::cout << "ball is moving" << std::endl;

			auto ballPosition = ball.getPosition();
			/*

				// ball position & movement
				//std::cout << delta_s << std::endl;

				ballPosition += ballVec * ballSpeed * delta_s;

				ball.setPosition(ballPosition);

			*/

			//bool isCollided = colUtil.isBoxCirlcleIntersected(leftPlayer, ball);
			bool isCollidedLeft = CollisionDetectUtil::isBoxCirlcleIntersected(leftPlayer.getInstance(), ball.getInstance());
			bool isCollidedRight = CollisionDetectUtil::isBoxCirlcleIntersected(rightPlayer.getInstance(), ball.getInstance());
			bool isCollidedMidObstacle = CollisionDetectUtil::isBoxCirlcleIntersected(midObstacle.getInstance(), ball.getInstance());
			bool isCollidedPowerUp = CollisionDetectUtil::isBoxCirlcleIntersected(powerUp.getInstance(), ball.getInstance());
			if (isCollidedLeft) {
				std::cout << "CollidedLeft!" << std::endl;
				ball.reflect(delta_s);
				ball.lastTouch = 1;
				popSound.play();
				//ball.direction.x = -ball.direction.x * 1.1f;
				float tmp = ball.getPosition().y - leftPlayer.getMidPoint();
				//std::cout << "tmp" << tmp << std::endl;
				if (tmp > 0) {
					ball.direction.y += tmp * 0.01f;
				}
				else {
					ball.direction.y += tmp * 0.01f;
				}
				isCollidedLeft = false;
			}
			else if (isCollidedRight) {
				std::cout << "CollidedRight!" << std::endl;
				//ball.direction.x = -ball.direction.x * 1.1f;
				ball.reflect(delta_s);
				ball.lastTouch = 2;
				popSound.play();
				float tmp = ball.getPosition().y - rightPlayer.getMidPoint();
				//std::cout << "tmp" << tmp << std::endl;
				if (tmp > 0) {
					ball.direction.y += tmp * 0.01f;
				}
				else {
					ball.direction.y += tmp * 0.01f;
				}
				isCollidedRight = false;
			}
			else if (isCollidedMidObstacle) {
				std::cout << "CollidedMidObstacle!" << std::endl;
				//ball.direction.x = -ball.direction.x * 1.1f;
				ball.direction.x = -ball.direction.x;
				popSound.play();
				isCollidedMidObstacle = false;
			}
			else if (isCollidedPowerUp) {
				if (ball.lastTouch == 1) {
					leftPlayer.powerUp(ok);
					if(ok)
						powerUpSound.play();
					powerUp.setFillColor(sf::Color::Black);
					ok = false;
				}
				else if (ball.lastTouch == 2) {
					rightPlayer.powerUp(ok);
					if(ok)
						powerUpSound.play();
					powerUp.setFillColor(sf::Color::Black);
					ok = false;
				}
			}


			if (ballPosition.x > window.getSize().x - ball.getRadius() / 2) {
				std::cout << "bounce2Left!" << std::endl;
				//ball.direction.x = -ball.direction.x;
				leftCounter.AddPoint();
				scoreSound.play();
				midObstacle.instance.setPosition(sf::Vector2f(midObstacle.instance.getPosition().x, 0));
				if (leftCounter.getPoints() == 5) {
					winner = 0;
					lastMode = PLAY_HUMAN;
					gameMode = RESULT;
					ball.restart();
					leftCounter.restart();
					rightCounter.restart();
				}
				ball.reset();
			}
			else if (ballPosition.x < ball.getRadius() / 2) {
				std::cout << "bounce2Right!" << std::endl;
				//ball.direction.x = -ball.direction.x;
				rightCounter.AddPoint();
				scoreSound.play();
				midObstacle.instance.setPosition(sf::Vector2f(midObstacle.instance.getPosition().x, 0));
				//std::cout << rightCounter.getPoints() << std::endl;
				if (rightCounter.getPoints() == 5) {
					winner = 1;
					lastMode = PLAY_HUMAN;
					gameMode = RESULT;
					ball.restart();
					leftCounter.restart();
					rightCounter.restart();
				}
				ball.reset();
			}
			else if (ballPosition.y < ball.getRadius() / 2) {
				std::cout << "bounce2Top!" << std::endl;
				ball.direction.y = -ball.direction.y;
				popSound.play();
			}
			else if (ballPosition.y > window.getSize().y - ball.getRadius() / 2) {
				std::cout << "bounce2Bottom!" << std::endl;
				ball.direction.y = -ball.direction.y;
				popSound.play();
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				auto position = leftPlayer.getPosition();
				leftPlayer.move(0.f, -8.f);
				if (leftPlayer.getPosition().y < 0.f) {
					leftPlayer.move(0.f, 8.f);
					std::cout << "stop!" << std::endl;
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				auto position = leftPlayer.getPosition();
				leftPlayer.move(0.f, 8.f);
				if (leftPlayer.getPosition().y > winHeight - leftPlayer.getSize().y) {
					leftPlayer.move(0.f, -8.f);
				}
			}

			if (delta_s > 0) {
				rightPlayer.setBoundry(0, winHeight);
				//rightPlayer.AIControl(ball);
				// mid Obstacle
				midObstacle.setBoundry(0, winHeight);
				midObstacle.regularMove(delta_s);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				auto position = rightPlayer.getPosition();
				rightPlayer.move(0.f, -8.f);
				if (rightPlayer.getPosition().y < 0.f) {
					rightPlayer.move(0.f, 8.f);
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				auto position = rightPlayer.getPosition();
				rightPlayer.move(0.f, 8.f);
				if (rightPlayer.getPosition().y > winHeight - rightPlayer.getSize().y) {
					rightPlayer.move(0.f, -8.f);
				}
			}



			/*
			sf::Clock clock;

			sf::Time elapsed1 = clock.getElapsedTime();
			std::cout << elapsed1.asMilliseconds() << std::endl;
			clock.restart();

			sf::Time elapsed2 = clock.getElapsedTime();
			std::cout << elapsed2.asMicroseconds() << std::endl;

			*/

			window.clear();
			window.draw(midLine);
			window.draw(midObstacle.getInstance());
			leftCounter.draw(window);
			rightCounter.draw(window);
			window.draw(leftPlayer.getInstance());
			window.draw(rightPlayer.getInstance());
			window.draw(powerUp.getInstance());
			window.draw(ball.getInstance());

		}
		else if (gameMode == RESULT) {
			std::cout << "Result!" << std::endl;
			window.clear();
			if (winner == 0) {
				resText.setString("Left Player Won ! Press SPACE Play Again!");
				resText.setCharacterSize(50.f);
				window.draw(resText);
			}
			else if (winner == 1) {
				resText.setString("Right Player Won ! Press SPACE Play Again!");
				resText.setCharacterSize(50.f);
				window.draw(resText);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				if (lastMode == PLAY_COMPUTER)
					gameMode = PLAY_COMPUTER;
				else if (lastMode == PLAY_HUMAN)
					gameMode = PLAY_HUMAN;
				ok = true;
				powerUp.setFillColor(sf::Color::Green);
				leftPlayer.resize(leftWidth, leftHeight);
				rightPlayer.resize(rightWidth, rightHeight);
				ball.reset();
				clock.restart();
			}

		}


		//window.draw(sprite);
		menu.draw(window, closeMenu);
		//window.draw
		window.display();
	}

	return 0;
}

