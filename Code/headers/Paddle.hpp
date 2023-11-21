#pragma once
#include <utils/All.hpp>
#include <Processes.hpp>
#include <Controllers.hpp>

class Paddle:
    public I_PhysicsProcess,
    public I_RenderProcess
{
public:
    Paddle(bool player_1, bool human = true);

    void physicsProcess();

    void renderProcess();

    sf::Vector2f getPosition();

    float getVelocity();

    sf::Color getColor();
    void setColor(const sf::Color &color);

    ~Paddle();

protected:
    // Input
    Controller *controller;

    //Physics
    sf::Vector2f position{20, 20};
    float velocity = 0;
    const float accel_speed = 2000;
    const float deaccel_speed = 500;
    const float wall_bounciness = 0.2;
    const float stopping_speed = 1;
    const float turning_boost = 2;

    // Rendering
    sf::RectangleShape shape{{20,100}};

};
