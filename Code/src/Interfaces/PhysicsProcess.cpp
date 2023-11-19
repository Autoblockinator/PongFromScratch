#pragma once
#include "../Utils/All.h"

class I_PhysicsProcess {
public:
    virtual void physicsProcess(float &delta) = 0;
};
