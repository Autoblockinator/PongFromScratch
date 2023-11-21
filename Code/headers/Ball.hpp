#pragma once
#include <SFML/Graphics.hpp>
#include <utils/All.hpp>
#include <Processes.hpp>

class Ball:
    public I_PhysicsProcess,
    public I_RenderProcess
{
public:
    Ball();

    void start();

    void launch();

    void physicsProcess();

    void renderProcess();

    void setHidden(bool hidden);

    sf::Color getColor();
    void setColor(sf::Color &color);

protected:
    // Physics
    sf::Vector2f position{};
    sf::Vector2f velocity{};

    // Timing
    sf::Clock launch_delay_timer{};
    bool launch_waiting = false;

    // Rendering
    sf::RectangleShape shape{{20,20}};

};
