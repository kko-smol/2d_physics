#include <Force.h>
#include <cassert>

SimpleGravity::SimpleGravity(const Vec2 &g) : force_(g) {}

Vec2 SimpleGravity::getForce(const Object *obj) const {
    return force_ * obj->mass();
}

SimpleFriction::SimpleFriction(double friction) : friction_(friction) {
    assert(friction >= 0.0);
    assert(friction < 1.0);
}

Vec2 SimpleFriction::getForce(const Object *obj) const {
    return obj->speed().normalize() * (-friction_);
}
