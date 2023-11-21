#pragma once
#include <cmath>

template <typename T>
struct vec2 {
    T x = 0;
    T y = 0;

    // Defaults
    static const vec2 ZERO;
    static const vec2 ONE;
    static const vec2 UP;
    static const vec2 RIGHT;
    static const vec2 DOWN;
    static const vec2 LEFT;

    // Vec2 to Vec2 Simple Math
    vec2<T> operator+(const vec2<T> &other) const { return vec2{x + other.x, y + other.y}; }
    vec2<T> operator-(const vec2<T> &other) const { return vec2{x - other.x, y - other.y}; }
    vec2<T> operator*(const vec2<T> &other) const { return vec2{x * other.x, y * other.y}; }
    vec2<T> operator/(const vec2<T> &other) const { return vec2{x / other.x, y / other.y}; }

    // Vec2 to Single Simple Math
    vec2<T> operator+(const T &other) const { return vec2{x + other, y + other}; }
    vec2<T> operator-(const T &other) const { return vec2{x - other, y - other}; }
    vec2<T> operator*(const T &other) const { return vec2{x * other, y * other}; }
    vec2<T> operator/(const T &other) const { return vec2{x / other, y / other}; }

    // Vec2 to Vec2 Assignments
    void operator=(const vec2<T> &other) { x = other.x; y = other.y; }
    void operator+=(const vec2<T> &other) { x += other.x; y += other.y; }
    void operator-=(const vec2<T> &other) { x -= other.x; y -= other.y; }
    void operator*=(const vec2<T> &other) { x *= other.x; y *= other.y; }
    void operator/=(const vec2<T> &other) { x /= other.x; y /= other.y; }

    // Vec2 to Single Assignments
    void operator=(const T &other) { x = other; y = other; }
    void operator+=(const T &other) { x += other; y += other; }
    void operator-=(const T &other) { x -= other; y -= other; }
    void operator*=(const T &other) { x *= other; y *= other; }
    void operator/=(const T &other) { x /= other; y /= other; }

    // Vector Length
    float len() const { return std::sqrt(std::pow(x, (T)2) + std::pow(y, (T)2)); }
    static float len(const vec2<T> &vector) { return std::sqrt(std::pow(vector.x, (T)2) + std::pow(vector.y, (T)2)); }

    // Dot Product
    float dot(const vec2<T> &other) const { return (x * other.x) + (y * other.y); }
    static float dot(const vec2<T> &vec_a, const vec2<T> &vec_b) { return (vec_a.x * vec_b.x) + (vec_a.y * vec_b.y); }

    // Rotate
    void rotate(const float &rad_angle) {
        float cos = std::cos(rad_angle);
        float sin = std::sin(rad_angle);
        float x_prime = (x * cos) - (y * sin);
        float y_prime = (y * sin) + (x * cos);
        x = x_prime;
        y = y_prime;
    }
    static vec2<T> rotate(const vec2<T> &vector, const float &radians) {
        auto x_prime = vector.x * std::cos(radians) - vector.y * std::sin(radians);
        auto y_prime = vector.y * std::sin(radians) + vector.x * std::cos(radians);
        return vec2<T>{x_prime, y_prime};
    }

};

template <typename T>
const vec2<T> vec2<T>::ZERO = vec2<T>{0, 0};

template <typename T>
const vec2<T> vec2<T>::ONE = vec2<T>{1, 1};

template <typename T>
const vec2<T> vec2<T>::UP = vec2<T>{0, -1};

template <typename T>
const vec2<T> vec2<T>::RIGHT = vec2<T>{1, 0};

template <typename T>
const vec2<T> vec2<T>::DOWN = vec2<T>{0, 1};

template <typename T>
const vec2<T> vec2<T>::LEFT = vec2<T>{-1, 0};
