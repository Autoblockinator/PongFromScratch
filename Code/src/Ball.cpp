#include <Ball.hpp>
#include <Globals.hpp>

Ball::Ball() {
    physics_pipeline.push_back(this);
    render_pipeline.push_back(this);

    start();
}

void Ball::start() {
    velocity = 0;
    test += 10;
    if (test == 360) { test = 0; }

    position.x = window->getSize().x / 2.0f;
    position.y = window->getSize().y / 2.0f;

    launch_delay_timer.restart();
    launch_waiting = true;
}

void Ball::launch() {
    launch_waiting = false;
    setColor(sf::Color::Red);
    
    velocity = vec2<float>::RIGHT * 500.0f;
    velocity.rotate(DEG2RAD(test));
    // velocity.rotate(DEG2RAD(rng(0,360)));
}

void Ball::physicsProcess() {
    if (launch_waiting && (launch_delay_timer.getElapsedTime().asSeconds() > 1.0f)) { launch(); }

    vec2<float> new_pos = position + (velocity * delta);

    if (
        ((new_pos.x + shape.getSize().x) >= (window->getSize().x - SCREENBORDER)) || (new_pos.x <= SCREENBORDER)
        ||
        ((new_pos.y + shape.getSize().y) >= (window->getSize().y - SCREENBORDER)) || (new_pos.y <= SCREENBORDER)
    ) { start(); }

    else {position = new_pos;}
}

void Ball::renderProcess() {
    shape.setPosition({position.x, position.y});
    window->draw(shape);
}

void Ball::setHidden(bool hidden) { }

sf::Color Ball::getColor() { return shape.getFillColor(); }
void Ball::setColor(const sf::Color &color) { shape.setFillColor(color); }
