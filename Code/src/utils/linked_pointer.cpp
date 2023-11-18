#include <utils/basic.h>

template <typename T>
class LinkedPointer {
public:
    #define DEFAULT ptr(nullptr), owner(nullptr), borrowers(Vector<LinkedPointer<T>*>())

    LinkedPointer(): DEFAULT {}

    LinkedPointer(T& ref): DEFAULT { setPtr(&ref); }

    LinkedPointer(T* ptr): DEFAULT { setPtr(ptr); }

    LinkedPointer(LinkedPointer<T>& owner): DEFAULT { borrow(owner); }

    #undef DEFAULT

    LinkedPointer<T>& operator=(T& other) { pointTo(&other); return *this; }
    
    LinkedPointer<T>& operator=(T* other) { pointTo(other); return *this; }

    // LinkedPointer<T>& operator=(LinkedPointer<T>& other) {
    // }

    LinkedPointer<T>& operator=(nullptr_t null) { setPtr(nullptr); return *this; }

    void borrow(LinkedPointer<T>& owner) { connectOwner(owner); setPtr(owner.ptr); }

    void stopBorrowing() { disconnectOwner(); setPtr(nullptr); }

    void becomeOwner() { disconnectOwner(); }

    bool isBorrowing() { return owner != nullptr; }

    bool hasBorrowers() { return borrowers.size() > 0; }

    ~LinkedPointer() {
        disconnectOwner();
        for (int i = 0; i < borrowers.size(); i++) {
            borrowers[i]->disconnectOwner();
            borrowers[i]->setPtr(nullptr);
        }
    }

    LinkedPointer<T>* getOwner() { return owner; }

    T* operator->() { return ptr; }

    T& get() { return *ptr; }

    void pointTo(T* ptr) {
        if (isBorrowing()) { becomeOwner(); }
        setPtr(ptr);
    }

    bool operator==(const LinkedPointer<T>& other) { return ptr == other.ptr; }
    bool operator==(nullptr_t null) { return !isValid(); }

    bool isValid() { return ptr != nullptr; }

protected:
    T* ptr;
    LinkedPointer<T>* owner;
    Vector<LinkedPointer<T>*> borrowers;

    void setPtr(T* ptr) {
        this->ptr = ptr;
        for (int i = 0; i < borrowers.size(); i++) { borrowers[i]->setPtr(ptr); }
    }

    void connectOwner(LinkedPointer<T>& owner) {
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
