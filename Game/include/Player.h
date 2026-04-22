#pragma once
#include "Core/Component.h"
#include "InputModule.h"

class Player : public Component
{
public:
	void Update(const float _delta_time) override
	{
		Maths::Vector2<float> position = GetOwner()->GetPosition();

		if (InputModule::GetKey(sf::Keyboard::Key::D))
		{
			position.x += speed * _delta_time;
		}
		if (InputModule::GetKey(sf::Keyboard::Key::Q))
		{
			position.x -= speed * _delta_time;
		}

		if (InputModule::GetKey(sf::Keyboard::Key::Z))
		{
			position.y -= speed * _delta_time;
		}
		if (InputModule::GetKey(sf::Keyboard::Key::S))
		{
			position.y += speed * _delta_time;
		}

		GetOwner()->SetPosition(position);

		// Rotation
		Maths::Vector2f mousePos(
			(float)InputModule::GetMousePosition().x,
			(float)InputModule::GetMousePosition().y
		);

		Maths::Vector2f direction = mousePos - position;

		float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159265f;

		angle += 90.f;

		float spriteOffset = 180.f;
		GetOwner()->SetRotation(sf::degrees(angle + spriteOffset));

		if (InputModule::GetKeyDown(sf::Keyboard::Key::Escape))
		{
			Engine::GetInstance()->RequestQuit();
		}
	}

	float speed = 200.0f;
};
