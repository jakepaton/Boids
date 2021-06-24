#include "Boid.h"

// Set up static member variables
std::default_random_engine Boid::generator;
std::normal_distribution<float> Boid::distribution(0.0f,5.0f);
float Boid::size(0.2f);

// Set up a static triangle for drawing each boid
sf::ConvexShape createTriangle()
{
    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(0, -40));
    triangle.setPoint(1, sf::Vector2f(100, 0));
    triangle.setPoint(2, sf::Vector2f(0, 40));
    triangle.setOrigin(sf::Vector2f(33.333f, 0));
    triangle.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255));
    return triangle;
}
sf::ConvexShape Boid::triangle = createTriangle();

Boid::Boid(float x, float y) :
	position(x, y),
    // Random initial velocity vector
	velocity(distribution(generator), distribution(generator)),
    acceleration(0.0f, 0.0f),
    // Random colour
    color{ rand() % 255, rand() % 255, rand() % 255 }
{
}

void Boid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    triangle.setPosition(position);
    triangle.setFillColor(color);
    triangle.setScale(size, size);
    triangle.setRotation(atan2(velocity.y, velocity.x) * 180 / PI);
    target.draw(triangle);
}

void Boid::update()
{
	velocity += acceleration;

    // Cap speed before updating position
    VectorFunctions::capMagnitude(velocity, MAX_SPEED);

	position += velocity;

    // Conform to toroidal geometry
    float x = fmod(position.x + WORLD_WIDTH, WORLD_WIDTH);
    float y = fmod(position.y + WORLD_HEIGHT, WORLD_HEIGHT);

    position = sf::Vector2f(x, y);

    // Reset acceleration to 0 vector before next update
    acceleration = sf::Vector2f(0.0f, 0.0f);
}

void Boid::accelerate(sf::Vector2f direction)
{
    acceleration += direction;
}

void Boid::align(const std::vector<Boid*>& boids)
{
    sf::Vector2f avg_vel{ 0.0f, 0.0f };
    int neighbours = 0;
    
    for (auto boid : boids)
    {
        if (boid == this)
            continue;
        
        float dist = VectorFunctions::toroidalDistance(this->getPosition(), boid->getPosition(), WORLD_WIDTH, WORLD_HEIGHT);

        if (dist < PERCEPTION_RADIUS)
        {
            neighbours++;
            avg_vel += boid->getVelocity();
        }
    }
    
    if (neighbours > 0)
        avg_vel /= (float)neighbours;

    sf::Vector2f diff = (avg_vel - velocity) / 8.0f;
    if (neighbours == 0)
        diff = sf::Vector2f(0.0f, 0.0f);

    accelerate(diff);
}

void Boid::cohese(const std::vector<Boid*>& boids)
{
    sf::Vector2f avg_pos{ 0.0f, 0.0f };
    int neighbours = 0;

    for (auto boid : boids)
    {
        if (boid == this)
            continue;

        sf::Vector2f disp = VectorFunctions::toroidalDirection(this->getPosition(), boid->getPosition(), WORLD_WIDTH, WORLD_HEIGHT);

        if (VectorFunctions::length(disp) < PERCEPTION_RADIUS)
        {
            neighbours++;
            avg_pos += this->getPosition() + disp;
        }
    }

    if (neighbours > 0)
        avg_pos /= (float)neighbours;

    sf::Vector2f diff = (avg_pos - this->getPosition()) / 100.0f;
    if (neighbours == 0)
        diff = sf::Vector2f(0.0f, 0.0f);

    accelerate(diff);
}

void Boid::separate(const std::vector<Boid*>& boids)
{
    sf::Vector2f avg_pos{ 0.0f, 0.0f };
    int neighbours = 0;

    for (auto boid : boids)
    {
        if (boid == this)
            continue;

        sf::Vector2f disp = VectorFunctions::toroidalDirection(this->getPosition(), boid->getPosition(), WORLD_WIDTH, WORLD_HEIGHT);

        if (VectorFunctions::length(disp) < AVOIDANCE_RADIUS)
        {
            neighbours++;
            avg_pos -= disp;
        }
    }

    accelerate(0.02f * avg_pos);
}
