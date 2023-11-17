#include <vector>
#ifndef Vector
#define Vector std::vector
#endif

#include <string>
#ifndef String
#define String std::string
#endif

class Node
{
public:
    Node()
    {
        name = String("");
        root = this;
        parent = nullptr;
        children = Vector<Node>();
    }

    Node(String name)
    {
        this->name = name;
        root = this;
        parent = nullptr;
        children = Vector<Node>();
    }

    Node(String name, Vector<Node> children)
    {
        this->name = name;
        root = this;
        parent = nullptr;
        this->children = children;
    }

    Node* getParent() { return parent; }

    Node* setParent(Node* parent)
    {
        this->parent = parent;
        if (this->parent == nullptr) { root = this->parent; return this->parent; }

        Node* old_root = root;
        if (findRoot() != old_root) { ready(); }
        
        return this->parent;
    }

    Node* setParentSameTree(Node* parent) { this->parent = parent; return this->parent; }

    Node* addChild(Node child)
    {
        children.push_back(child);
        if (child.parent != nullptr) { child.parent->removeChild(child); }
        child.setParent(this);
        return &children.back();
    }

    Node* addChild(Node* child)
    {
        if (child == nullptr) { return nullptr; }
        children.push_back(*child);
        child->setParent(this);
        return child;
    }

    void removeChild(Node child)
    {
        for (auto i = children.begin(); i <= children.end(); i += 1)
        {

        }
    }

    Node* getRoot()
    {
        if (root != nullptr) { return root; }
        if (parent == nullptr) { root = this; return root; }
        Node* new_root = parent;
        while (new_root->parent != nullptr) { new_root = new_root->parent; }
        root = new_root;
        return root;
    }

    Node* findRoot() { root = nullptr; return getRoot(); }

    Node* findNode(Vector<String>* path)
    {
        return nullptr;
    }

    // Node* findNode(String* path)
    // {
    //     return findNode(&utils::string::split());
    // }

protected:
    String name;
    Node* root;
    Node* parent;
    Vector<Node> children;

    void ready() {} // Called when the root node is changed.
};
