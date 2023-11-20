#include <Controllers.hpp>
#include <Globals.hpp>

PlayerController::PlayerController(bool player_1) {
    if (player_1 == ISPLAYER2) {
        up = sf::Keyboard::Up;
        down = sf::Keyboard::Down;
    }
}

float PlayerController::process() {
    if (sf::Keyboard::isKeyPressed(up)) { return -1; }
    if (sf::Keyboard::isKeyPressed(down)) { return 1; }
    return 0;
}
