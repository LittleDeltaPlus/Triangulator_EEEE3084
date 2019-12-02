//
// Created by Seámus on 29/11/19.
// For Triangulator
//

#include "Triangle.h"

#include <utility>

Triangle::Triangle(Vec3 *point1, Vec3 *point2, Vec3 *point3) : point1(point1), point2(point2), point3(point3) {}

Triangle::Triangle(Vec3 *point1, Vec3 *point2, Vec3 *point3, std::vector<double> parameters) : point1(point1), point2(point2), point3(point3), params(std::move(parameters)) {}


Vec3* Triangle::getPoint1() const {
    return point1;
}


void Triangle::setPoint1(Vec3* vertex1) {
    Triangle::point1 = vertex1;
}


Vec3* Triangle::getPoint2() const {
    return point2;
}


void Triangle::setPoint2(Vec3* vertex2) {
    Triangle::point2 = vertex2;
}


Vec3* Triangle::getPoint3() const {
    return point3;
}


void Triangle::setPoint3(Vec3* vertex3) {
    Triangle::point3 = vertex3;
}

std::vector<double>* Triangle::getParams()  {
    return &params;
}

void Triangle::setParams(std::vector<double> parameters) {
    Triangle::params = std::move(parameters);
}

std::ostream& operator<<(std::ostream& os, const Triangle& tri)
{
    os << std::fixed << std::setprecision(10) <<'[' << tri.getPoint1() << ',' << tri.getPoint2() << ',' << tri.getPoint3() << ']';
    return os;
}

std::ofstream& operator<<(std::ofstream& os, const Triangle& tri) {
    os << "v "  << " " << tri.getPoint1() << " " << tri.getPoint2() << " " << tri.getPoint3();
    return os;
};

std::istream &operator>>(std::istream &is, Triangle &tri) {
    Vec3 point1, point2, point3;
    is >> point1 >> point2 >> point3;

    tri.setPoint1(&point1);
    tri.setPoint2(&point2);
    tri.setPoint3(&point3);

    return is;
}
