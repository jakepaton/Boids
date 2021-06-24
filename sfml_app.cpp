// Libraries
#include <SFML/Graphics.hpp>
#include <vector>
#include "Boid.h"
#include "Constants.h"

int main()
{
    // Set up antialiasing
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;

    // Set up window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
    window.setFramerateLimit(60);

    // Set up view
    sf::View view(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), sf::Vector2f(WINDOW_WIDTH, -WINDOW_HEIGHT));
    view.zoom(1.0f);
    window.setView(view);

    // Create corner squares
    sf::CircleShape rect;
    rect.setRadius(20.0f);
    rect.setOrigin(sf::Vector2f(20.0f, 20.0f));

    // Create boids
    std::vector<Boid*> boids;
    for (int i = 0; i < NUM_BOIDS; i++)
    {
        int x = rand() % WORLD_WIDTH;
        int y = rand() % WORLD_HEIGHT;
        Boid* boid = new Boid(x, y);
        boids.push_back(boid);
    }

    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear the window
        window.clear(sf::Color::White);

        // Draw corners
        rect.setPosition(0, 0);
        rect.setFillColor(sf::Color::Red);
        window.draw(rect);
        rect.setPosition(WORLD_WIDTH, 0);
        rect.setFillColor(sf::Color::Blue);
        window.draw(rect);
        rect.setPosition(0, WORLD_HEIGHT);
        rect.setFillColor(sf::Color::Green);
        window.draw(rect);
        rect.setPosition(WORLD_WIDTH, WORLD_HEIGHT);
        rect.setFillColor(sf::Color::Magenta);
        window.draw(rect);

        // Update boids
        for (auto boid : boids)
        {
            boid->align(boids);
            boid->cohese(boids);
            boid->separate(boids);
        }

        // Draw boids
        for (auto boid : boids)
        {
            boid->update();
            window.draw(*boid);
        }

        // Display window
        window.display();
    }

    return 0;
}