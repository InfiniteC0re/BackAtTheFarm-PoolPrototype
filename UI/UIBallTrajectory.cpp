#include "UIBallTrajectory.h"

UIBallTrajectory::UIBallTrajectory()
{
	m_texture.loadFromFile("Textures/Pool_Chalk.png");
	m_vertices.setPrimitiveType(sf::Quads);
	m_arrowTexture.loadFromFile("Textures/Pool_Chalk_Arrow_head.png");
	m_arrowVertices.setPrimitiveType(sf::Quads);
}

void UIBallTrajectory::Rebuild(float distance)
{
	if (distance <= 0)
	{
		m_isVisible = false;
		return;
	}
	else m_isVisible = true;

	int sizeOfTile = 20;
	int arrowOffset = 14;
	int countOfQuads = distance / sizeOfTile;

	setOrigin(-16, sizeOfTile / 2);
	m_vertices.resize(4 * countOfQuads);
	sf::Vector2u size = m_texture.getSize();

	int alpha = 180;
	sf::Color color = sf::Color::Color(123, 242, 123, alpha);
	sf::Color alphaColor = sf::Color::Color(123, 242, 123, 0);

	for (int i = 1; i <= countOfQuads; i++)
	{
		color = sf::Color::Color(123, 242, 123, alpha - 100 * ((float)i / countOfQuads));
		sf::Vertex* quad = &m_vertices[(i - 1) * 4];

		quad[0].position = sf::Vector2f(sizeOfTile * (i - 1), 0);
		quad[1].position = sf::Vector2f(sizeOfTile * i, 0);
		quad[2].position = sf::Vector2f(sizeOfTile * i, sizeOfTile);
		quad[3].position = sf::Vector2f(sizeOfTile * (i - 1), sizeOfTile);

		quad[0].texCoords = sf::Vector2f(0, 8);
		quad[1].texCoords = sf::Vector2f(0, size.y - 8);
		quad[2].texCoords = sf::Vector2f(size.x, size.y - 8);
		quad[3].texCoords = sf::Vector2f(size.x, 8);

		quad[0].color = color;
		quad[1].color = color;
		quad[2].color = color;
		quad[3].color = color;

		if (i == countOfQuads && (sizeOfTile * i - arrowOffset) >= distance - 60)
		{
			// make the end of quad semi-transparent
			quad[1].color = alphaColor;
			quad[2].color = alphaColor;	
		}
	}

	// make the arrow quad
	m_arrowVertices.resize(4);
	m_arrowVertices[0].position = sf::Vector2f(distance - arrowOffset, 0);
	m_arrowVertices[1].position = sf::Vector2f(distance + sizeOfTile - arrowOffset, 0);
	m_arrowVertices[2].position = sf::Vector2f(distance + sizeOfTile - arrowOffset, sizeOfTile);
	m_arrowVertices[3].position = sf::Vector2f(distance - arrowOffset, sizeOfTile);

	m_arrowVertices[0].texCoords = sf::Vector2f(0, size.y - 8);
	m_arrowVertices[1].texCoords = sf::Vector2f(0, 8);
	m_arrowVertices[2].texCoords = sf::Vector2f(size.x, 8);
	m_arrowVertices[3].texCoords = sf::Vector2f(size.x, size.y - 8);
	
	m_arrowVertices[0].color = color;
	m_arrowVertices[1].color = color;
	m_arrowVertices[2].color = color;
	m_arrowVertices[3].color = color;
}
