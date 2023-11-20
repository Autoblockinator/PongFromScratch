#pragma once
#include <utils/All.hpp>
#include <Processes.hpp>

class Paddle:
    public I_PhysicsProcess,
    public I_RenderProcess
{
public:
    Paddle(bool player_1);

    void physicsProcess();

    void renderProcess();

    Vector<float> getPosition();
    void setPosition(const Vector<float> &position);

    sf::Color getColor();
    void setColor(const sf::Color &color);

protected:
    // Input
    sf::Keyboard::Key up;
    sf::Keyboard::Key down;

    //Physics
    Vector<float> position{20, 20};
    float velocity = 0;
    float acceleration = 0;
    float speed = 7000;
    float deaccel_speed = 5000;

    // Rendering
    sf::RectangleShape shape{{20,100}};

};
