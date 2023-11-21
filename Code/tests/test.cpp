#include "../headers/utils/Vectors.hpp"
#include "../headers/utils/Basic.hpp"

int main() {

    auto vector = vec2<float>::RIGHT;
    vector.rotate(10);
    logLine("{x: " << vector.x << ", y: " << vector.y << "}");

    return 0;
}
