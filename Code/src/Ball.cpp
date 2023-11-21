#include <Ball.hpp>
#include <Globals.hpp>

Ball::Ball() {
    physics_pipeline.push_back(this);
    render_pipeline.push_back(this);

    start();
}

void Ball::start() {
    velocity = 0;

    position.x = window->getSize().x / 2.0f;
    position.y = window->getSize().y / 2.0f;

    launch_delay_timer.restart();
    launch_waiting = true;
}

void Ball::launch() {
    launch_waiting = false;
    velocity = vec2<float>::UP * 1000.0f;
    if (rng(0,1) == 1) { velocity.rotate(DEG2RAD(rng(90, 180) - 45)); }
    else { velocity.rotate(DEG2RAD(rng(-90, -180) + 45)); }
}

void Ball::physicsProcess() {
    if (launch_waiting && (launch_delay_timer.getElapsedTime().asSeconds() > 1.0f)) { launch(); }

    vec2<float> new_pos = position + (velocity * delta);
    
    // Bounce off floor & ceiling.
    {
        bool hit_bottom = (new_pos.y + shape.getSize().y) >= (window->getSize().y - SCREENBORDER);
        if ((new_pos.y <= SCREENBORDER) || hit_bottom) {
            if (!hit_bottom) { new_pos.y = SCREENBORDER; }
            else { new_pos.y = window->getSize().y - SCREENBORDER - shape.getSize().y; }
            velocity.y *= -1;

            // vec2<float> vel = {0, std::max(velocity.y, 0.0f)};
            // if () {}
    }}

    // Bounce off paddles.
    if (
        (new_pos.x <= SCREENBORDER + shape.getSize().x)
        ||
        (new_pos.x >= window->getSize().x - SCREENBORDER - shape.getSize().x)
    ) {
        Paddle *player = p1;
        if (new_pos.x > ((float)window->getSize().x / 2.0f)) { player = p2; }

        float diff = new_pos.y - player->position.y;
        if ((diff >= -shape.getSize().y) && (diff <= player->shape.getSize().y)) {
            // Set x position.
            if (player == p1) { new_pos.x = player->position.x + player->shape.getSize().x; }
            else { new_pos.x = player->position.x - shape.getSize().x; }
            
            // Figure out how much velocity should be transfered from x to y based on how far down the paddle the hit was.
            float transfer = LERP(
                -vel_transfer_max,
                (diff + shape.getSize().y) / (player->shape.getSize().y + shape.getSize().y),
                vel_transfer_max
            );

            // Reflect the x velocity and take some for the y.
            velocity.x *= 1.0f - std::abs(transfer) * -1.0f;

            // Set y velocity.
            velocity.y += transfer * velocity.x;
        } else {
            // Score.
            if (((new_pos.x + shape.getSize().x) >= (window->getSize().x - SCREENBORDER)) || (new_pos.x <= SCREENBORDER)) {
                start();
                return;
            }
        }
    }

    position = new_pos;
}

void Ball::renderProcess() {
    shape.setPosition({position.x, position.y});
    window->draw(shape);
}

void Ball::setHidden(bool hidden) { }

sf::Color Ball::getColor() { return shape.getFillColor(); }
void Ball::setColor(const sf::Color &color) { shape.setFillColor(color); }
