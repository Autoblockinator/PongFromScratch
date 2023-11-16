#pragma once
#include <vector>

class Node
{
public:
    Node()
    {
        parent = nullptr;
        children = std::vector<Node*>();
    }

    Node* getParent() { return parent; }

    Node* setParent(Node* new_parent)
    {
        parent = new_parent;
        return new_parent;
    }

    Node* addChild(Node* new_child)
    {
        if (new_child == nullptr) { return nullptr; }
        children.push_back(new_child);
        new_child->parent = this;
        return new_child;
    }

    Node* findNode(const char* path)
    {
        return nullptr;
    }

protected:
    Node* parent;
    std::vector<Node*> children;
};
