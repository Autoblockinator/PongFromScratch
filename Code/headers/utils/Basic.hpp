#pragma once

#include <vector>

#include <string>
using std::string;

#include <cmath>
#define rng(from, to) (from + (rand() % ((to - from) + 1)))
#define DEG2RAD(degrees) (degrees * ((float)M_PI / 180.0f))
#define RAD2DEG(radians) (radians * (180.0f / (float)M_PI))

#include <memory>
using std::unique_ptr;
using std::make_unique;
using std::shared_ptr;
using std::make_shared;
using std::weak_ptr;

#include <iostream>
#define log(text) std::cout << text
#define logLine(text) log(text) << std::endl

