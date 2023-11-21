#include <Paddle.hpp>
#include <Globals.hpp>
#include <Controllers.hpp>

Paddle::Paddle(bool player_1, bool human) {
    physics_pipeline.push_back(this);
    render_pipeline.push_back(this);

    if (human == ISHUMAN) { controller = new PlayerController(player_1); }
    else { controller = new AIController(player_1); }

    setColor(sf::Color::White);

    if (player_1) { position.x = SCREENBORDER; }
    else { position.x = window->getSize().x - SCREENBORDER - shape.getSize().x; }

    position.y = ((float)window->getSize().y / 2.0f) - ((float)shape.getSize().y / 2.0f);
}

void Paddle::physicsProcess() {
    float acceleration = controller->process() * accel_speed;

    // Add acceleration.
    if (std::abs(acceleration) > 0.0f) {
        bool accpos = acceleration > 0;
        bool velpos = velocity > 0;
        if (accpos == velpos) { velocity += acceleration * delta; }
        else { velocity += acceleration * turning_boost * delta; }
    } else {
        if (std::abs(velocity) > stopping_speed) {
            if (velocity > 0) { velocity -= deaccel_speed * delta; }
            else { velocity += deaccel_speed * delta; }
        } else { velocity = 0; }
    }

    // Set virtual position
    float new_pos = position.y + (velocity * delta);

    // Bounce off screen border.
    if ((new_pos + shape.getSize().y) >= (window->getSize().y - SCREENBORDER)) {
        new_pos = window->getSize().y - SCREENBORDER - shape.getSize().y;
        velocity *= -wall_bounciness;
    } else { if (new_pos <= SCREENBORDER) {
        new_pos = SCREENBORDER;
        velocity *= -wall_bounciness;
    }}

    // Logging
    // logLine("acc: " << acceleration);
    // logLine("vel: " << velocity);
    // logLine("pos: " << position.y);

    // Finalize
    position.y = new_pos;
}

void Paddle::renderProcess() {
    shape.setPosition({position.x, position.y});
    window->draw(shape);
}

void Paddle::setColor(const sf::Color &color) { shape.setFillColor(color); };

Paddle::~Paddle() { delete controller; }
