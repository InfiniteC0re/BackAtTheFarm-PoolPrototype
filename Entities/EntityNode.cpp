#include "EntityNode.h"

void EntityNode::addNode(EntityNode* pNode)
{
	m_children.push_back(pNode);
}

void EntityNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform = getTransform() * states.transform;
	if (m_isVisible) OnDraw(target, states);

	for (std::size_t i = 0; i < m_children.size(); i++)
	{
		m_children[i]->PreUpdate();
		m_children[i]->draw(target, states);
		m_children[i]->Update();
	}
}

