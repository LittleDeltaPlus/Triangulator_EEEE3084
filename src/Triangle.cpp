//
// Created by Seámus on 29/11/19.
// For Triangulator
//

#include "Triangle.h"

#include <utility>

Triangle::Triangle(Vec3 *point1, Vec3 *point2, Vec3 *point3) : point1(point1), point2(point2), point3(point3) {
    calcCc();
}

Triangle::Triangle(Vec3 *point1, Vec3 *point2, Vec3 *point3, std::vector<double> parameters) : point1(point1), point2(point2), point3(point3), params(std::move(parameters)) {
    calcCc();
}


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

Vec3 Triangle::getCcCentre() {
    return CcCentre;
}

double Triangle::getCcRadius() {
    return CcRadius;
}

bool Triangle::isWithinCc(const Vec3& point) {
    double magnitude = Vec3(point - CcCentre).mag();
    return CcRadius >= magnitude;
}



bool Triangle::isWithin(Vec3 point) {
    double S = area(point1,point2,point3), alpha, beta, gamma, theta;
    double S1 = area(&point, point2, point3);
    double S2 = area(point1, &point, point3);
    alpha = S1/S;
    beta = S2/S;
    gamma = 1- alpha -beta;
    return (0 <= alpha && alpha <=1) && (0 <= beta && beta <=1) && (0 <= gamma && gamma <=1);
}


double Triangle::area(){
    Vec3 a= localise(point1);
    Vec3 b= localise(point2);
    Vec3 c= localise(point3);
    Vec3 ab = a-b;
    Vec3 ac = a-c;
    double theta =  asin(ab.dot(ac)/(ab.mag()*ac.mag()));
    return 0.5*ab.mag()*ac.mag()*sin(theta);
}

double Triangle::area(Vec3 *pointa, Vec3 *pointb, Vec3 *pointc) {
    Vec3 a= localise(pointa);
    Vec3 b= localise(pointb);
    Vec3 c= localise(pointc);
    Vec3 ab = a-b;
    Vec3 ac = a-c;
    double theta =  asin(ab.dot(ac)/(ab.mag()*ac.mag()));
    return 0.5*ab.mag()*ac.mag()*sin(theta);
}

Vec3 Triangle::centre() {
    Vec3 a= localise(point1);
    Vec3 b= localise(point2);
    Vec3 c= localise(point3);
    return ((a+b+c)/3);
}

void Triangle::calcCc() {
    Vec3 x(point1->getX(), point2->getX(), point3->getX());
    Vec3 y(point1->getY(), point2->getY(), point3->getY());
    Vec3 one (1,1,1);
    Mat LHS(x,y,one);
    Vec3 Cc = LHS.inverse() * Vec3( (point1->getX())*(point1->getX())+(point1->getY())*(point1->getY()),
                                    (point2->getX())*(point2->getX())+(point2->getY())*(point2->getY()),
                                    (point3->getX())*(point3->getX())+(point3->getY())*(point3->getY()));

    CcCentre = Vec3( Cc.getX()/2, Cc.getY()/2, (point1->getZ()+point1->getZ()+point1->getZ())/3);
    CcRadius = (sqrt(Cc.getZ()+CcCentre.getX()*CcCentre.getX()+CcCentre.getY()*CcCentre.getY()));
}

Vec3 Triangle::localise(Vec3 *vector){
    return Vec3(vector->getX(), vector->getY(), vector->getZ());
}