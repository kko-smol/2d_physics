#pragma once

#include <math.h>
#include <iostream>

class Vec2 {
public:
    Vec2(): x_(0), y_(0) {}
    Vec2(double x, double y): x_(x), y_(y) {}
    inline double x() const {
        return x_;
    }

    inline double y() const {
        return y_;
    }

    inline Vec2 mulElementWise(const Vec2& a) const {
        return {x() * a.x(), y() * a.y()};
    }

    inline double mulScalar(const Vec2& a) const {
        return x() * a.x() + y() * a.y();
    }

    double length() const {
        return std::sqrt(x() * x() + y() * y());
    }

    inline Vec2 normalize() const {
        auto len = length();
        if (len > 0) {
            return {x() / len, y() / len};
        } else {
            return {0.0, 0.0};
        }
    }

    inline double mulVec(const Vec2& b) {
        return x() * b.y() - y() * b.x();
    }

    inline Vec2 normal() const {
        return {-y(), x()};
    }

private:
    double x_;
    double y_;
};

inline Vec2 operator+(const Vec2& a, double b) {
    return Vec2(a.x() + b, a.y() + b);
}

inline Vec2 operator-(const Vec2& a, double b) {
    return Vec2(a.x() - b, a.y() + b);
}

inline Vec2 operator+(const Vec2& a, const Vec2& b) {
    return Vec2(a.x() + b.x(), a.y() + b.y());
}

inline Vec2 operator-(const Vec2& a, const Vec2& b) {
    return Vec2(a.x() - b.x(), a.y() - b.y());
}

inline Vec2 operator*(const Vec2& a, double b) {
    return Vec2(a.x() * b, a.y() * b);
}

inline Vec2 operator/(const Vec2& a, double b) {
    return Vec2(a.x() / b, a.y() / b);
}

inline std::ostream& operator<<(std::ostream& str, const Vec2& vec) {
    str << "(" << vec.x() << ", " << vec.y() << ")";
    return str;
}