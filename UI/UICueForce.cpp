#include "UICueForce.h"

UICueForce::UICueForce()
{
	m_texture.loadFromFile("Textures/Pool_Power_Bar.png");

	m_bar.setTexture(m_texture);
	m_bar.setOrigin(m_barWidth / 2, m_barHeight / 2);
	m_bar.setPosition(400, 385);

	m_barWrap.setTexture(m_texture);
	m_barWrap.setOrigin(m_barWrapWidth / 2, m_barWrapHeight / 2);
	m_barWrap.setPosition(400, 385);
	m_barWrap.setTextureRect(sf::IntRect(82, 21, m_barWrapWidth, m_barWrapHeight));
}

void UICueForce::DisplayStrength(float forceStep)
{
	m_isVisible = forceStep > -1;
	m_bar.setTextureRect(sf::IntRect(102, 64, m_barWidth * forceStep, 64));
}
