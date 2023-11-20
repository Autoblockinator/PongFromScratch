#pragma once
#include <utils/All.hpp>
#include <Processes.hpp>
#include <Globals.hpp>
#include <Controllers.hpp>

class Paddle:
    public I_PhysicsProcess,
    public I_RenderProcess
{
public:
    Paddle(bool player_1, bool human = ISHUMAN);

    void physicsProcess();

    void renderProcess();

    Vector<float> getPosition();

    sf::Color getColor();
    void setColor(const sf::Color &color);

    ~Paddle();

protected:
    // Input
    Controller *controller;

    //Physics
    Vector<float> position{20, 20};
    float velocity = 0;
    const float accel_speed = 700;
    const float deaccel_speed = 1;

    // Rendering
    sf::RectangleShape shape{{20,100}};

};
