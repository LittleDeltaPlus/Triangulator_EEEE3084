//
// Created by matt on 08/11/18.
// For ModelLoader
//

#include "Vec3.h"

#include <utility>

Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

Vec3::Vec3(double x, double y, double z, std::vector<double> params) : x(x), y(y), z(z), params(std::move(params)) {}


double Vec3::getX() const {
    return x;
}


void Vec3::setX(double x_val) {
    Vec3::x = x_val;
}


double Vec3::getY() const {
    return y;
}


void Vec3::setY(double y_val) {
    Vec3::y = y_val;
}


double Vec3::getZ() const {
    return z;
}


void Vec3::setZ(double z_val) {
    Vec3::z = z_val;
}

std::vector<double>* Vec3::getParams()  {
    return &params;
}

void Vec3::setParams(std::vector<double> parameters){
    Vec3::params = std::move(parameters);
}
int * Vec3::getTriangles() {
    return triangles.data();
}
void Vec3::addTriangle(int triangle) {
    Vec3::triangles.push_back(triangle);
}


Vec3 Vec3::operator+(const Vec3 &right) const {
    return {x + right.x, y + right.y, z + right.z};
}

Vec3 Vec3::operator-(const Vec3 &right) const {
    return {x - right.x, y - right.y, z - right.z};
}

Vec3 Vec3::operator*(const double &right) const {
    return {x * right, y * right, z * right};
}

Vec3 Vec3::operator*(const Vec3 &right) const {
    return {y * right.z - z * right.y,
            z * right.x - x * right.z,
            x * right.y - y * right.x};
}

Vec3 Vec3::operator/(const double &right) const {
    return {x / right, y / right, z / right};
}

bool Vec3::operator==(const Vec3 &rhs) const {
    return x == rhs.x &&
           y == rhs.y &&
           z == rhs.z;
}

bool Vec3::operator!=(const Vec3 &rhs) const {
    return !(rhs == *this);
}


double Vec3::dot(const Vec3 &right) {
    return x*right.x + y*right.y + z*right.z;
}

double Vec3::mag() {
    return sqrt(x*x + y*y + z*z);
}


std::ostream& operator<<(std::ostream& os, const Vec3& vec)
{
    os << std::fixed << std::setprecision(10) <<'[' << vec.getX() << ',' << vec.getY() << ',' << vec.getZ() << ']';
    return os;
}

std::ofstream& operator<<(std::ofstream& os, const Vec3& vec) {
    os << "v "  << " " << vec.getX() << " " << vec.getY() << " " << vec.getZ();
    return os;
};

std::istream &operator>>(std::istream &is, Vec3 &vec) {
    double x, y, z;
    is >> x >> y >> z;

    vec.setX(x);
    vec.setY(y);
    vec.setZ(z);

    return is;
}
