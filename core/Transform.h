#pragma once

#include <memory>

#include <Types.h>

class Transform {
public:
    Transform();
    virtual const Vec2 translate() const;
    virtual void setPos(const Vec2& p) = 0;
    virtual Vec2 dof() = 0;

protected:
    Vec2 translate_;
};

using TransformPtr = std::shared_ptr<Transform>;

class FixedTransform: public Transform {
public:
    FixedTransform(const Vec2& pos);

    void setPos(const Vec2& p) override;
    Vec2 dof() override;
};

class FreeTransform: public Transform {
public:
    FreeTransform(const Vec2& pos);

    void setPos(const Vec2& p) override;
    Vec2 dof() override;
};
