#pragma once
#include "Utils/All.h"
#include "Interfaces.cpp"

class Paddle:
public
    I_LogicProcess,
    I_PhysicsProcess,
    I_RenderProcess
{
public:
    Paddle() {}

    bool logicProcess(float &delta) {
        return true;
    }

    void physicsProcess(float &delta) {}

    void renderProcess(sf::RenderWindow &window) { window.draw(shape); }

protected:
    sf::RectangleShape shape{{20,100}};
};
