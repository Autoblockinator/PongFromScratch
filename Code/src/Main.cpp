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

int main() {
    window = new sf::RenderWindow{{1920, 1080}, "Pong"};

    Paddle p1{ISPLAYER1, ISHUMAN};
    // Paddle p2{ISPLAYER2, ISAI};
    
    sf::Clock clock{};
    while ((logicProcess() && running) || (!window->isOpen())) {
        physicsProcess();
        renderProcess();
        delta = clock.restart().asSeconds();
    }

    if (window->isOpen()) { window->close(); };
    return 0;
}
