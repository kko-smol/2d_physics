#include <Force.h>

SimpleGravity::SimpleGravity(const Vec2 &g) : force_(g) {}

Vec2 SimpleGravity::getForce(const Object *obj) const
{
    return force_ * obj->mass();
}
