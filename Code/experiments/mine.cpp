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

    explicit CustomSmartPointer(T* ptr): DEFAULT { this->ptr = ptr; }

    CustomSmartPointer(const CustomSmartPointer<T>& owner): DEFAULT { borrow(owner); }

    #ifdef DEFAULT
    #undef DEFAULT
    #endif

    CustomSmartPointer& operator=(const CustomSmartPointer<T>& owner) { borrow(owner); return *this; }

    void borrow(const CustomSmartPointer<T>& owner) { ptr = owner.ptr; owner.borrowers.push_back(this); }

    ~CustomSmartPointer() {

    }

    T* operator->() const { return ptr; }

    T& get() const { return *ptr; }

    CustomSmartPointer<T>& getOwner() {
        if (typeid(*ptr) == typeid(CustomSmartPointer<T>)) { return *ptr; }
        else { return nullptr; }
    }

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

    CustomSmartPointer csp{&var};
    logLine("csp->: " << csp->A << csp->B);

    return 0;
}