#include "Vectors.h"

float Vectors::dot(const sf::Vector2f& lv, const sf::Vector2f& rv)
{
	return lv.x * rv.x + lv.y * rv.y;
}

float Vectors::length(const sf::Vector2f& source)
{
	return std::sqrt(dot(source, source));
}

sf::Vector2f Vectors::normalize(const sf::Vector2f& source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));

	if (length != 0)
		return sf::Vector2f(source.x / length, source.y / length);
	else
		return source;
}
