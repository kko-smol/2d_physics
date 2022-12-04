#include <CliUI.h>

void CliUI::draw(double t, const Scene* scene) {
    std::unique_lock<std::mutex> lck(scene->mtx());
    std::cout << "Sim time: " << t << "\n";

    for (auto i = scene->objects().cbegin(); i != scene->objects().cend(); ++i) {
        std::cout << "Object type:" << (*i)->shape()->type() 
                  << " mass" << (*i)->mass()
                  << " at " << (*i)->pos()
                  << " speed: " << (*i)->speed() << "\n";
    }

    std::cout << "\n";
}