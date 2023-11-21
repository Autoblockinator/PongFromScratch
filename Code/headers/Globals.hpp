#pragma once
#include <SFML/Graphics.hpp>
#include <Processes.hpp>
#include <Paddle.hpp>

#define ISHUMAN true
#define ISAI false
#define ISPLAYER1 true
#define ISPLAYER2 false

#define SCREENBORDER 20

extern sf::RenderWindow *window;

extern std::vector<I_LogicProcess*> logic_pipeline;
extern std::vector<I_PhysicsProcess*> physics_pipeline;
extern std::vector<I_RenderProcess*> render_pipeline;

extern float delta;

extern std::vector<sf::Event> events;

extern bool running;

extern Paddle *p1;
extern Paddle *p2;
extern Ball *ball;
