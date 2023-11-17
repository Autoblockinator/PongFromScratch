#include <iostream>
#include <vector>

template <typename T>
class CustomSmartPointer {
public:
    CustomSmartPointer() : ptr(nullptr), owner(true) {}

    explicit CustomSmartPointer(T* rawPtr) : ptr(rawPtr), owner(true) {}

    CustomSmartPointer(const CustomSmartPointer& other) : ptr(other.ptr), owner(false) {}

    ~CustomSmartPointer() {
        if (owner) {
            delete ptr;
        }
    }

    CustomSmartPointer& operator=(const CustomSmartPointer& other) {
        if (this != &other) {
            if (owner) {
                delete ptr;
            }
            ptr = other.ptr;
            owner = false;
        }
        return *this;
    }

    void freed() {
        if (owner) {
            if (ptr) {
                delete ptr;
            }
            for (auto& borrower : borrowers) {
                borrower->freed();
            }
            borrowers.clear();
            ptr = nullptr;
            owner = false;
        } else {
            ptr = nullptr;
        }
    }

    T* get() const {
        return ptr;
    }

    bool isOwner() const {
        return owner;
    }

    void addBorrower(CustomSmartPointer* borrower) {
        borrowers.push_back(borrower);
    }

private:
    T* ptr;
    bool owner;
    std::vector<CustomSmartPointer*> borrowers;
};

int main() {
    // Example usage
    CustomSmartPointer<int> ownerPtr(new int(42));
    CustomSmartPointer<int> borrowerPtr(ownerPtr);

    std::cout << "Owner pointer value: " << *ownerPtr.get() << std::endl;
    std::cout << "Borrower pointer value: " << *borrowerPtr.get() << std::endl;

    ownerPtr.freed();

    std::cout << "After freeing owner pointer, borrower pointer value: ";
    if (borrowerPtr.get() == nullptr) {
        std::cout << "nullptr" << std::endl;
    } else {
        std::cout << *borrowerPtr.get() << std::endl;
    }

    return 0;
}
