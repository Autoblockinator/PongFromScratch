#include <Ball.hpp>
#include <Globals.hpp>

Ball::Ball() { start(); }

void Ball::start() {
    resetPosition();
    launch_delay_timer.restart();
    launch_waiting = true;
}

void Ball::launch() {
    launch_waiting = false;
    shape.setFillColor(sf::Color::Red);
    // velocity = {(float)rand(), 9};
}

void Ball::physicsProcess() {}

void Ball::renderProcess() {
    if (launch_waiting && (launch_delay_timer.getElapsedTime().asSeconds() > 1.0f)) { launch(); }

    shape.setPosition({position.x, position.y});
    window->draw(shape);
}

void Ball::resetPosition() {
    position.x = window->getSize().x / 2.0f;
    position.y = window->getSize().y / 2.0f;
}

sf::Color Ball::getColor() { return shape.getFillColor(); }
void Ball::setColor(sf::Color &color) { shape.setFillColor(color); }
