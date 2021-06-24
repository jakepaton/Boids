#pragma once
#include <random>
#include "SFML/Graphics.hpp"
#include "Constants.h"
#include "VectorFunctions.h"

class Boid : public sf::Drawable
{
public:
	Boid(float x, float y);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Vector2f getPosition() const { return position; }
	sf::Vector2f getVelocity() const { return velocity; }

	void update();

	void accelerate(const sf::Vector2f direction);
	void align(const std::vector<Boid*>& boids);
	void cohese(const std::vector<Boid*>& boids);
	void separate(const std::vector<Boid*>& boids);

private:
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;

	sf::Color color;

	static std::default_random_engine generator;
	static std::normal_distribution<float> distribution;

	static float size;
	static sf::ConvexShape triangle;
};