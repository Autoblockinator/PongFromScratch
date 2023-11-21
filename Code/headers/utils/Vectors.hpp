#pragma once

template <typename T>
struct vec2 {
    T x = 0;
    T y = 0;

    vec2<T> operator+(const vec2<T> &other) const { return vec2{x+other.x, y+other.y}; }
    vec2<T> operator-(const vec2<T> &other) const { return vec2{x-other.x, y-other.y}; }
    vec2<T> operator*(const vec2<T> &other) const { return vec2{x*other.x, y*other.y}; }
    vec2<T> operator/(const vec2<T> &other) const { return vec2{x/other.x, y/other.y}; }

    void operator+=(const vec2<T> &other) { x += other.x; y += other.y; }
    void operator-=(const vec2<T> &other) { x -= other.x; y -= other.y; }
    void operator*=(const vec2<T> &other) { x *= other.x; y *= other.y; }
    void operator/=(const vec2<T> &other) { x /= other.x; y /= other.y; }

    vec2<T> operator+(const vec2<T> &other) const { return vec2{x+other.x, y+other.y}; }
    vec2<T> operator-(const vec2<T> &other) const { return vec2{x-other.x, y-other.y}; }
    vec2<T> operator*(const vec2<T> &other) const { return vec2{x*other.x, y*other.y}; }
    vec2<T> operator/(const vec2<T> &other) const { return vec2{x/other.x, y/other.y}; }

};
