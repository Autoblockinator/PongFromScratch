#pragma once
#include <SFML/Graphics.hpp>
#include <utils/Basic.hpp>

class I_LogicProcess {
public:
    virtual bool logicProcess() = 0;
};

class I_PhysicsProcess {
public:
    virtual void physicsProcess() = 0;
};

class I_RenderProcess {
public:
    virtual void renderProcess() = 0;
};

bool logicProcess();

void physicsProcess();

void renderProcess();
