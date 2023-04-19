#include <CollisionHandler.h>
#include <iostream>
#include <cassert>

void CollisionHandler::handleCollision(
    ObjectPtr o1, Vec2& o1_speed, Vec2& o1_pos,
    ObjectPtr o2, Vec2& o2_speed, Vec2& o2_pos,
    const CollisionDescriprtion& col) {
    auto m1 = o1->mass();
    auto m2 = o2->mass();
    auto Esys = (o1_speed.mulElementWise(o1_speed) * m1 + o2_speed.mulElementWise(o2_speed) * m2) / 2.0;

    std::cout << "o_speeds_in" << o1_speed << "," << o2_speed << "\n";

    auto r_o1_speed = (o1_speed - col.normal() * o1_speed.mulScalar(col.normal()) * 2).mulElementWise(o1->transform()->dof());
    auto r_o2_speed = (o2_speed - col.normal() * o2_speed.mulScalar(col.normal()) * 2).mulElementWise(o2->transform()->dof());

    std::cout << "r_speeds" << r_o1_speed << "," << r_o2_speed << "\n";

    o1_speed = r_o1_speed.mulElementWise(o1->transform()->dof());
    o2_speed = r_o2_speed.mulElementWise(o2->transform()->dof());

    std::cout << "o_speedst" << o1_speed << "," << o2_speed << "\n";


    auto u1 = (o1_speed * (m1 - m2) + o2_speed * 2 * m2)/(m1 + m2);
    auto u2 = (o2_speed * (m2 - m1) + o1_speed * 2 * m1)/(m1 + m2);

    auto E1 = (u1.mulElementWise(u1) * m1 / 2);
    auto E2 = (u2.mulElementWise(u2) * m2 / 2);

    auto E1c = E1.mulElementWise(o1->transform()->dof()) + E2.mulElementWise(o2->transform()->dof()*(-1) + 1);
    assert((E1c.x() + E1c.y()) >= 0);
    auto E2c = E2.mulElementWise(o2->transform()->dof()) + E1.mulElementWise(o1->transform()->dof()*(-1) + 1);
    assert((E2c.x() + E2c.y()) >= 0);

    double v1 = std::sqrt(2 * (E1c.x() + E1c.y()) / m1);
    double v2 = std::sqrt(2 * (E2c.x() + E2c.y()) / m2);

    o1_speed = o1_speed.normalize() * v1;
    o2_speed = o2_speed.normalize() * v2;

    auto Esys_new =  (o1_speed.mulElementWise(o1_speed) * m1 + o2_speed.mulElementWise(o2_speed) * m2) / 2.0;

    assert(abs(Esys.x() + Esys.y() - (Esys_new.x() + Esys_new.y())) < 0.1);
}