#pragma once
#include <SFML/Graphics.hpp>
#include <utils/All.hpp>
#include <Ball.hpp>

class Controller {
public:
    virtual float process() = 0;
};

class PlayerController:
    public Controller
{
public:
    sf::Keyboard::Key up = sf::Keyboard::W;
    sf::Keyboard::Key down = sf::Keyboard::S;

    PlayerController(bool player_1);

    float process();
};
