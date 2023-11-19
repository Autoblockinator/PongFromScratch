#pragma once
#include "../Utils/All.h"

class I_RenderProcess {
public:
    virtual void renderProcess(sf::RenderWindow &window) = 0;
};
