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
        children.push_back(makeShared<Node>(child));
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

    WeakPtr<Node> getRoot()
    {
        if (!root.expired()) { return root; }
        if (parent == nullptr) { root = this; return root; }
        Node* new_root = parent;
        while (new_root->parent != nullptr) { new_root = new_root->parent; }
        root = new_root;
        return root;
    }

    WeakPtr<Node> findRoot() { root = WeakPtr<Node>(); return getRoot(); }

    Node* findNode(Vector<String>* path)
    {
        auto var = makeShared<String>("Hello World!");
        return nullptr;
    }

    // Node* findNode(String* path)
    // {
    //     return findNode(&utils::string::split());
    // }

protected:
    String name;
    SharedPtr<Node> self;
    WeakPtr<Node> root;
    WeakPtr<Node> parent;
    Vector<SharedPtr<Node>> children;

    void ready() {} // Called when the root node is changed.
};
