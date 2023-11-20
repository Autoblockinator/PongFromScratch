#pragma once
#include "Utils/All.h"

class Shadow_NodeRef {
public:
    virtual void invalidate() = 0;
};

class Node {
public:
    Node() { setName(name); }

    Node(string &name) { setName(name); }

    ~Node() {
        removeFromParentChildList();
        for (auto child: children) { free(child); }
        for (auto ref: references) { ref->invalidate(); }
    }

    void update(const float &delta) { for (auto child: children) { child->update(delta); } }

    void referenced(Shadow_NodeRef* ref) { references.push_back(ref); }

    void referenceFreed(Shadow_NodeRef* ref) {
        for (int i = 0; i < references.size(); i++) {
            if (references[i] == ref) { references.erase(references.begin() + i); break; }
        }
    }

    string getName() { return name; }
    void setName(string &name) { this->name = name; }

    Node* getRoot() {
        auto current = this;
        while (true) {
            if (current->root != nullptr) { current = current->root; break; }
            if (current->parent != nullptr) { current = current->parent; }
            break;
        }
        root = current;
        return root;
    }
    Node* findRoot() { root = nullptr; return getRoot(); }

    Node* getChild(int &child) { return children[child]; }
    Node* getChild(const string &child) {
        for (auto i: children) {
            if (i->name == child) { return i; }
        }
        return nullptr;
    }

    // Node* findNode(const string &path) {} //TODO

    Node* getParent() { return parent; }
    void setParent(Node* parent) { removeFromParentChildList(); this->parent = parent; }

private:
    string name = "Node";
    Node* root = nullptr;
    Node* parent = nullptr;
    std::vector<Node*> children{};
    std::vector<Shadow_NodeRef*> references{};

    void removeFromParentChildList() {
        if (parent != nullptr) {
            for (int i = 0; i < parent->children.size(); i++) {
                if (parent->children[i] == this) {
                    parent->children.erase(parent->children.begin() + i);
                    break;
                }
            }
        }
    }
};

template <typename T>
class NodeRef: public Shadow_NodeRef {
public:
    NodeRef() {}

    NodeRef(T* node): ptr((Node*)node) { node->referenced(this); }

    ~NodeRef() { ptr->referenceFreed(this); }

    T* operator->() { return (T*)ptr; }

    void invalidate() { ptr = nullptr; }

private:
    Node* ptr = nullptr;

};
