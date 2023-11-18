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

    CustomSmartPointer(T& ref): DEFAULT { setPtr(&ref); }

    CustomSmartPointer(T* ptr): DEFAULT { setPtr(ptr); }

    CustomSmartPointer(CustomSmartPointer<T>& owner): DEFAULT { borrow(owner); }

    #undef DEFAULT

    CustomSmartPointer<T>& operator=(T& other) { setPtr(&other); return *this; }
    
    CustomSmartPointer<T>& operator=(T* other) { setPtr(other); return *this; }

    // CustomSmartPointer<T>& operator=(CustomSmartPointer<T>& other) {
    //     ptr = other.ptr;
    //     owner = other.owner;
        
    //     targetChanged(nullptr);


    //     return *this;
    // }

    CustomSmartPointer<T>& operator=(nullptr_t null) { setPtr(nullptr); return *this; }

    void borrow(CustomSmartPointer<T>& owner) { connectOwner(owner); setPtr(owner.ptr); }

    void stopBorrowing() { disconnectOwner(); setPtr(nullptr); }

    void becomeOwner() { disconnectOwner(); }

    bool isBorrowing() { return owner != nullptr; }

    bool hasBorrowers() { return borrowers.size() > 0; }

    ~CustomSmartPointer() {
        disconnectOwner();
        for (int i = 0; i < borrowers.size(); i++) {
            borrowers[i]->disconnectOwner();
            borrowers[i]->setPtr(nullptr);
        }
    }

    // CustomSmartPointer<T>* getOwner() { return owner; }

    // T* operator->() const { return ptr; }

    // T& get() const { return *ptr; }

    bool operator==(const CustomSmartPointer<T>& other) { return ptr == other.ptr; }
    bool operator==(nullptr_t null) { return !isValid(); }

    bool isValid() { return ptr != nullptr; }

protected:
    T* ptr;
    CustomSmartPointer<T>* owner;
    Vector<CustomSmartPointer<T>*> borrowers;

    void setPtr(T* ptr) {
        this->ptr = ptr;
        for (int i = 0; i < borrowers.size(); i++) { borrowers[i]->setPtr(ptr); }
    }

    void connectOwner(CustomSmartPointer<T>& owner) {
        this->owner = &owner;
        owner.borrowers.push_back(this);
    }

    void disconnectOwner() {
        if (owner != nullptr) {
            for (int i = 0; i < owner->borrowers.size(); i++) {
                if (owner->borrowers[i] == this) {
                    owner->borrowers.erase(owner->borrowers.begin() + i);
                    break;
                }
            }
        }
        owner = nullptr;
    }
};



class TestClass {
public:
    String A;
    String B;

    TestClass(String a, String b): A(a), B(b) {}
};

#define CSP CustomSmartPointer
int main() {
    TestClass var_a{"Hello ", "World!"};
    logLine("var_a: " << var_a.A << var_a.B);
    TestClass var_b{"Hello ", "World!"};
    logLine("var_b: " << var_b.A << var_b.B);

    return 0;
}