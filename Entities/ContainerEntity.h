#pragma once
#include "Entities/EntityNode.h"

class ContainerEntity : public EntityNode
{
public:
	virtual const char* getName() { return "Container"; }
private:
	virtual void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const {};
};

