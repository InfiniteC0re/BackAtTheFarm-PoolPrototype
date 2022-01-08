#pragma once
#include <SFML/Graphics.hpp>

class Vectors
{
public:
	static float dot(const sf::Vector2f& lv, const sf::Vector2f& rv);
	static float length(const sf::Vector2f& source);
	static sf::Vector2f normalize(const sf::Vector2f& source);
};

