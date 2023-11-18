#include <utils.h>

class Node
{
public:
    Node() { constructDefaults(); }

    Node(const String &name) { constructDefaults(); this->setName(name); }

    Node(const String &name, Vector<SharedPtr<Node>> children)
    {
        constructDefaults();
        this->setName(name);
        this->addChildren(children);
    }

    WeakPtr<Node> getParent() { return parent; }

    WeakPtr<Node> setParent(WeakPtr<Node> parent)
    {
        this->parent = parent;
        if (this->parent.expired()) { root = self; return this->parent; }

        auto old_root = root;
        if (findRoot().lock() != old_root.lock()) { ready(); }
        
        return this->parent;
    }

    WeakPtr<Node> setParentSameTree(WeakPtr<Node> parent) { this->parent = parent; return this->parent; }

    WeakPtr<Node> addChild(SharedPtr<Node> child)
    {
        children.push_back(child);
        if (!child->parent.expired()) { child->parent.lock()->removeLastChild(); }
        child->setParent(self);
        return children.back();
    }
    WeakPtr<Node> addChild(Node &child) { return addChild(SharedPtr<Node>(&child)); }
    Vector<WeakPtr<Node>> addChildren(Vector<SharedPtr<Node>> children)
    {
        Vector<WeakPtr<Node>> out;
        for (int i = 0; i < children.size(); i++) { this->addChild(children[i]); out.push_back(children[i]); }
        return out;
    }
    Vector<WeakPtr<Node>> addChildren(Vector<WeakPtr<Node>> children)
    { for (int i = 0; i < children.size(); i++) { this->addChild(children[i].lock()); } return children; }

    // Remove a child node.
    SharedPtr<Node> removeChild(int child)
    {
        auto out = children[child];
        children.erase(vectorIterAt(children, child));
        return out;
    }
    SharedPtr<Node> removeLastChild() { return removeChild(children.size() - 1); }

    // Find & get the root node.
    WeakPtr<Node> getRoot()
    {
        if (!root.expired()) { return root; }
        if (parent.expired()) { root = self; return root; }
        auto new_root = parent.lock();
        while (!new_root->parent.expired()) { new_root = new_root->parent.lock(); }
        root = new_root;
        return root;
    }
    WeakPtr<Node> findRoot() { root = WeakPtr<Node>(); return getRoot(); }

    // Get a child node.
    WeakPtr<Node> getChild(int index)
    {
        if ( index >= 0 && index < children.size()) { return children[index]; }
        return WeakPtr<Node>();
    }
    WeakPtr<Node> getChild(String name) { return getChild(getChildIndex(name)); }
    int getChildIndex(String name)
    {
        for (int i = 0; i < children.size(); i++) { if (children[i]->name == name) { return i; } }
        return -1;
    }

    // Name SetGet
    String getName() { return name; }
    String setName(const String &name)
    {
        this->name = name;
        return this->name;
    }

protected:
    String name;
    SharedPtr<Node> self;
    WeakPtr<Node> root;
    WeakPtr<Node> parent;
    Vector<SharedPtr<Node>> children;

    void constructDefaults()
    {
        name = "Node";
        self = SharedPtr<Node>(this);
        root = self;
        parent = WeakPtr<Node>();
        children = Vector<SharedPtr<Node>>();
    }

    void ready() { log("Ready Called On Node \"" << name << "\""); } // Called when the root node is changed.
};
