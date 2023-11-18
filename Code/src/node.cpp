#include <utils/all.h>

class Node {
public:
    // Constructors
    #define DEFAULT name(""), parent(nullptr), children(Vector<LinkedPointer<Node>>())

    Node(): DEFAULT {}

    #undef DEFAULT

    // Set Get
    String& getName() { return this->name; }
    void setName(String& name) { this->name = name; }

    LinkedPointer<Node>& getParent() { return parent; }

    LinkedPointer<Node>& getChild(int child) { return children[child]; }
    LinkedPointer<Node>& getChild(String child) {
        for (int i = 0; i < children.size(); i++) {
            if (child == children[i]->getName()) { return getChild(i); }
        }
    }

    // LinkedPointer<Node>& getNode(const int* path) {} //TODO
    // LinkedPointer<Node>& getNode(const char* path) {} //TODO
    // LinkedPointer<Node>& getNode(const String& path) {} //TODO

protected:
    String name;
    LinkedPointer<Node> parent;
    Vector<LinkedPointer<Node>> children;

};
