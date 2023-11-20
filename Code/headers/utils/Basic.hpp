#pragma once

#include <vector>

#include <string>
using std::string;

#include <cmath>

#include <memory>
using std::unique_ptr;
using std::make_unique;
using std::shared_ptr;
using std::make_shared;
using std::weak_ptr;

#include <iostream>
#define log(text) std::cout << text
#define logLine(text) log(text) << std::endl

