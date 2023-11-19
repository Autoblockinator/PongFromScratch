#pragma once
#include "../Utils/All.h"

class PhysicsObject {
public:
    PhysicsObject() {}

protected:
    vec position{0,0};
    vec velocity{0,0};

};
#define PhysObj PhysicsObject
