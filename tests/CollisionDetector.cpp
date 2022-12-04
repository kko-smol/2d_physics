#include <gtest/gtest.h>

#include <CollisionDetector.h>

TEST(NoCollision, Box2BoxStatic) {
  CollisionDetector cd;

    auto box1 = std::make_shared<Object>(
        std::make_shared<Box>(2.0, 2.0),
        std::make_shared<FreeTransform>(Vec2{0.0, 0.0}),
        Vec2(0.0, 0.0), 1.0);

    auto box2 = std::make_shared<Object>(
        std::make_shared<Box>(6.0, 2.0),
        std::make_shared<FreeTransform>(Vec2{0.0, 0.0}),
        Vec2(0.0, 0.0), 1.0);

    Vec2 pointsToCheck[16] = {
        {-1.0, 2.0}, {0.0, 2.0}, {1.0, 2.0},
        {-1.0, -2.0}, {0.0, -2.0}, {1.0, -2.0},
        {-4.0, 2.0}, {-4.0, 1.0}, {-4.0, 0.0},{-4.0, -1.0}, {-4.0,-2.0},
        {4.0, 2.0}, {4.0, 1.0}, {4.0, 0.0}, {4.0, -1.0}, {4.0,-2.0}
    };
    for (int i = 0; i < 16; ++i) {
        box1->transform()->setPos(pointsToCheck[i]);
    
        auto r = cd.detect(box1, box1->pos(), box2, box2->pos());

        ASSERT_FALSE(r.valid());
    }
}

TEST(Collision, Box2BoxStatic) {
  CollisionDetector cd;

    auto box1 = std::make_shared<Object>(
        std::make_shared<Box>(2.0, 2.0),
        std::make_shared<FreeTransform>(Vec2{0.0, 0.0}),
        Vec2(0.0, 0.0), 1.0);

    auto box2 = std::make_shared<Object>(
        std::make_shared<Box>(6.0, 2.0),
        std::make_shared<FreeTransform>(Vec2{0.0, 0.0}),
        Vec2(0.0, 0.0), 1.0);

    Vec2 pointsToCheck[16] = {
        {-1.0, 1.9}, {0.0, 1.9}, {1.0, 1.9},
        {-1.0, -1.9}, {0.0, -1.9}, {1.0, -1.9},
        {-3.9, 2.0}, {-3.9, 1.0}, {-3.9, 0.0},{-3.9, -1.0}, {-3.9,-2.0},
        {3.9, 2.0}, {3.9, 1.0}, {3.9, 0.0}, {3.9, -1.0}, {3.9,-2.0}
    };
    for (int i = 0; i < 16; ++i) {
        box1->transform()->setPos(pointsToCheck[i]);
    
        auto r = cd.detect(box1, box1->pos(), box2, box2->pos());

        ASSERT_TRUE(r.valid()) << i;
    }
}
