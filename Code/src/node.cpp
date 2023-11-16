#pragma once
#include <iostream>
#include <vector>

class Node
{
public:
    Node* parent;
    std::vector<Node*> children;

    Node()
    {
        parent = nullptr;
        children = std::vector<Node*>();
        std::cout << "Constructor Called" << std::endl;
    }

    Node* add_child(Node* new_child)
    {
        if (new_child == nullptr) { return nullptr; }

        children.push_back(new_child);
        return new_child;
    }

    Node* find_node(const char* path)
    {
        return nullptr;
    }
};
