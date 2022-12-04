#pragma once

#include <Types.h>
#include <Object.h>
#include <CollisionDescription.h>

class CollisionDetector {
public:
    CollisionDescriprtion detect(ObjectPtr o1, Vec2 new_o1_pos,
                                 ObjectPtr o2, Vec2 new_o2_pos);
};