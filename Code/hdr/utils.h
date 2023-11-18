#pragma once

#include <vector>
#define Vector std::vector

#include <string>
#define String std::string

#include <memory>
#define UniquePtr std::unique_ptr
#define makeUnique std::make_unique
#define SharedPtr std::shared_ptr
#define makeShared std::make_shared
#define WeakPtr std::weak_ptr

#include <iostream>
#define log(text) std::cout << text << std::endl

// namespace utils{
//     #include "../src/utils/string_utils.cpp"
// }