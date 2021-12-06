// AsteroidsGroupGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include "player.h"
#include "bullet.h"
#include "asteroid.h"

float getDistance(sf::Vector2f entity1, sf::Vector2f entity2) {
	float distance = sqrt(pow(entity1.x - entity2.x, 2) + pow(entity1.y - entity2.y, 2));
	return distance;
}

int main()
{

	int maxAsteroidCount = 15; //max asteroids on window 
	int score = 0; //initial score
	bool isAlive = true; //alive or dead at beginning of game


	std::vector<Bullet> activeBullets;
	std::vector<Asteroid*> activeAsteroids;

	//Game Window
	sf::RenderWindow window(sf::VideoMode(500, 500), "Group Assignment");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	sf::Clock deltaClock;
	double debounceTimer = 0.0f, lastClick = 0.0f, lastAsteroidSpawn = 0.0f;
	sf::Time dt = dt.Zero;

	//player texture, size, spawn position and initial speed
	Player* player = new Player("Assets/player2.png", 100.0f, 100.0f, 360.0f);
	player->setScale(1.12f, 1.12f);
	player->setPosition(250, 250);
	player->setSpeed(0, 0);


	//Text Font
	sf::Font font;
	if (!font.loadFromFile("Assets/Gameboy.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
	}

	sf::Text bannerText, scoreText, deathText;

	// select the font
	bannerText.setFont(font); // font is a sf::Font
	scoreText.setFont(font);
	deathText.setFont(font);

	// set the string to display
	bannerText.setString("BirdAttack!");
	scoreText.setString("Score : 0");
	deathText.setString("GAME OVER");

	// set the character size
	bannerText.setCharacterSize(20); // in pixels, not points!
	scoreText.setCharacterSize(12);
	deathText.setCharacterSize(20);

	//Set text colour
	bannerText.setFillColor(sf::Color(255, 255, 255));
	scoreText.setFillColor(sf::Color(255, 255, 255));
	deathText.setFillColor(sf::Color(255, 255, 255));

	//Set text origin
	bannerText.setOrigin(bannerText.getGlobalBounds().width / 2, 0);
	scoreText.setOrigin(scoreText.getGlobalBounds().width / 2, 0);
	deathText.setOrigin(deathText.getGlobalBounds().width / 2, deathText.getGlobalBounds().height / 2);

    //Set text position in window
	bannerText.setPosition(250, 0);
	scoreText.setPosition(250, bannerText.getGlobalBounds().height + 10);
	deathText.setPosition(250, 250);


	//Window open
	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}

		window.clear();


		if (isAlive) {
			//MOVEMENT OF CHARACTER
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if (debounceTimer - lastClick > 100) {
					sf::Vector2f playerDirection = player->getDirection();
					Bullet newBullet(player->m_entityPosition.x, player->m_entityPosition.y, playerDirection.x, playerDirection.y);
					activeBullets.push_back(newBullet);
					lastClick = debounceTimer;
				}
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				player->rotateBy(-player->m_rotationSpeed * dt.asSeconds());
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				player->rotateBy(player->m_rotationSpeed * dt.asSeconds());
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				player->m_movementSpeed = 100.0f;
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				player->m_movementSpeed = -100.0f;
			}

			else {
				player->m_movementSpeed = 75.0f;
			}


			//SPAWN ASTEROIDS IF LESS THAN MAX ALLOWED
			if (activeAsteroids.size() < maxAsteroidCount)
			{
				if (debounceTimer - lastAsteroidSpawn > 100) {
					sf::Vector2f spawnPosition(rand() % 800, rand() % 800);
					if (getDistance(player->m_entityPosition, spawnPosition) < 200.0f) {
						
					}
					else {
						sf::Vector2f spawnSpeed(rand() % 200 + (-100), rand() % 200 + (-100));
						Asteroid* newAsteroid = new Asteroid(int(rand() % 4), spawnPosition, spawnSpeed);
						activeAsteroids.push_back(newAsteroid);
						lastAsteroidSpawn = debounceTimer;
					}
				}
			}


			player->move(dt.asSeconds());
			window.draw(player->m_entitySprite);

			//DRAW BULLETS
			for (int i = 0; i < activeBullets.size(); i++)
			{
				activeBullets[i].move(dt.asSeconds());
				if (activeBullets[i].m_position.x < -100 || activeBullets[i].m_position.x > 600 || activeBullets[i].m_position.y < -100 || activeBullets[i].m_position.y > 600) {
					activeBullets.erase(activeBullets.begin() + i);

				}
				else {
					window.draw(activeBullets[i].m_shape);
				}
			}

			//DRAW ASTEROIDS
			for (int i = 0; i < activeAsteroids.size(); i++)
			{
				activeAsteroids[i]->move(dt.asSeconds());
				window.draw(activeAsteroids[i]->m_entitySprite);
			}

			//CHECK FOR BULLETS IF THEY HIT AN ASTEROID

			for (int i = 0; i < activeBullets.size(); i++)
			{
				for (int j = 0; j < activeAsteroids.size(); j++)
				{
					float distance = getDistance(activeBullets[i].m_position, activeAsteroids[j]->m_entityPosition);
					if (distance < activeAsteroids[j]->m_entitySprite.getGlobalBounds().width)
					{
						activeAsteroids.erase(activeAsteroids.begin() + j);
						activeBullets.erase(activeBullets.begin() + i);
						score += 10;
						break;
					}
				}
			}

			//CHECK FOR PLAYER DEATH
			for (int i = 0; i < activeAsteroids.size(); i++)
			{
				float distance = getDistance(player->m_entityPosition, activeAsteroids[i]->m_entityPosition);
				if (distance < activeAsteroids[i]->m_entitySprite.getGlobalBounds().width)
				{
					activeAsteroids.erase(activeAsteroids.begin() + i);
					delete player;
					isAlive = false;
					for (int j = 0; j < activeAsteroids.size(); j++)
					{
						activeAsteroids.erase(activeAsteroids.begin() + j);
					}
					break;
				}
			}
		}

		//Draw to window
		window.draw(bannerText);

		std::string scoreTextString = "Score : " + std::to_string(score);
		scoreText.setString(scoreTextString);
		scoreText.setOrigin(scoreText.getGlobalBounds().width / 2, 0);
		window.draw(scoreText);

		if (!isAlive) {
			window.draw(deathText);
		}

		window.display();
		debounceTimer += dt.asMilliseconds();
		dt = deltaClock.restart();
	}

	return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
