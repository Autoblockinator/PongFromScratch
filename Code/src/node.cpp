#pragma once
#include <vector>
#include <string>
#include <utils.h>

class Node
{
public:
    Node()
    {
        root = this;
        parent = nullptr;
        children = std::vector<Node*>();
    }

    Node(Node* parent)
    {
        root = parent->getRoot();
        this->parent = parent;
        children = std::vector<Node*>();
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

    Node* addChild(Node* child)
    {
        if (child == nullptr) { return nullptr; }
        children.push_back(child);
        child->setParent(this);
        return child;
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

    Node* findNode(std::vector<std::string>* path)
    {
        return nullptr;
    }

    Node* findNode(std::string* path)
    {
        return findNode(&utils::string::split());
    }

protected:
    std::string name;
    Node* root;
    Node* parent;
    std::vector<Node*> children;

    void ready() {} // Called when the root node is changed.
};
