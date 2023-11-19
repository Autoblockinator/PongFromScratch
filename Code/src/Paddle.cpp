#pragma once
#include "Utils/All.h"
#include "Interfaces/LogicProcess.cpp"
#include "Interfaces/PhysicsProcess.cpp"
#include "Interfaces/RenderProcess.cpp"

class Paddle:
    I_LogicProcess,
    I_PhysicsProcess,
    I_RenderProcess
{
public:
    Paddle() {}

    void physicsProcess(float &delta) {}

    // void gameProcess

protected:
};
