#pragma once
#include <SFML/Graphics.hpp>
#include <utils/Basic.hpp>

class I_LogicProcess {
public:
    virtual bool logicProcess(sf::Event &ev, const float &delta) = 0;
};

class I_PhysicsProcess {
public:
    virtual void physicsProcess(std::vector<I_PhysicsProcess*> &others, const float &delta) = 0;
};

class I_RenderProcess {
public:
    virtual void renderProcess(sf::RenderWindow &window, const float &delta) = 0;
};

bool logicProcess(
    const std::vector<I_LogicProcess*> &pipeline,
    float &delta,
    sf::RenderWindow &window
);

void physicsProcess(
    std::vector<I_PhysicsProcess*> &pipeline,
    float &delta
);

void renderProcess(
    const std::vector<I_RenderProcess*> &pipeline,
    sf::RenderWindow &window,
    const float &delta
);
