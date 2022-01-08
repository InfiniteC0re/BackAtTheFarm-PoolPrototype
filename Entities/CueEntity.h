#pragma once
#include "Entities/EntityNode.h"
#include "Helpers/Globals.h"
#include "UI/UICueForce.h"

class CueEntity : public EntityNode
{
public:
	enum class CUESTATE
	{
		MOVING,
		PLACING,
		PREPARING
	};

	virtual const char* getName() { return "CueEntity"; }
	
	CueEntity();
	float m_forceStep = 0;
	float m_forceStepDir = 1;
	float m_force = G_CUE_MINFORCE;
	float m_rotation = 180;
	float m_rotationSpeed = 0;
	CUESTATE m_cueState = CUESTATE::PLACING;
	UICueForce* m_pUIElem = 0x0;
	sf::RectangleShape m_cue;

	// functions
	float GetForce();
	void SetRotationSpeed(float rotationSpeed);
	void AttachUIElement(UICueForce* pUIElem);
	void ResetCueLook();

private:
	virtual void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void PreUpdate();
};

