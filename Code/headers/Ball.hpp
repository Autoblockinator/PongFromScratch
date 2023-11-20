#pragma once
#include <SFML/Graphics.hpp>
#include <utils/All.hpp>
#include <Processes.hpp>

class Ball:
    public I_PhysicsProcess,
    public I_RenderProcess
{
public:
    Ball(sf::RenderWindow *window);

    void start();

    void launch();

    void physicsProcess(std::vector<I_PhysicsProcess*> &others, const float &delta);

    void renderProcess(sf::RenderWindow &window, const float &delta);

    void resetPosition();

    sf::Color getColor();
    void setColor(sf::Color &color);

protected:
    // Physics
    Vector<float> position{};
    Vector<float> velocity{};

    // Timing
    sf::Clock launch_delay_timer{};
    bool launch_waiting = false;

    // Rendering
    sf::CircleShape shape{10.0f};
    sf::RenderWindow *window;

};
