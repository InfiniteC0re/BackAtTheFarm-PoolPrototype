#pragma once
#include "Entities/EntityNode.h"
#include "Entities/ContainerEntity.h"

class UIBallTrajectory : public EntityNode
{
public:
	UIBallTrajectory();
	void Rebuild(float distance);
	virtual const char* getName() { return "UI_BallTrajectory"; }
	float* m_rotation = 0x0;

private:
	virtual void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.texture = &m_texture;
		target.draw(m_vertices, states);
		states.texture = &m_arrowTexture;
		target.draw(m_arrowVertices, states);
	};

	virtual void PreUpdate()
	{
		setRotation(180 + *m_rotation);
	}

	sf::VertexArray m_vertices;
	sf::VertexArray m_arrowVertices;
	sf::Texture m_texture;
	sf::Texture m_arrowTexture;
};

