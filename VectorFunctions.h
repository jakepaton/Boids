#pragma once
#include "SFML/Graphics.hpp"

namespace VectorFunctions
{
	float length(const sf::Vector2f vec);

	void normalise(sf::Vector2f& vec);

	void setMagnitude(sf::Vector2f& vec, float mag);

	void capMagnitude(sf::Vector2f& vec, float cap);

	float toroidalDistance(const sf::Vector2f vec1, const sf::Vector2f vec2, float torus_width, float torus_height);

	sf::Vector2f toroidalDirection(const sf::Vector2f vec1, const sf::Vector2f vec2, float torus_width, float torus_height);
}
