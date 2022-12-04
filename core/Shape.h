#pragma once

#include <memory>
#include <Types.h>

class Shape {
public:
    enum ShapeType {
        Sphere = 0,
        Box,

        MaxShapeType
    };

    Shape(ShapeType type);

    inline const ShapeType type() const {
        return type_;
    }

private:
    ShapeType type_;
};

using ShapePtr = std::shared_ptr<Shape>;

class Box: public Shape {
public:
    Box(double w, double h): Shape(ShapeType::Box), w_(w), h_(h) {}

    inline double width() const {
        return w_;
    }

    inline double height() const {
        return h_;
    }

private:
    double w_;
    double h_;
};

class Sphere: public Shape {
public:
    Sphere(double r):Shape(ShapeType::Sphere), r_(r) {}

    inline double radius() const {
        return r_;
    }

private:
    double r_;
};