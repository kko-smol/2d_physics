#include <Transform.h>

Transform::Transform():translate_(0.0, 0.0) {}

const Vec2 Transform::translate() const {
    return translate_;
}

FixedTransform::FixedTransform(const Vec2& pos) {
    translate_ = pos;
}

void FixedTransform::setPos(const Vec2& p) {}

FreeTransform::FreeTransform(const Vec2& pos) {
    translate_ = pos;
}

void FreeTransform::setPos(const Vec2& p) {
    translate_ = p;

}

Vec2 FreeTransform::dof() {
    return {1.0, 1.0};
}

Vec2 FixedTransform::dof() {
    return {0.0, 0.0};
}

