#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>

class Entity
{

public:
	sf::Texture m_entityTexture;
	sf::Sprite m_entitySprite;
	sf::Vector2f m_entityPosition;
	sf::Vector2f m_entityScale;
	sf::Vector2f m_entitySpeed;
	float m_entityRotation;

	//Get texture for entity
	Entity(std::string textureImage) {
		sf::Texture entityTexture;
		if (!entityTexture.loadFromFile(textureImage)) {
			
		}
		else {
			m_entityTexture = entityTexture;
			m_entitySprite.setTexture(m_entityTexture);
			m_entitySprite.setOrigin(m_entityTexture.getSize().x / 2, m_entityTexture.getSize().y / 2);
			m_entityPosition, m_entitySpeed = sf::Vector2f(0.0f, 0.0f);
			m_entityScale = sf::Vector2f(1.0f, 1.0f);;
			m_entityRotation = 0.0f;
		}
	}

	~Entity() {
		//delete current object from array of entities
	}

	sf::Vector2f getScale() {
		return m_entityScale;
	}

	void setScale(float scaleX, float scaleY) {
		m_entityScale = sf::Vector2f(scaleX, scaleY);
		m_entitySprite.setScale(m_entityScale);
	}

	sf::Vector2f getPosition() {
		return m_entityPosition;
	}

	void setPosition(float positionX, float positionY) {
		m_entityPosition = sf::Vector2f(positionX, positionY);
		m_entitySprite.setPosition(m_entityPosition);
	}

	float getRotation() {
		return m_entityRotation;
	}

	void setRotation(float angle) {
		m_entityRotation = angle;
		m_entitySprite.setRotation(m_entityRotation);
	}

	void rotateBy(float degrees) {
		m_entityRotation += degrees;
		if (m_entityRotation > 360) {
			m_entityRotation -= 360;
		}
		else if (m_entityRotation < 0) {
			m_entityRotation += 360;
		}
		m_entitySprite.setRotation(m_entityRotation);

	}

	void updatePosition() {
		m_entitySprite.setPosition(m_entityPosition);
	}

	//Speed of asteroid
	sf::Vector2f getSpeed() {
		return m_entitySpeed;
	}

	//Direction of asteroid
	sf::Vector2f getDirection() {
		float mag = sqrt(pow(sin(m_entityRotation * 0.0174533), 2) + pow(-cos(m_entityRotation * 0.0174533), 2));
		return sf::Vector2f(sin(m_entityRotation * 0.0174533) / mag, -cos(m_entityRotation * 0.0174533) / mag);
	}

	//X and Y speed of asteroid
	void setSpeed(float speedX, float speedY) {
		m_entitySpeed.x = speedX;
		m_entitySpeed.y = speedY;
	}

	//Ensuring proper position of entity
	void move(float deltaTime) {
		m_entityPosition.x += m_entitySpeed.x * deltaTime;
		m_entityPosition.y += m_entitySpeed.y * deltaTime;
		if (m_entityPosition.x < 0) {
			m_entityPosition.x = 500;
		}
		if (m_entityPosition.x > 500) {
			m_entityPosition.x = 0;
		}
		if (m_entityPosition.y < 0) {
			m_entityPosition.y = 500;
		}
		if (m_entityPosition.y > 500) {
			m_entityPosition.y = 0;
		}
		updatePosition();
	}
};