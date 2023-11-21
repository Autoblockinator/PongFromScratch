#include <Controllers.hpp>
#include <Globals.hpp>

AIController::AIController(bool player_1) { this->player_1 = player_1; }

float AIController::process() {
    if (waiting == 0) {
        waiting = (float)rng(1, 20) / 100.0f;
        timer.restart();

        if (rng(0,1) == 0) { output = -1; }
        else { output = 1; }
        // logLine("AI Out: " << output);
        // logLine("AI Time: " << waiting);
        return output;
    } else {
        if (timer.getElapsedTime().asSeconds() >= waiting) { waiting = 0; }
        return output;
    }
}
