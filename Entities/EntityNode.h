#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class EntityNode : public sf::Drawable, public sf::Transformable
{
public:
	virtual const char* getName() { return "EntityNode"; }
	void addNode(EntityNode* pNode);

	bool m_isVisible = true;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	virtual void PreUpdate() {};
	virtual void Update() {};
	
	std::vector<EntityNode*> m_children;
};

