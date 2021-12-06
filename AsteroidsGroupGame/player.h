#pragma once
#include <iostream>
#include "entity.h"
#include <cmath>


class Player : public Entity {
public:

	float m_health;
	float m_movementSpeed;
	float m_rotationSpeed;

	//Movement and Rotation speed of player
	Player(std::string textureImage, float health, float movementSpeed, float rotationSpeed) : Entity(textureImage) {
		m_health = health;
		m_movementSpeed = movementSpeed;
		m_rotationSpeed = rotationSpeed;
	}


	//Ensure proper positioning of player
	void move(float deltaTime) {
		m_entitySpeed.x = m_movementSpeed * sin(m_entityRotation * 0.0174533);
		m_entitySpeed.y = m_movementSpeed * -cos(m_entityRotation * 0.0174533);
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