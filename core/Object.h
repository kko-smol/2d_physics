#pragma once
#include <vector>
#include <memory>

#include <Transform.h>
#include <Shape.h>

class Object {
public:
    Object(ShapePtr shape, TransformPtr transform, const Vec2& speed, double mass);

    TransformPtr transform() const;
    ShapePtr shape() const;

    virtual Vec2 pos() const;

    virtual Vec2 speed() const;
    virtual void setSpeed(const Vec2&);

    virtual double mass() const;
private:
    ShapePtr shape_;
    TransformPtr transform_;
    Vec2 speed_;
    double mass_;
};

using ObjectPtr = std::shared_ptr<Object>;
