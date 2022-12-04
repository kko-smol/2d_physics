#include <Object.h>

Object::Object(ShapePtr shape, TransformPtr transform,
               const Vec2 &speed, double mass) :
    shape_(shape), transform_(transform),
    speed_(speed), mass_(mass) {}

TransformPtr Object::transform() const {
    return transform_;
}

ShapePtr Object::shape() const {
    return shape_;
}

Vec2 Object::pos() const {
    return transform_->translate();
}

Vec2 Object::speed() const {
    return speed_;
}

void Object::setSpeed(const Vec2 &speed) {
    speed_ = speed;
}

double Object::mass() const {
    return mass_;
}
