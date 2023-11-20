#include <Paddle.hpp>
#include <Globals.hpp>
#include <Controllers.hpp>

Paddle::Paddle(bool player_1, bool human) {
    physics_pipeline.push_back(this);
    render_pipeline.push_back(this);

    if (human == ISHUMAN) { controller = new PlayerController(player_1); }
    // else { } //Ai Controller

    setColor(sf::Color::White);

    if (player_1) { position.x = 20; }
    else { position.x = window->getSize().x - 40; }

    position.y = ((float)window->getSize().y / 2.0f) - ((float)shape.getSize().y / 2.0f);
}

void Paddle::physicsProcess() {
    const float border = 20;
    const float min_speed = 5000;

    float acceleration = controller->process() * accel_speed;

    velocity += acceleration * delta;

    float new_pos = position.y + (velocity * delta);

    logLine("acc: " << acceleration);
    logLine("vel: " << velocity);
    logLine("pos: " << position.y);

    position.y = new_pos;
}

void Paddle::renderProcess() {
    shape.setPosition({position.x, position.y});
    window->draw(shape);
}

Vector<float> Paddle::getPosition() { return position; };

void Paddle::setColor(const sf::Color &color) { shape.setFillColor(color); };

Paddle::~Paddle() { delete controller; }
