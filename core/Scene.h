#pragma once

#include <Object.h>
#include <Force.h>
#include <deque>
#include <mutex>

class Scene {
public:
    inline void addObject(ObjectPtr obj) {
        objects_.push_back(obj);
    }

    inline void addForce(ForcePtr f) {
        forces_.push_back(f);
    }

    inline const std::deque<ObjectPtr>& objects() const {
        return objects_;
    }

    inline const std::deque<ForcePtr>& forces() const {
        return forces_;
    }

    inline std::mutex& mtx() const {
        return mtx_;
    }

private:
    std::deque<ObjectPtr> objects_;
    std::deque<ForcePtr> forces_;
    mutable std::mutex mtx_;
};

using ScenePtr = std::shared_ptr<Scene>;
