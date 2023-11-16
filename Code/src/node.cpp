#pragma once
#include <vector>

class Node
{
public:
    Node()
    {
        parent = nullptr;
        children = std::vector<Node*>();
        root = nullptr;
    }

    Node* getParent() { return parent; }

    Node* setParent(Node* new_parent)
    {
        parent = new_parent;
        if (parent == nullptr) { root = parent; return parent; }

        Node* old_root = root;
        if (findRoot() != old_root) { ready(); }
        
        return parent;
    }

    Node* setParentSameTree(Node* new_parent) { parent = new_parent; return parent; }

    Node* addChild(Node* new_child)
    {
        if (new_child == nullptr) { return nullptr; }
        children.push_back(new_child);
        new_child->setParent(this);
        return new_child;
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

    Node* findNode(const char* path)
    {
        return nullptr;
    }

protected:
    Node* parent;
    std::vector<Node*> children;
    Node* root;

    void ready() {} // Called when the root node is changed.
};
