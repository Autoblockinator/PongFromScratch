#pragma once
#include "Basic.h"

template <typename T>
class Vector {
public:
    T x{0}, y{0};

    Vector() {}

    Vector(T size): x(size), y(size) {}

    Vector(T x, T y): x(x), y(y) {}

    Vector<T> operator+(Vector<T>& other) { return Vector<T>{x+other.x, y+other.y}; }
    Vector<T> operator-(Vector<T>& other) { return Vector<T>{x-other.x, y-other.y}; }
    Vector<T> operator*(Vector<T>& other) { return Vector<T>{x*other.x, y*other.y}; }
    Vector<T> operator/(Vector<T>& other) { return Vector<T>{x/other.x, y/other.y}; }
};
