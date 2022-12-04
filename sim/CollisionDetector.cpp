#include <CollisionDetector.h>
#include <Shape.h>
#include <functional>
#include <cassert>

#include <iostream>

std::pair<Vec2, Vec2> point2SegmentDistance(const Vec2& p0, const Vec2& p1, const Vec2& point) {
    auto obj_vec = point - p0;
    auto side_vec = p1 - p0;
    double scalarProd = obj_vec.mulScalar(side_vec) / (side_vec.length() * side_vec.length());
    scalarProd = std::max(0.0, std::min(1.0, scalarProd));
    Vec2 collisionPoint = p0 + side_vec * scalarProd;
    return {(point - collisionPoint), collisionPoint};
}

static CollisionDescriprtion detectBox2Box(ObjectPtr o1, Vec2 new_o1_pos,
                                           ObjectPtr o2, Vec2 new_o2_pos) {
    assert(o1->shape()->type() == Shape::ShapeType::Box);
    assert(o2->shape()->type() == Shape::ShapeType::Box);
    Box* box1 = reinterpret_cast<Box*>(o1->shape().get());
    Box* box2 = reinterpret_cast<Box*>(o2->shape().get());
    CollisionDescriprtion res;

    auto getPoint = [&](Box* box, bool old, int idx) -> Vec2 {
        assert(idx >= 0);
        assert(idx < 4);
        auto pos = old ? (box == box1 ? o1->pos() : o2->pos()) : (box == box1 ? new_o1_pos : new_o2_pos);
        auto w2 = box->width() / 2;
        auto h2 = box->height() / 2;
        Vec2 signs[4] = {{-1, 1},{-1, -1}, {1, -1}, {1, 1}};
        return pos + Vec2(w2, h2).mulElementWise(signs[idx]);
    };

    for (int other_box_vertex = 0; other_box_vertex < 4; ++other_box_vertex) {
        auto p1 = getPoint(box2, false, other_box_vertex);
        auto p2 = getPoint(box2, true, other_box_vertex);

        double prevVecProds[4];
        double newVecProds[4];

        for (int box_side = 0; box_side < 4; ++box_side) {
            auto s0 = getPoint(box1, false, box_side);
            auto s1 = getPoint(box1, false, (box_side + 1) % 4);
            auto s = s1 - s0;
            prevVecProds[box_side] = s.mulVec(p1 - s0);
            newVecProds[box_side] = s.mulVec(p2 - s0);
        }

        if ((newVecProds[0] > 0) && (newVecProds[1] > 0) && (newVecProds[2] > 0) && (newVecProds[3] > 0)) {
            for (int collision_side = 0; collision_side < 4; ++collision_side) {
                if (prevVecProds[collision_side] * newVecProds[collision_side] < 0) {
                    auto s0 = getPoint(box1, false, collision_side);
                    auto s1 = getPoint(box1, false, (collision_side + 1) % 4);
                    auto s = s1 - s0;
                    res.points.push_back(p2);
                    res.normals.push_back(s.normal().normalize());
                }
            }
        }
    }

    for (int other_box_vertex = 0; other_box_vertex < 4; ++other_box_vertex) {    
        auto p1 = getPoint(box1, false, other_box_vertex);
        auto p2 = getPoint(box1, true, other_box_vertex);
    
        double prevVecProds[4];
        double newVecProds[4];

        for (int box_side = 0; box_side < 4; ++box_side) {
            auto s0 = getPoint(box2, false, box_side);
            auto s1 = getPoint(box2, false, (box_side + 1) % 4);
            auto s = s1 - s0;
            prevVecProds[box_side] = s.mulVec(p1-s0);
            newVecProds[box_side] = s.mulVec(p2-s0);
        }

        if ((newVecProds[0] > 0) && (newVecProds[1] > 0) && (newVecProds[2] > 0) && (newVecProds[3] > 0)) {
            for (int collision_side = 0; collision_side < 4; ++collision_side) {
                if (prevVecProds[collision_side] * newVecProds[collision_side] < 0) {
                    auto s0 = getPoint(box2, false, collision_side);
                    auto s1 = getPoint(box2, false, (collision_side + 1) % 4);
                    auto s = s1 - s0;
                    res.points.push_back(p2);
                    res.normals.push_back(s.normal().normalize());
                }
            }
        }
    }

    return res;
}

static CollisionDescriprtion detectSphere2Sphere(ObjectPtr o1, Vec2 new_o1_pos,
                                                ObjectPtr o2, Vec2 new_o2_pos) {
    assert(o1->shape()->type() == Shape::ShapeType::Sphere);
    assert(o2->shape()->type() == Shape::ShapeType::Sphere);
    Sphere* s1 = reinterpret_cast<Sphere*>(o1->shape().get());
    Sphere* s2 = reinterpret_cast<Sphere*>(o2->shape().get());

    CollisionDescriprtion res;

    Vec2 d = new_o2_pos - new_o1_pos;
    if (d.length() < (s1->radius() + s2->radius())) {
        auto n = d.normalize();
        res.normals.push_back(n);
        res.points.push_back((new_o1_pos + n * s1->radius() + new_o2_pos - n * s2->radius()) * 0.5);
    }

    return res;
}

static CollisionDescriprtion detectSphere2Box(ObjectPtr o1, Vec2 new_o1_pos,
                                             ObjectPtr o2, Vec2 new_o2_pos) {
    assert(o1->shape()->type() == Shape::ShapeType::Sphere);
    assert(o2->shape()->type() == Shape::ShapeType::Box);

    CollisionDescriprtion res;

    Sphere* spehre = reinterpret_cast<Sphere*>(o1->shape().get());
    Box* box = reinterpret_cast<Box*>(o2->shape().get());

    Vec2 points[4] = {new_o2_pos + Vec2(-box->width(), -box->height()) * 0.5,
                      new_o2_pos + Vec2(-box->width(), box->height()) * 0.5,
                      new_o2_pos + Vec2(box->width(), box->height()) * 0.5,
                      new_o2_pos + Vec2(box->width(), -box->height()) * 0.5};

    for (int i = 0; i < 4; ++i) {
        auto cpAndDist = point2SegmentDistance(points[i], points[(i + 1) % 4], new_o1_pos);
        auto collisionPoint = cpAndDist.second;
        double distance = cpAndDist.first.length() - spehre->radius();

        if (distance < 0.0) {
            res.points.push_back(collisionPoint);
            res.normals.push_back((new_o1_pos - collisionPoint).normalize());
            return res;
        }
    }

    return res;
}

CollisionDescriprtion CollisionDetector::detect(ObjectPtr o1, Vec2 new_o1_pos,
                                                      ObjectPtr o2, Vec2 new_o2_pos) {
static_assert(Shape::ShapeType::MaxShapeType == 2);
using namespace std::placeholders;
static std::function<CollisionDescriprtion(ObjectPtr, Vec2, ObjectPtr, Vec2)>
    detectors[Shape::ShapeType::MaxShapeType][Shape::ShapeType::MaxShapeType] = {
        {detectSphere2Sphere, detectSphere2Box},
        {std::bind(detectSphere2Box,_3, _4, _1, _2), detectBox2Box}
    };
    return detectors[o1->shape()->type()][o2->shape()->type()](o1, new_o1_pos, o2, new_o2_pos);
}

