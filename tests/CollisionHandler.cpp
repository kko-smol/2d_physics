#include <gtest/gtest.h>

#include <CollisionHandler.h>

static double epsilon = 0.0001;

TEST(All, Sphere2FixSphere) {
  CollisionHandler ch;

    double R = 1.0;
    auto s1 = std::make_shared<Object>(
        std::make_shared<Sphere>(R),
        std::make_shared<FreeTransform>(Vec2{0.0, 0.0}),
        Vec2(0.0, 0.0), 1.0);

    auto s2 = std::make_shared<Object>(
        std::make_shared<Sphere>(R),
        std::make_shared<FixedTransform>(Vec2{0.0, 0.0}),
        Vec2(0.0, 0.0), 1.0);

    struct TestCase {
        Vec2 pos;
        Vec2 speed;
        Vec2 collision_normal;
        Vec2 collision_point;

        Vec2 expexcted_speed;
    };
    
    double sr = sqrt(2.0);
    TestCase pointsToCheck[12] = {
        {{2*R, 0.0}, {-1, 0}, {1, 0}, {R, 0}, {1, 0}},
        {{0.0, 2*R}, {0, -1}, {0, 1}, {0, R}, {0, 1}},
        {{-2*R, 0.0}, {1, 0}, {-1, 0}, {-1, 0}, {-1, 0}},
        {{0.0, -2*R}, {0, 1}, {0, -1}, {0, -1}, {0, -1}},

        {{ 2*R*sr,  2*R*sr}, {-1, -1}, { 1,  1}, {R*sr, R*sr}, {1, 1}},
        {{ 2*R*sr, -2*R*sr}, {-1,  1}, { 1, -1}, {R*sr, -R*sr}, {1, -1}},
        {{-2*R*sr,  2*R*sr}, { 1, -1}, {-1,  1}, {-R*sr, R*sr}, {-1, 1}},
        {{-2*R*sr, -2*R*sr}, { 1,  1}, {-1, -1}, {-R*sr, -R*sr}, {-1, -1}},

        {{ 2*R*sr,  2*R*sr}, {-1,  0}, { 1,  1}, {R*sr, R*sr}, {0, 1}},
        {{ 2*R*sr,  2*R*sr}, { 0, -1}, { 1,  1}, {R*sr, R*sr}, {-1, 0}},
    };
    for (int i = 0; i < 8; ++i) {
        auto tc = pointsToCheck[i];
        CollisionDescriprtion cd;
        cd.points.push_back(tc.collision_point);
        cd.normals.push_back(tc.collision_normal.normalize());
        s1->transform()->setPos(tc.pos);
        s1->setSpeed(tc.speed);

        Vec2 s2_pos = s2->pos();
        Vec2 s2_speed = s2->speed();

        ch.handleCollision(s1, tc.speed, tc.pos, s2, s2_speed, s2_pos, cd);

        EXPECT_NEAR(s2_pos.x(), s2->pos().x(), epsilon) << i;
        EXPECT_NEAR(s2_pos.y(), s2->pos().y(), epsilon) << i;
        EXPECT_NEAR(s2_speed.x(), s2->speed().x(), epsilon) << i;
        EXPECT_NEAR(s2_speed.y(), s2->speed().y(), epsilon) << i;

        EXPECT_NEAR(tc.speed.x(), tc.expexcted_speed.x(), epsilon) << i;
        EXPECT_NEAR(tc.speed.y(), tc.expexcted_speed.y(), epsilon) << i;
    }
}
