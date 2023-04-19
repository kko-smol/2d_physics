#include <gtest/gtest.h>

#include <SimpleSim.h>
#include <Force.h>

static const double epsilon = 0.0001;

TEST(ConstSpeed, BoxMoving) {
    for (double dt = 0.0001; dt < 0.1; dt *= 10.0) {
        double x_vel = 1.0;
        double y_vel = 2.0;
        auto box1 = std::make_shared<Object>(
        std::make_shared<Box>(1.0, 1.0),
        std::make_shared<FreeTransform>(Vec2{0.0, 0.0}),
        Vec2(x_vel, y_vel), 1.0);

        SimpleSim sim;

        auto world = std::make_shared<Scene>();
        world->addObject(box1);

        for (int i = 0; i < 1000; ++i) {
            sim.step(world, dt);
            EXPECT_NEAR(box1->pos().x(), dt*(i+1)*x_vel, epsilon);
            EXPECT_NEAR(box1->pos().y(), dt*(i+1)*y_vel, epsilon);
        }
    }
}

TEST(ConstForce, BoxMoving) {
    for (double dt = 0.0001; dt < 0.1; dt *= 10.0) {
        auto box1 = std::make_shared<Object>(
        std::make_shared<Box>(1.0, 1.0),
        std::make_shared<FreeTransform>(Vec2{0.0, 0.0}),
        Vec2(0.0, 0.0), 1.0);

        double force = 1.0;

        SimpleSim sim;

        auto world = std::make_shared<Scene>();
        world->addForce(std::make_shared<SimpleGravity>(Vec2{force, force}));
        world->addObject(box1);

        for (int i = 0; i < 1000; ++i) {
            sim.step(world, dt);
            double t = dt * (i + 1);

            EXPECT_NEAR(box1->speed().x(), force * t, epsilon);
            EXPECT_NEAR(box1->speed().y(), force * t, epsilon);
            EXPECT_NEAR(box1->pos().x(), force * t * t / 2.0, epsilon);
            EXPECT_NEAR(box1->pos().y(), force * t * t / 2.0, epsilon);
        }
    }
}


TEST(ConstForce, BoxFixed) {
    for (double dt = 0.0001; dt < 0.1; dt *= 10.0) {
        auto box1 = std::make_shared<Object>(
        std::make_shared<Box>(1.0, 1.0),
        std::make_shared<FixedTransform>(Vec2{0.0, 0.0}),
        Vec2(0.0, 0.0), 1.0);

        double force = 1.0;

        SimpleSim sim;

        auto world = std::make_shared<Scene>();
        world->addForce(std::make_shared<SimpleGravity>(Vec2{force, force}));
        world->addObject(box1);

        for (int i = 0; i < 1000; ++i) {
            sim.step(world, dt);
            double t = dt * (i + 1);

            EXPECT_NEAR(box1->speed().x(), 0.0, epsilon);
            EXPECT_NEAR(box1->speed().y(), 0.0, epsilon);
            EXPECT_NEAR(box1->pos().x(), 0.0, epsilon);
            EXPECT_NEAR(box1->pos().y(), 0.0, epsilon);
        }
    }
}

TEST(ForceAddition, BoxMoving) {
    for (double dt = 0.0001; dt < 0.1; dt *= 10.0) {
        auto box1 = std::make_shared<Object>(
        std::make_shared<Box>(1.0, 1.0),
        std::make_shared<FreeTransform>(Vec2{0.0, 0.0}),
        Vec2(0.0, 0.0), 1.0);

        double force = 1.0;

        SimpleSim sim;

        auto world = std::make_shared<Scene>();
        world->addForce(std::make_shared<SimpleGravity>(Vec2{force, force}));
        world->addForce(std::make_shared<SimpleGravity>(Vec2{-force, -force}));
        world->addObject(box1);

        for (int i = 0; i < 1000; ++i) {
            sim.step(world, dt);
            double t = dt * (i + 1);

            EXPECT_NEAR(box1->speed().x(), 0.0, epsilon);
            EXPECT_NEAR(box1->speed().y(), 0.0, epsilon);
            EXPECT_NEAR(box1->pos().x(), 0.0, epsilon);
            EXPECT_NEAR(box1->pos().y(), 0.0, epsilon);
        }
    }
}