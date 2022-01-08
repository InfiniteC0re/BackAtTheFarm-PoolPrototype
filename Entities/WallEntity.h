#pragma once
#include "Entities/EntityNode.h"
#include "Helpers/Vectors.h"

class WallEntity : public EntityNode
{
public:
	virtual const char* getName() { return "WallEntity"; }
	sf::Vector2f ClosestPoint(sf::Vector2f point);

private:
	virtual void OnDraw(sf::RenderTarget& target, sf::RenderStates state) const;

public:
	WallEntity(sf::Vector2f point1, sf::Vector2f point2, float depth);
	sf::Vector2f m_startPoint;
	sf::Vector2f m_endPoint;
	sf::VertexArray m_vertexes;
	float m_depth;
};

class WallManager
{
public:
	WallManager() {};
	void AddWall(WallEntity* pWall);
	std::vector<WallEntity*> m_walls;
};

extern class WallManager* g_pWallManager;

