#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class BaseManager
{
public:
	virtual bool IsCorrect(sf::Event::EventType& eventType) const;
	virtual bool Process(sf::Event& event) = 0;
};

class EventManager
{
public:
	bool Process(sf::Event& event)
	{
		for (size_t i = 0; i < m_managers.size(); i++)
		{
			if (m_managers[i]->IsCorrect(event.type))
				return m_managers[i]->Process(event);
		}

		return false;
	}

	void Attach(BaseManager* pManager)
	{
		m_managers.push_back(pManager);
	}
private:
	std::vector<BaseManager*> m_managers;
};
