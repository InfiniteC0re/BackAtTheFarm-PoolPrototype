#include "WallEntity.h"

void WallEntity::OnDraw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(m_vertexes, state);
}

WallEntity::WallEntity(sf::Vector2f point1, sf::Vector2f point2, float depth = 0)
{
	m_depth = depth;
	m_startPoint = point1;
	m_endPoint = point2;

	m_vertexes = sf::VertexArray(sf::Lines, 2);
	m_vertexes[0].position = m_startPoint;
	m_vertexes[1].position = m_endPoint;
	m_vertexes[0].color = sf::Color::White;
	m_vertexes[1].color = sf::Color::White;

	g_pWallManager->AddWall(this);
}

sf::Vector2f WallEntity::ClosestPoint(sf::Vector2f point)
{
	sf::Vector2f vec1 = m_startPoint - point;
	sf::Vector2f vec2 = point - m_endPoint;
	sf::Vector2f wallUnit = Vectors::normalize(m_endPoint - m_startPoint);

	if (Vectors::dot(wallUnit, vec1) > 0)
		return vec1;
	
	if (Vectors::dot(wallUnit, vec2) > 0)
		return vec2 * -1.0f;

	float closestDist = Vectors::dot(wallUnit, vec1);
	sf::Vector2f closestVec = wallUnit * closestDist;

	return vec1 - closestVec;
}

void WallManager::AddWall(WallEntity* pWall)
{
	m_walls.push_back(pWall);
}

WallManager* g_pWallManager = new WallManager();