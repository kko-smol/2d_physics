#pragma once

#include <Types.h>
#include <Object.h>
#include <memory>

class Force {
public:
    virtual Vec2 getForce(const Object *obj) const = 0;
};

using ForcePtr = std::shared_ptr<Force>;

class SimpleGravity : public Force {
public:
    SimpleGravity(const Vec2 &g);

    Vec2 getForce(const Object *obj) const override;

private:
    Vec2 force_;
};