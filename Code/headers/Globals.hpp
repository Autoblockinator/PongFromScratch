#pragma once
#include <SFML/Graphics.hpp>
#include <Processes.hpp>

extern sf::RenderWindow *window;

extern std::vector<I_LogicProcess*> logic_pipeline;
extern std::vector<I_PhysicsProcess*> physics_pipeline;
extern std::vector<I_RenderProcess*> render_pipeline;

extern float delta;

extern std::vector<sf::Event> events;

extern bool running;