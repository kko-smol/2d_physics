#include <NanaGui.h>
#include <nana/gui.hpp>
#include <nana/gui/timer.hpp>
#include <cassert>

#include <X11/Xlib.h>

#include "../gui/nana/source/detail/platform_spec_selector.hpp"

struct NanaCtx {
    NanaCtx(int w, int h):width(w), height(h), fm(nana::API::make_center(w, h)), dw(fm) {}
    int width;
    int height;
    nana::form fm;
    nana::drawing dw;
    nana::timer t1;

    Vec2 view_point;
    double scale;
};


void circle(nana::paint::graphics& gc, int x, int y, int r, const nana::color& clr) {
	gc.palette(false, clr);
#if defined(NANA_WINDOWS)
    assert(false);  /* not implemented for Windows*/
#elif defined(NANA_X11)
	Display* disp = nana::detail::platform_spec::instance().open_display();
    gc.handle()->update_color();
    XFillArc(disp, reinterpret_cast<Drawable>(gc.pixmap()),
    reinterpret_cast<GC>(const_cast<void*>(gc.context())),
    x, y,
    r * 2, r * 2,
    0, 360*64);

#endif

	gc.set_changed();
}

NanaSceneDraw::NanaSceneDraw(const Scene* scene, int w, int h): scene_(scene),
    ctx_(std::make_unique<NanaCtx>(w, h)) {

    ctx_->view_point = {static_cast<double>(w / 2) , static_cast<double>(h / 2)};
    ctx_->scale = 20.0;

    ctx_->dw.draw([this](nana::paint::graphics& graph) {
        std::unique_lock<std::mutex> lck(scene_->mtx());

        for (auto i = scene_->objects().cbegin(); i != scene_->objects().cend(); ++i) {
            switch ((*i)->shape()->type()) {
            case Shape::ShapeType::Sphere: {
                Sphere* sphere = static_cast<Sphere*>((*i)->shape().get());

                Vec2 pos = ((*i)->pos() - sphere->radius()).mulElementWise({1.0, -1.0}) * ctx_->scale + ctx_->view_point;
                circle(graph, pos.x(), pos.y(), sphere->radius() * ctx_->scale, nana::colors::red);
                break;
            }
            case Shape::ShapeType::Box: {
                Box* box = static_cast<Box*>((*i)->shape().get());

                Vec2 pos = ((*i)->pos() - Vec2(box->width() / 2, -box->height() / 2))
                    .mulElementWise({1.0, -1.0}) * ctx_->scale + ctx_->view_point;
                graph.rectangle(
                    nana::rectangle{static_cast<int>(pos.x()), static_cast<int>(pos.y()),
                    static_cast<uint>(box->width() * ctx_->scale), static_cast<uint>(box->height() * ctx_->scale)},
                    true, nana::colors::red);
                break;
            }
            default:
                assert(false); // unknown shape
            }
        }
    });

    ctx_->t1.interval(std::chrono::milliseconds(1000/60));
    ctx_->t1.elapse([this](){
        ctx_->dw.update();
    });
    ctx_->t1.start();

    ctx_->dw.update();
    ctx_->fm.show();

}

void NanaSceneDraw::start() {
    ::nana::exec();
}