#include <Globals.hpp>
#include <Processes.hpp>
#include <Paddle.hpp>
#include <Ball.hpp>
#include <Controllers.hpp>

sf::RenderWindow *window;

std::vector<I_LogicProcess*> logic_pipeline{};
std::vector<I_PhysicsProcess*> physics_pipeline{};
std::vector<I_RenderProcess*> render_pipeline{};

float delta = 0;

std::vector<sf::Event> events{};

bool running = true;

Paddle *p1;
Paddle *p2;
Ball *ball;

int main() {
    window = new sf::RenderWindow{{1920, 1080}, "Pong"};

    ball = new Ball{};
    p1 = new Paddle{ISPLAYER1, ISHUMAN};
    p2 = new Paddle{ISPLAYER2, ISAI};

    sf::Vertex line[] = {
        sf::Vertex{{window->getSize().x / 2.0f, window->getSize().y / 2.0f}},
        sf::Vertex{{window->getSize().x / 2.0f, window->getSize().y / 2.0f}}
    };
    line[1].position.x += 100;

    sf::Clock clock{};
    while ((logicProcess() && running) || (!window->isOpen())) {
        physicsProcess();
        vec2<float> vector = {line[1].position.x, line[1].position.y};
        vector.rotate(DEG2RAD(10));
        line[1].position = {vector.x, vector.y};
        renderProcess();
        window->draw(line, 2, sf::Lines);
        window->display();
        delta = clock.restart().asSeconds();
    }

    if (window->isOpen()) { window->close(); };
    return 0;
}
