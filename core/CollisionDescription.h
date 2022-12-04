#pragma once
#include <Types.h>
#include <vector>
#include <cassert>

struct CollisionDescriprtion {
    std::vector<Vec2> points;
    std::vector<Vec2> normals;

    inline bool valid() const {
        return (normals.size() > 0) && (points.size() > 0);
    }

    Vec2 normal() const {
        assert(normals.size() > 0);
        Vec2 normal;
        for (int i = 0; i < normals.size(); ++i) {
            normal = normal + normals[i];
        }
        return normal / normals.size();
    }
};
