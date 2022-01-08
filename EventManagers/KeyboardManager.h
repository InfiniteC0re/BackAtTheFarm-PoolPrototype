#pragma once
#define _USE_MATH_DEFINES
#include "EventManagers/BaseManager.h"
#include "Entities/BallEntity.h"
#include "Helpers/Simulations.h"
#include <math.h>

#define degreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)
#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / M_PI)

class KeyboardManager : public BaseManager
{
public:
	bool keyboardMap[255];

	KeyboardManager()
	{
		for (int i = 0; i < sizeof(keyboardMap); i++)
			keyboardMap[i] = false;
	};

	void SetButtonHold(sf::Event& event)
	{
		keyboardMap[event.key.code] = event.type == sf::Event::EventType::KeyPressed;
	}

	bool GetButtonHold(sf::Event& event)
	{
		return keyboardMap[event.key.code];
	}

	virtual bool IsCorrect(sf::Event::EventType& eventType) const
	{
		return eventType == sf::Event::EventType::KeyPressed || eventType == sf::Event::EventType::KeyReleased;
	};

	virtual bool Process(sf::Event& event)
	{
		bool processed = false;
		bool isButtonHold = GetButtonHold(event);
		BallEntity* pPlayer = g_pBallManager->m_pPlayer;
		CueEntity* pCue = pPlayer->m_pCue;
		float& rotation = pCue->m_rotation;
		float rotationSpeed = 0;
		sf::Vector2f newVel = sf::Vector2f();

		switch (event.key.code)
		{
		case sf::Keyboard::Space:
			if (!isButtonHold) Simulations::SimulateBallPhysics();
			break;
		case sf::Keyboard::Enter:
		case sf::Keyboard::W:
		{
			if (!isButtonHold && pCue->m_cueState == CueEntity::CUESTATE::PLACING)
				pCue->m_cueState = CueEntity::CUESTATE::PREPARING;
			else if (!isButtonHold && pCue->m_cueState == CueEntity::CUESTATE::PREPARING)
			{
				//float force = pCue->GetForce();
				float force = G_CUE_MAXFORCE;
				newVel = sf::Vector2f(cos(degreesToRadians(rotation)) * force, sin(degreesToRadians(rotation)) * force);
				pPlayer->m_velocity = -newVel;
				g_pBallManager->m_allStopped = false;

				pCue->m_cueState = CueEntity::CUESTATE::MOVING;
				pCue->ResetCueLook();
				processed = true;
			}
		}
		break;
		case sf::Keyboard::A:
		case sf::Keyboard::D:
			if (event.key.code == sf::Keyboard::A && event.type == event.KeyPressed)
				rotationSpeed = 0.5;
			else if (event.type == event.KeyPressed)
				rotationSpeed = -0.5;
			else
				rotationSpeed = 0;
			break;
		}

		if (pCue != nullptr) pCue->SetRotationSpeed(rotationSpeed);
		SetButtonHold(event);
		return processed;
	};
};