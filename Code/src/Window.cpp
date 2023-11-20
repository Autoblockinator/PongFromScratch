#pragma once
#include "Utils/All.h"
#include "Node.cpp"

class I_Window:
    public NodeRef<Node>
{

};

class Window:
    public Node
{
public:
    sf::RenderWindow rw{{1920, 1080}, "Window"};

    Window() {}
    
    Window(const string &title) { rw.setTitle(title); }

    Vector<int> getPosition() { return {rw.getPosition().x, rw.getPosition().y}; }
    void setPosition(const Vector<int> &position) { rw.setPosition({position.x, position.y}); }

};
