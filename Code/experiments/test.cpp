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
    #define DEFAULT ptr(nullptr), owner(nullptr), borrowers(Vector<CustomSmartPointer<T>*>())

    CustomSmartPointer(): DEFAULT {}

    explicit CustomSmartPointer(T* ptr): DEFAULT { this->ptr = ptr; }

    // CustomSmartPointer(CustomSmartPointer<T>& owner): DEFAULT { borrow(owner); }

    #undef DEFAULT

    // CustomSmartPointer<T>& operator=(CustomSmartPointer<T>& owner) { borrow(owner); return *this; }

    void borrow(CustomSmartPointer<T>& owner) {
        this->owner = &owner;
        ptr = owner.ptr;
        owner.borrowers.push_back(this);
    }

    // ~CustomSmartPointer() {}

    CustomSmartPointer<T>* getOwner() { return owner; }

    T* operator->() const { return ptr; }

    T& get() const { return *ptr; }

    bool operator==(const CustomSmartPointer<T>& other) { return ptr == other.ptr; }
    bool operator==(nullptr_t null) { return valid(); }

    bool valid() { return ptr == nullptr; }

protected:
    T* ptr;
    CustomSmartPointer<T>* owner;
    Vector<CustomSmartPointer<T>*> borrowers;
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

    CustomSmartPointer a{&var};
    CustomSmartPointer<TestClass> b;
    b.borrow(a);
    if (b.valid()) { logLine("b == null"); }
    else { logLine("b /= null"); }
    // logLine("a borrowers: " << a.test());

    return 0;
}