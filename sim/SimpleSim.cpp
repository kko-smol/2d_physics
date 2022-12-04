#include <SimpleSim.h>
#include <map>
#include <CollisionDetector.h>
#include <CollisionHandler.h>

void SimpleSim::step(ScenePtr scene, double dt) {
    std::map<ObjectPtr, Vec2> new_speeds;
    std::map<ObjectPtr, Vec2> new_positions;

    for (auto f = scene->forces().cbegin(); f != scene->forces().cend(); ++f) {
        for (auto o = scene->objects().cbegin(); o != scene->objects().cend(); ++o) {
            auto force = (*f)->getForce(o->get()).mulElementWise((*o)->transform()->dof());

            auto new_speed = (*o)->speed() + force * dt / (*o)->mass();
            auto new_pos = (*o)->pos() + ((*o)->speed() + new_speed) * dt / 2;

            new_speeds.insert({*o, new_speed});
            new_positions.insert({*o, new_pos});
        }
    }

    CollisionDetector collisionDetector;
    CollisionHandler collisionHandler;
    for (auto o1 = scene->objects().cbegin(); o1 != scene->objects().cend(); ++o1) {
        for (auto o2 = o1 + 1; o2 != scene->objects().cend(); ++o2) {
            auto collision = collisionDetector.detect(*o1, new_positions[*o1],
                                                      *o2, new_positions[*o2]);
            if (collision.valid()) {
                collisionHandler.handleCollision(
                    *o1, new_speeds[*o1], new_positions[*o1],
                    *o2, new_speeds[*o2], new_positions[*o2], collision);
            }
        }
    }

    {
        std::unique_lock<std::mutex> lck(scene->mtx());
        for (auto o = scene->objects().cbegin(); o != scene->objects().cend(); ++o) {
            (*o)->setSpeed(new_speeds[*o]);
            (*o)->transform()->setPos(new_positions[*o]);
        }
    }

}