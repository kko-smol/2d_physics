#pragma once

#include <Scene.h>

class NanaSceneDraw {
public:
    NanaSceneDraw(const Scene* scene, int w, int h);

    void start();
private:
    const Scene* scene_;
    std::shared_ptr<struct NanaCtx> ctx_;
};