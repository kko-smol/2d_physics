#include <Transform.h>
#include <Shape.h>
#include <Force.h>
#include <Scene.h>
#include <Object.h>
#include <SimpleSim.h>
#include <CliUI.h>
#include <NanaGui.h>
#include <thread>
#include <iostream>

int main(int argc, char** argv) {

    CliUI ui;
    SimpleSim sim;

    auto world = std::make_shared<Scene>();

    auto boxl = std::make_shared<Object>(
        std::make_shared<Box>(1.0, 5.0),
        std::make_shared<FixedTransform>(Vec2{3.1, 2.5}),
        Vec2(0.0, 0.0), 1.0);

    auto boxr = std::make_shared<Object>(
        std::make_shared<Box>(1.0, 5.0),
        std::make_shared<FixedTransform>(Vec2{-3.1, 2.5}),
        Vec2(0.0, 0.0), 1.0);

    auto boxb = std::make_shared<Object>(
        std::make_shared<Box>(5.0, 1.0),
        std::make_shared<FixedTransform>(Vec2{0.0, 0.0}),
        Vec2(0.0, 0.0), 1.0);

    auto boxf = std::make_shared<Object>(
        std::make_shared<Box>(1.0, 1.0),
        std::make_shared<FreeTransform>(Vec2{0.0, 4.0}),
        Vec2(5.0, 0.0), 2.0);

    auto sphere0 = std::make_shared<Object>(
        std::make_shared<Sphere>(0.5),
        std::make_shared<FreeTransform>(Vec2{-2.0, 3.0}),
        Vec2(3.0, 0.0), 1.0);
    
    auto sphere1 = std::make_shared<Object>(
        std::make_shared<Sphere>(0.5),
        std::make_shared<FreeTransform>(Vec2{1.0, 4.0}),
        Vec2(1.0, 0.0), 10.0);

    world->addForce(std::make_shared<SimpleGravity>(Vec2{0, -9.8}));
    world->addObject(boxl);
    world->addObject(boxr);
    world->addObject(boxb);
//    world->addObject(boxf);

    world->addObject(sphere0);
    world->addObject(sphere1);

    NanaSceneDraw gui(world.get(), 300, 300);

    std::thread sim_thread([&]() {
        double t = 0.0;
        double dt = 0.001;
        while (true) {
            sim.step(world, dt);
            t += dt;
            ui.draw(t, world.get());
            std::this_thread::sleep_for(std::chrono::duration<double>(dt));
        }
    });

    gui.start();

    return 0;
}