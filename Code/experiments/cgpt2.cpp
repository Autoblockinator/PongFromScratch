#include <iostream>
#include <vector>

template <typename T>
class CustomSmartPointer {
public:
    CustomSmartPointer() : data(nullptr), borrowers() {}

    // Constructor for raw pointer (owner)
    explicit CustomSmartPointer(T* ptr) : data(ptr), borrowers() {}

    // Constructor for another smart pointer (borrower)
    CustomSmartPointer(const CustomSmartPointer<T>& other) : data(other.data), borrowers(other.borrowers) {}

    // Destructor
    ~CustomSmartPointer() {
        if (data != nullptr) {
            std::cout << "Deleting data: " << *data << std::endl;
            delete data;
            data = nullptr;
        }
    }

    // Check if the pointer is freed
    bool freed() const {
        return data == nullptr;
    }

    // Release the ownership and make it a borrower
    void makeBorrower() {
        data = nullptr;
    }

    // Add a borrower to the owner
    void addBorrower(CustomSmartPointer<T>& borrower) {
        borrowers.push_back(&borrower);
    }

    // Get the raw pointer
    T* get() const {
        return data;
    }

    // Overloaded arrow operator
    T* operator->() const {
        return get();
    }

    // Assignment operator for raw pointer
    CustomSmartPointer<T>& operator=(T* ptr) {
        if (data != nullptr) {
            delete data;
        }
        data = ptr;
        return *this;
    }

    // Assignment operator for another smart pointer
    CustomSmartPointer<T>& operator=(const CustomSmartPointer<T>& other) {
        if (this != &other) {
            data = other.data;
            borrowers = other.borrowers;
        }
        return *this;
    }

private:
    T* data;
    std::vector<CustomSmartPointer<T>*> borrowers;
};

int main() {
    // Example usage
    CustomSmartPointer<int> owner(new int(42));
    CustomSmartPointer<int> borrower1(owner);
    CustomSmartPointer<int> borrower2(owner);

    std::cout << "Owner value: " << *owner.get() << std::endl;
    std::cout << "Borrower1 value: " << *borrower1.get() << std::endl;
    std::cout << "Borrower2 value: " << *borrower2.get() << std::endl;

    owner.makeBorrower(); // Release ownership
    std::cout << "Owner freed: " << owner.freed() << std::endl;
    std::cout << "Borrower1 freed: " << borrower1.freed() << std::endl;
    std::cout << "Borrower2 freed: " << borrower2.freed() << std::endl;

    return 0;
}
