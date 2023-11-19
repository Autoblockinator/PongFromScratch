#pragma once
#include "Utils/All.h"

class I_LogicProcess {
public:
    virtual bool logicProcess(sf::Event &ev, float &delta) = 0;
};

class I_PhysicsProcess {
public:
    virtual void physicsProcess(float &delta) = 0;
};

class I_RenderProcess {
public:
    virtual void renderProcess(sf::RenderWindow &window) = 0;
};
