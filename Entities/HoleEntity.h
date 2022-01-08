#pragma once
#include "Entities/EntityNode.h"

class HoleEntity : public EntityNode
{
public:
	virtual const char* getName() { return "HoleEntity"; }
	HoleEntity(sf::Vector2f position);
	sf::CircleShape m_circle;
	float m_fRadius = 14;
	float m_fHalfRadius = m_fRadius / 7;

private:
	virtual void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_circle, states);
	};
};

class HoleManager
{
public:
	HoleManager() {};
	std::vector<HoleEntity*> m_holes;
};

extern class HoleManager* g_pHoleManager;