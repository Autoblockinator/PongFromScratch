#include <Paddle.hpp>

Paddle::Paddle(bool player_1, sf::RenderWindow* window) {
    this->window = window;

    setColor(color);

    if (player_1) {
        up = sf::Keyboard::W;
        down = sf::Keyboard::S;

        setPosition({20,0});
    } else {
        up = sf::Keyboard::Up;
        down = sf::Keyboard::Down;

        setPosition({(float)window->getSize().x - 40.0f,0});
    }

    setPosition(Vector<float>{ position.x,
        ((float)window->getSize().y / 2.0f)
                        -
        ((float)shape.getSize().y / 2.0f)
    });
};

void Paddle::physicsProcess(std::vector<I_PhysicsProcess*> &others, const float &delta) {
    using sf::Keyboard;
    const float border = 20;
    const float min_speed = 5000;

    if (Keyboard::isKeyPressed(up)) { acceleration += speed * -1; }
    if (Keyboard::isKeyPressed(down)) { acceleration += speed; }

    if ((std::abs(velocity) >= min_speed) && (acceleration == 0)) {
        if (velocity > 0) { acceleration = -deaccel_speed; }
        else { acceleration = deaccel_speed; }
    } else {
        bool vel_pos = velocity > 0;
        bool acc_pos = acceleration > 0;
        if (vel_pos != acc_pos) { acceleration *= 1; }
    }

    velocity += acceleration;
    Vector<float> new_pos{position.x, position.y + (velocity * delta)};

    if (
        ((new_pos.y + shape.getSize().y) > (window->getSize().y - border))
        ||
        (new_pos.y < border)
    ) {
        velocity = velocity * -0.5;
        new_pos.y += velocity * delta;
    }

    setPosition({new_pos.x, std::min(
            std::max(new_pos.y,
            border),
        (window->getSize().y - shape.getSize().y) - border
    )});

    if ((std::abs(velocity) < min_speed) && !(
        Keyboard::isKeyPressed(up)
        ||
        Keyboard::isKeyPressed(down)
    )) { velocity = 0; }

    // logLine("dt: " << delta);
    // logLine("acc: " << acceleration);
    // logLine("vel: " << velocity);
    // logLine("position: " << position.y);

    acceleration = 0;
};

void Paddle::renderProcess(sf::RenderWindow &window, const float &delta) {
    this->window = &window;
    shape.setPosition({position.x, position.y});
    window.draw(shape);
};


Vector<float> Paddle::getPosition() { return position; };
void Paddle::setPosition(const Vector<float> &position) { this->position = position; };

void Paddle::setColor(const sf::Color &color) { this->position = position; };
