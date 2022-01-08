#include "HoleEntity.h"

HoleEntity::HoleEntity(sf::Vector2f position)
{
	setPosition(position);
	m_circle.setRadius(m_fRadius);
	m_circle.setOrigin(m_circle.getRadius(), m_circle.getRadius());
	m_circle.setFillColor(sf::Color::Black);

	g_pHoleManager->m_holes.push_back(this);
}

HoleManager* g_pHoleManager = new HoleManager();