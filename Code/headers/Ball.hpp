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
    void setColor(const sf::Color &color);

    // Variables
    // Physics
    vec2<float> position{};
    vec2<float> velocity{};

    // Timing
    sf::Clock launch_delay_timer{};
    bool launch_waiting = false;

    // Rendering
    sf::RectangleShape shape{{20,20}};

    // Constants
    // Physics
    //Multiplier, how much the x vel should
    //be transfered to y vel when hitting a paddle at most.
    const float vel_transfer_max = 0.5;

};
