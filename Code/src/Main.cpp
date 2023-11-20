#include <Globals.hpp>
#include <Processes.hpp>
#include <Paddle.hpp>
#include <Ball.hpp>

sf::RenderWindow *window;

std::vector<I_LogicProcess*> logic_pipeline{};
std::vector<I_PhysicsProcess*> physics_pipeline{};
std::vector<I_RenderProcess*> render_pipeline{};

float delta = 0;

std::vector<sf::Event> events{};

bool running = true;

int main() {
    window = new sf::RenderWindow{{1920, 1080}, "Pong"};

    Paddle p1{true};
    
    // Paddle p2{false, &window};
    // physics_pipeline.push_back(&p2);
    // render_pipeline.push_back(&p2);

    // Ball ball{&window};
    // physics_pipeline.push_back(&ball);
    // render_pipeline.push_back(&ball);
    
    sf::Clock clock{};
    while (logicProcess() && running) {
        physicsProcess();
        renderProcess();
        delta = clock.restart().asSeconds();
    }

    window->close();
    return 0;
}
