#pragma once
#include "Entities/EntityNode.h"

class UICueForce : public EntityNode
{
public:
	UICueForce();
	void DisplayStrength(float forceStep);
	virtual const char* getName() { return "UI_CueForce"; }

	int m_barWidth = 288;
	int m_barHeight = 15;
	int m_barWrapWidth = 330;
	int m_barWrapHeight = 20;
private:
	virtual void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_barWrap, states);
		target.draw(m_bar, states);
	};

	sf::Texture m_texture;
	sf::Sprite m_bar;
	sf::Sprite m_barWrap;
};

