#pragma once
#define _USE_MATH_DEFINES
#include "Entities/WallEntity.h"
#include "Entities/BallEntity.h"
#include "Entities/HoleEntity.h"
#include "Helpers/Globals.h"
#include <cmath>

class Simulations
{
public:
	Simulations() {};
	static EntityNode* TraceLine(sf::Vector2f position, float angle, sf::Vector2f& hitPos, float radius);
	static float RandomFloat(float max);
	static void SimulateBallPhysics();
};

