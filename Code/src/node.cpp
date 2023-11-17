#include <utils.h>

class Node
{
public:
    Node()
    {
        name = String();
        self = SharedPtr<Node>(this);
        root = self;
        parent = WeakPtr<Node>();
        children = Vector<SharedPtr<Node>>();
    }

    Node(String name)
    {
        this->name = name;
        self = SharedPtr<Node>(this);
        root = self;
        parent = WeakPtr<Node>();
        children = Vector<SharedPtr<Node>>();
    }

    Node(String name, Vector<SharedPtr<Node>> children)
    {
        this->name = name;
        self = SharedPtr<Node>(this);
        root = self;
        parent = WeakPtr<Node>();
        this->children = children;
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
    WeakPtr<Node> addChild(Node &child) { return addChild(makeShared<Node>(child)); }

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
        if ( index >= children.size()) { return WeakPtr<Node>(); }
        return children[index];
    }
    WeakPtr<Node> getChild(String name)
    {
        for (uint i = 0; i < children.size(); i++) { if (children[i]->name == name) { return children[i]; } }
        return WeakPtr<Node>();
    }

    // Node* findNode(Vector<String>* path)
    // {
    //     auto var = makeShared<String>("Hello World!");
    //     return nullptr;
    // }

protected:
    String name;
    SharedPtr<Node> self;
    WeakPtr<Node> root;
    WeakPtr<Node> parent;
    Vector<SharedPtr<Node>> children;

    void ready() {} // Called when the root node is changed.
};
