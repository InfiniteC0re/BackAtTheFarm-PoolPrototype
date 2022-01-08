#include "CueEntity.h"

CueEntity::CueEntity()
{
	m_cue = sf::RectangleShape(sf::Vector2f(G_CUE_WIDTH, 4));
	m_cue.setFillColor(sf::Color::White);
	m_cue.setOrigin(-G_CUE_MINDISTANCE, 2);
}

float CueEntity::GetForce()
{
	return G_CUE_MINFORCE + ((G_CUE_MAXFORCE - G_CUE_MINFORCE) * m_forceStep);
}

void CueEntity::SetRotationSpeed(float rotationSpeed)
{
	if (m_cueState != CUESTATE::PLACING)
	{
		m_rotationSpeed = 0;
		return;
	};

	m_rotationSpeed = rotationSpeed;
}

void CueEntity::AttachUIElement(UICueForce* pUIElem)
{
	m_pUIElem = pUIElem;
	ResetCueLook();
}

void CueEntity::ResetCueLook()
{
	m_forceStep = 0;
	m_forceStepDir = 1;
	m_pUIElem->DisplayStrength(-1);
	m_cue.setOrigin(-G_CUE_MINDISTANCE, m_cue.getOrigin().y);
}

void CueEntity::OnDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.rotate(m_rotation);
	target.draw(m_cue, states);
}
void CueEntity::PreUpdate()
{
	if (m_cueState == CUESTATE::PREPARING)
	{
		m_forceStep += G_CUE_FORCE_STEP_SIZE * m_forceStepDir;

		if (m_forceStep <= 0 || m_forceStep >= 1.0)
			m_forceStepDir *= -1;

		if (m_pUIElem != 0x0)
			m_pUIElem->DisplayStrength(m_forceStep);

		m_cue.setOrigin(-m_forceStep * G_CUE_MAXDISTANCE - G_CUE_MINDISTANCE, m_cue.getOrigin().y);
	}
}
