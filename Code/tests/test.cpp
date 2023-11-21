#include "../headers/utils/Vectors.hpp"
#include "../headers/utils/Basic.hpp"

int main() {
    vec2<float> pos{3,1};

    pos += vec2<float>{1,1};

    logLine("pos: {x: " << pos.x << ", y: " << pos.y << "}");

    return 0;
}
