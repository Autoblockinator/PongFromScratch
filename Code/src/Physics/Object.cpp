#include <Utils/All.h>

class PhysicsObject {
public:
    PhysicsObject(): position(vec{0,0}), velocity(vec{0,0}) {}

protected:
    vec position;
    vec velocity;

};
