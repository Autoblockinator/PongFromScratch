#pragma once
#include "Utils/All.h"
#include "Interfaces.cpp"

class Ball:
    public I_PhysicsProcess,
    public I_RenderProcess
{
public:
    Ball(sf::RenderWindow *window) {
        this->window = window;
        start();
    }

    void start() {
        resetPosition();
        launch_delay_timer.restart();
        launch_waiting = true;
    }

    void launch() {
        launch_waiting = false;
    }

    void physicsProcess(float &delta) {}

    void renderProcess(sf::RenderWindow &window) {
        if (launch_waiting && (launch_delay_timer.getElapsedTime().asSeconds() > 1.0f)) { launch(); }

        shape.setPosition({position.x, position.y});
        window.draw(shape);
    }

    void resetPosition() {
        position.x = window->getSize().x / 2.0f;
        position.y = window->getSize().y / 2.0f;
    }

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
