#include <Ball.hpp>
#include <Globals.hpp>

Ball::Ball() {
    physics_pipeline.push_back(this);
    render_pipeline.push_back(this);

    start();
}

void Ball::start() {
    position.x = window->getSize().x / 2.0f;
    position.y = window->getSize().y / 2.0f;

    launch_delay_timer.restart();
    launch_waiting = true;
}

void Ball::launch() {
    launch_waiting = false;
    shape.setFillColor(sf::Color::Red);
    velocity = {
        (float)rng(-100, 100) / 100.0f,
        (float)rng(-100, 100) / 100.0f
    };
}

void Ball::physicsProcess() {
    if (launch_waiting && (launch_delay_timer.getElapsedTime().asSeconds() > 1.0f)) { launch(); }

    sf::Vector2f new_pos = position + (velocity * delta);

    position = new_pos;
}

void Ball::renderProcess() {
    shape.setPosition({position.x, position.y});
    window->draw(shape);
}

void Ball::setHidden(bool hidden) { }

sf::Color Ball::getColor() { return shape.getFillColor(); }
void Ball::setColor(sf::Color &color) { shape.setFillColor(color); }
