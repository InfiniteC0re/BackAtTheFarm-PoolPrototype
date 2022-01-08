#pragma once
#include <SFML/Graphics.hpp>

const float G_FRICTION = 0.02f;
const float G_BALL_MINSPEED = 0.3f;

const float G_TRACE_MAX_STEPS_COUNT = 2000;

const float	G_CUE_FORCE_STEP_SIZE = 0.02;
const float	G_CUE_MINFORCE = 1;
const float	G_CUE_MAXFORCE = 42;
const float G_CUE_WIDTH = 160.0f;
const float G_CUE_MINDISTANCE = 20.0f;
const float G_CUE_MAXDISTANCE = 90.0f;
const sf::Vector2f G_BALLS[] { sf::Vector2f(700, 200),
							   sf::Vector2f(720, 212), sf::Vector2f(720, 188),
							   sf::Vector2f(740, 200), sf::Vector2f(740, 224), sf::Vector2f(740, 176),
};