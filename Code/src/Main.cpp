#include <Processes.hpp>
#include <Paddle.hpp>
#include <Ball.hpp>

int main() {
    sf::RenderWindow window{{1920, 1080}, "Pong"};
    window.setFramerateLimit(144);
    sf::Clock clock{};

    std::vector<I_LogicProcess*> logic_pipeline{};
    std::vector<I_PhysicsProcess*> physics_pipeline{};
    std::vector<I_RenderProcess*> render_pipeline{};

    Paddle p1{true, &window};
    physics_pipeline.push_back(&p1);
    render_pipeline.push_back(&p1);
    
    Paddle p2{false, &window};
    physics_pipeline.push_back(&p2);
    render_pipeline.push_back(&p2);

    Ball ball{&window};
    physics_pipeline.push_back(&ball);
    render_pipeline.push_back(&ball);

    for (
        float delta = clock.restart().asSeconds();
        logicProcess(logic_pipeline, delta, window);
    ) {

        //

        physicsProcess(physics_pipeline, delta);
        renderProcess(render_pipeline, window, delta);
    }

    window.close();
    return 0;
}
