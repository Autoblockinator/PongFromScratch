#include <iostream>
#define log(text) std::cout << text << std::endl
#include <vector>
#define Vector std::vector
#include <string>
#define String std::string

template <typename T>
class CustomSmartPointer {
public:
    CustomSmartPointer(): ptr(nullptr) borrowers() {}

protected:
    T* ptr;
    Vector<CustomSmartPointer*> borrowers;
};

int main() {
    auto var = 69;

    log("");
    return 0;
}