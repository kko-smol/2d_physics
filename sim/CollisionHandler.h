#pragma once

#include <Object.h>
#include <CollisionDescription.h>

class CollisionHandler {
public:
    void handleCollision(ObjectPtr o1, Vec2& o1_speed, Vec2& o1_pos,
                         ObjectPtr o2, Vec2& o2_speed, Vec2& o2_pos,
                         const CollisionDescriprtion& col);
};