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

    CustomSmartPointer(T& ref): DEFAULT { ptr = &ref; }

    explicit CustomSmartPointer(T* ptr): DEFAULT { this->ptr = ptr; }

    CustomSmartPointer(CustomSmartPointer<T>& owner): DEFAULT { borrow(owner); }

    #undef DEFAULT

    T& operator=(T& other) {}

    T* operator=(T* other) {}

    CustomSmartPointer<T>& operator=(CustomSmartPointer<T>& other) {
        return *this;
    }

    // CustomSmartPointer<T>& operator=(nullptr_t null) {

    // }

    void borrow(CustomSmartPointer<T>& owner) {
        this->owner = &owner;
        ptr = owner.ptr;
        owner.borrowers.push_back(this);
    }

    ~CustomSmartPointer() {
        logLine("deleted");
        if (owner != nullptr) {
            for (int i = 0; i < owner->borrowers.size(); i++) {
                if (owner->borrowers[i] == this) {
                    owner->borrowers.erase(owner->borrowers.begin() + i);
                }
            }
        }
        targetChanged(nullptr);
    }

    void targetChanged(T* new_target) {
        logLine("targetChanged()");
        ptr = new_target;
        for (int i = 0; i < borrowers.size(); i++) { borrowers[i]->targetChanged(nullptr); }
    }

    CustomSmartPointer<T>* getOwner() { return owner; }

    T* operator->() const { return ptr; }

    T& get() const { return *ptr; }

    bool operator==(const CustomSmartPointer<T>& other) { return ptr == other.ptr; }
    bool operator==(nullptr_t null) { return !valid(); }

    bool valid() { return ptr != nullptr; }

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
    TestClass var{"Hello ", "World!"};
    logLine("var: " << var.A << var.B);

    // CustomSmartPointer a{var};
    // CustomSmartPointer<TestClass> b;
    // b = a;

    CustomSmartPointer<TestClass> b;
    {
        CustomSmartPointer a{&var};
        b.borrow(a);
        if (b == nullptr) { logLine("b invalid"); }
        else { logLine("b: " << b->A << b->B << " " << b.getOwner()); }
    }
    if (b == nullptr) { logLine("b invalid"); }
    else { logLine("b: " << b->A << b->B << " " << b.getOwner()); }
    
    return 0;
}