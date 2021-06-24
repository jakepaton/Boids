#include "VectorFunctions.h"

float VectorFunctions::length(sf::Vector2f vec)
{
	return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

void VectorFunctions::normalise(sf::Vector2f& vec)
{
	float len = length(vec);
	if (len > 0)
		vec /= len;
}

void VectorFunctions::setMagnitude(sf::Vector2f& vec, float mag)
{
	normalise(vec);
	vec *= mag;
}

void VectorFunctions::capMagnitude(sf::Vector2f& vec, float cap)
{
	float len = length(vec);
	if (len > cap)
	{
		normalise(vec);
		vec *= cap;
	}
}

float VectorFunctions::toroidalDistance(const sf::Vector2f vec1, const sf::Vector2f vec2, float torus_width, float torus_height)
{
	float x_disp = std::abs(vec2.x - vec1.x);
	float y_disp = std::abs(vec2.y - vec1.y);

	if (x_disp > torus_width / 2)
		x_disp = torus_width - x_disp;

	if (y_disp > torus_height / 2)
		y_disp = torus_height - y_disp;

	return length(sf::Vector2f(x_disp, y_disp));
}

sf::Vector2f VectorFunctions::toroidalDirection(const sf::Vector2f vec1, const sf::Vector2f vec2, float torus_width, float torus_height)
{
	float x_disp = vec2.x - vec1.x;
	float y_disp = vec2.y - vec1.y;

	if (std::abs(x_disp) > torus_width / 2)
		x_disp += torus_width * ((x_disp < 0) - (x_disp > 0));

	if (std::abs(y_disp) > torus_height / 2)
		y_disp += torus_height * ((y_disp < 0) - (y_disp > 0));

	return sf::Vector2f(x_disp, y_disp);
}
