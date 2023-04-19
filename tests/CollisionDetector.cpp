#include <gtest/gtest.h>

#include <CollisionDetector.h>

static double epsilon = 0.0001;

TEST(All, Sphere2SphereStatic) {
  CollisionDetector cd;

    double R = 1.0;
    auto s1 = std::make_shared<Object>(
        std::make_shared<Sphere>(R),
        std::make_shared<FreeTransform>(Vec2{0.0, 0.0}),
        Vec2(0.0, 0.0), 1.0);

    auto s2 = std::make_shared<Object>(
        std::make_shared<Sphere>(R),
        std::make_shared<FreeTransform>(Vec2{0.0, 0.0}),
        Vec2(0.0, 0.0), 1.0);

    std::pair<Vec2, bool> pointsToCheck[12] = {
        {{2*R, 0.0}, false},
        {{0.0, 2*R}, false},
        {{-2*R, 0.0}, false},
        {{0.0, -2*R}, false},
        {{2*R + epsilon, 0.0}, false},
        {{0.0, 2*R + epsilon}, false},
        {{-2*R - epsilon, 0.0}, false},
        {{0.0, -2*R - epsilon}, false},
        {{2*R - epsilon, 0.0}, true},
        {{0.0, 2*R - epsilon}, true},
        {{-2*R + epsilon, 0.0}, true},
        {{0.0, -2*R + epsilon}, true},
    };
    for (int i = 0; i < 12; ++i) {
        s1->transform()->setPos(pointsToCheck[i].first);
        auto r = cd.detect(s1, s1->pos(), s2, s2->pos());
        ASSERT_EQ(r.valid(), pointsToCheck[i].second) << i << " " << pointsToCheck[i].first << " : " << pointsToCheck[i].second;
    }
}

TEST(All, Sphere2BoxStatic) {
  CollisionDetector cd;

    double R = 1.0;
    auto s1 = std::make_shared<Object>(
        std::make_shared<Sphere>(R),
        std::make_shared<FreeTransform>(Vec2{0.0, 0.0}),
        Vec2(0.0, 0.0), 1.0);

    auto b1 = std::make_shared<Object>(
        std::make_shared<Box>(2*R, 2*R),
        std::make_shared<FreeTransform>(Vec2{0.0, 0.0}),
        Vec2(0.0, 0.0), 1.0);

    std::pair<Vec2, bool> pointsToCheck[12] = {
        {{2*R, 0.0}, false},
        {{0.0, 2*R}, false},
        {{-2*R, 0.0}, false},
        {{0.0, -2*R}, false},
        {{2*R + epsilon, 0.0}, false},
        {{0.0, 2*R + epsilon}, false},
        {{-2*R - epsilon, 0.0}, false},
        {{0.0, -2*R - epsilon}, false},
        {{2*R - epsilon, 0.0}, true},
        {{0.0, 2*R - epsilon}, true},
        {{-2*R + epsilon, 0.0}, true},
        {{0.0, -2*R + epsilon}, true},
    };
    for (int i = 0; i < 12; ++i) {
        s1->transform()->setPos(pointsToCheck[i].first);
        auto r = cd.detect(s1, s1->pos(), b1, b1->pos());
        ASSERT_EQ(r.valid(), pointsToCheck[i].second) << i << " " << pointsToCheck[i].first << " : " << pointsToCheck[i].second;
    }
}

TEST(All, Box2BoxStatic) {
  CollisionDetector cd;

    double R = 1.0;
    auto s1 = std::make_shared<Object>(
        std::make_shared<Box>(2*R, 2*R),
        std::make_shared<FreeTransform>(Vec2{0.0, 0.0}),
        Vec2(0.0, 0.0), 1.0);

    auto b1 = std::make_shared<Object>(
        std::make_shared<Box>(2*R, 2*R),
        std::make_shared<FreeTransform>(Vec2{0.0, 0.0}),
        Vec2(0.0, 0.0), 1.0);

    std::pair<Vec2, bool> pointsToCheck[12] = {
        {{2*R, 0.0}, false},
        {{0.0, 2*R}, false},
        {{-2*R, 0.0}, false},
        {{0.0, -2*R}, false},
        {{2*R + epsilon, 0.0}, false},
        {{0.0, 2*R + epsilon}, false},
        {{-2*R - epsilon, 0.0}, false},
        {{0.0, -2*R - epsilon}, false},
        {{2*R - epsilon, 0.0}, true},
        {{0.0, 2*R - epsilon}, true},
        {{-2*R + epsilon, 0.0}, true},
        {{0.0, -2*R + epsilon}, true},
    };
    for (int i = 0; i < 12; ++i) {
        s1->transform()->setPos(pointsToCheck[i].first);
        auto r = cd.detect(s1, s1->pos(), b1, b1->pos());
        ASSERT_EQ(r.valid(), pointsToCheck[i].second) << i << " " << pointsToCheck[i].first << " : " << pointsToCheck[i].second;
    }
}
