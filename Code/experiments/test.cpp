#include <iostream>
#define log(text) std::cout << text
#define logLine(text) log(text) << std::endl

#include <vector>
#define Vector std::vector

#include <string>
#define String std::string



template <typename T>
class CustomSmartPointer {
public:
    #ifndef DEFAULT
    #define DEFAULT ptr(nullptr), borrowers(Vector<CustomSmartPointer<T>*>())
    #endif

    CustomSmartPointer(): DEFAULT {}

    // explicit CustomSmartPointer(T* ptr): DEFAULT { this->ptr = ptr; } //Untested

    // CustomSmartPointer(const CustomSmartPointer<T>& owner): DEFAULT { borrow(owner); } //Untested

    #ifdef DEFAULT
    #undef DEFAULT
    #endif

    // CustomSmartPointer& operator=(const CustomSmartPointer<T>& owner) { borrow(owner); return *this; } //Untested

    // void borrow(const CustomSmartPointer<T>& owner) { ptr = owner.ptr; owner.borrowers.push_back(this); } //Untested

    // ~CustomSmartPointer() {} //Untested

    // CustomSmartPointer<T>* getOwner() {
    //     if (typeid(*ptr) == typeid(CustomSmartPointer<T>)) { return ptr; }
    //     else { return nullptr; }
    // } //Untested

    // T* operator->() const {
    //     if (getOwner == nullptr) { return ptr; }
    //     while (CustomSmartPointer<T>* i; i)
    // } //Untested

    // T& get() const { return *ptr; } //Untested

    // bool isValid() {
    //     if ( getOwner() == nullptr) { return ptr == nullptr; }

    // } //Untested

protected:
    T* ptr;
    Vector<CustomSmartPointer<T>*> borrowers;

    void constructDefault() { ptr = nullptr; borrowers = Vector<CustomSmartPointer<T>*>(); }
};



class TestClass {
public:
    String A;
    String B;

    TestClass(String a, String b): A(a), B(b) {}
};



int main() {
    TestClass var{"Hello ", "World! "};
    logLine("var: " << var.A << var.B);

    CustomSmartPointer<TestClass> owner;

    return 0;
}