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
    p2 = new Paddle{ISPLAYER2, ISHUMAN};

    sf::Clock clock{};
    while (logicProcess() && running && window->isOpen()) {
        physicsProcess();
        renderProcess();
        delta = clock.restart().asSeconds();
    }

    if (window->isOpen()) { window->close(); };
    return 0;
}
