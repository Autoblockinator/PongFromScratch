#include <vector>
#ifndef Vector
#define Vector std::vector
#endif

#include <string>
#ifndef String
#define String std::string
#endif

#include <memory>
#ifndef UniquePtr
#define UniquePtr std::unique_ptr
#endif
#ifndef makeUnique
#define makeUnique std::make_unique
#endif
#ifndef SharedPtr
#define SharedPtr std::shared_ptr
#endif
#ifndef makeShared
#define makeShared std::make_shared
#endif

#include <iostream>

// namespace utils{
//     #include "../src/utils/string_utils.cpp"
// }