#include "Vec3.h"
#include "Matrix.h"

//
// Created by Seámus on 09/11/18.
//


Mat::Mat(Vec3 VecA, Vec3 VecB, Vec3 VecC): VecA(VecA), VecB(VecB), VecC(VecC) {}


const Vec3 &Mat::getVecA() const {
    return VecA;
}

void Mat::setVecA(const Vec3 &VecA) {
    Mat::VecA = VecA;
}

const Vec3 &Mat::getVecB() const {
    return VecB;
}

void Mat::setVecB(const Vec3 &VecB) {
    Mat::VecB = VecB;
}

const Vec3 &Mat::getVecC() const {
    return VecC;
}

void Mat::setVecC(const Vec3 &VecC) {
    Mat::VecC = VecC;
}


Mat Mat::operator+(const Mat &right) {
    return {VecA + right.VecA, VecB + right.VecB, VecC + right.VecC};
}

Mat Mat::operator-(const Mat &right) {
    return {VecA - right.VecA, VecB - right.VecB, VecC - right.VecC};
}

Mat Mat::operator*(const Mat &right){

    Vec3 X(this->VecA.getX(), this->VecB.getX(), this->VecC.getX());
    Vec3 Y(this->VecA.getY(), this->VecB.getY(), this->VecC.getY());
    Vec3 Z(this->VecA.getZ(), this->VecB.getZ(), this->VecC.getZ());

    VecA.setX(X.dot(right.VecA)); // ( - - - )
    VecB.setX(X.dot(right.VecB)); // (       )
    VecC.setX(X.dot(right.VecC)); // (       )

    VecA.setY(Y.dot(right.VecA));// (       )
    VecB.setY(Y.dot(right.VecB));// ( - - - )
    VecC.setY(Y.dot(right.VecC));// (       )

    VecA.setZ(Z.dot(right.VecA));// (       )
    VecB.setZ(Z.dot(right.VecB));// (       )
    VecC.setZ(Z.dot(right.VecC));// ( - - - )


    return {VecA, VecB, VecC};
}

Mat Mat::operator*(const double &right) {
    return {VecA * right, VecB * right, VecC * right};
}

Mat Mat::operator/(const Mat &right) {
    return {*this * right.inverse()};
}

Mat Mat::operator/(const double &right) {
    return {VecA / right, VecB / right , VecC / right};
}

bool Mat::operator==(const Mat &rhs) const {
    return VecA == rhs.VecA &&
           VecB == rhs.VecB &&
           VecC == rhs.VecC;
}

bool Mat::operator!=(const Mat &rhs) const {
    return !(rhs == *this);
}


double Mat::calcDet() const{
    double a, b, c, d;
    std::array<double, 3> det{0};

    a = this->VecB.getY();
    b = this->VecC.getY();
    c = this->VecB.getZ();
    d = this->VecC.getZ();

    det[0] = a*d - b*c;
    det[0]= det[0]*this->VecA.getX();

    a = this->VecA.getY();
    b = this->VecC.getY();
    c = this->VecA.getZ();
    d = this->VecC.getZ();

    det[1] = a*d - b*c;
    det[1]= (-1)*det[1]*this->VecB.getX();

    a = this->VecA.getY();
    b = this->VecB.getY();
    c = this->VecA.getZ();
    d = this->VecB.getZ();

    det[2] = a*d - b*c;
    det[2] = det[2]*this->VecC.getX();

    return std::accumulate(det.begin(),det.end(), 0.0);

}

Mat Mat::transpose() const{
    Mat out = *this;

    out.VecB.setX(this->VecA.getY());
    out.VecA.setY(this->VecB.getX());

    out.VecC.setX(this->VecA.getZ());
    out.VecA.setZ(this->VecC.getX());

    out.VecC.setY(this->VecB.getZ());
    out.VecB.setZ(this->VecC.getY());

    return {out};

}

Mat Mat::inverse() const{
    double Det;
    Mat out = this->transpose();
    Det = out.calcDet();
    out = out.detMatrix();
    out = out.cofactor();
    if (Det!= 0) {
        out = out  / Det;
    }
    else {
        throw;
    }

    return {out};
}

Mat Mat::detMatrix(){
    Mat out;
    double a, b, c, d;
    std::array<double, 9> det{0};

    //------Find X Determinants-------
    a = this->VecB.getY();
    b = this->VecC.getY();
    c = this->VecB.getZ();
    d = this->VecC.getZ();

    det[0] = a*d - b*c;

    a = this->VecA.getY();
    b = this->VecC.getY();
    c = this->VecA.getZ();
    d = this->VecC.getZ();

    det[1] = a*d - b*c;

    a = this->VecA.getY();
    b = this->VecB.getY();
    c = this->VecA.getZ();
    d = this->VecB.getZ();

    det[2] = a*d - b*c;

    //------Find Y Determinants-------

    a = this->VecB.getX();
    b = this->VecC.getX();
    c = this->VecB.getZ();
    d = this->VecC.getZ();

    det[3] = a*d - b*c;

    a = this->VecA.getX();
    b = this->VecC.getX();
    c = this->VecA.getZ();
    d = this->VecC.getZ();

    det[4] = a*d - b*c;

    a = this->VecA.getX();
    b = this->VecB.getX();
    c = this->VecA.getZ();
    d = this->VecB.getZ();

    det[5] = a*d - b*c;

    //------Find Z Determinants-------

    a = this->VecB.getX();
    b = this->VecC.getX();
    c = this->VecB.getY();
    d = this->VecC.getY();

    det[6] = a*d - b*c;

    a = this->VecA.getX();
    b = this->VecC.getX();
    c = this->VecA.getY();
    d = this->VecC.getY();

    det[7] = a*d - b*c;

    a = this->VecA.getX();
    b = this->VecB.getX();
    c = this->VecA.getY();
    d = this->VecB.getY();

    det[8] = a*d - b*c;

    //------Populate for output-------
    out.populate(det[0],det[1],det[2],
                 det[3],det[4],det[5],
                 det[6],det[7],det[8]);
    return out;
}

/**
 * |+ - + |
 * |- + - |
 * |+ - + |
 */
Mat Mat::cofactor(){
    Mat out = *this;
    out.VecA.setY(this->VecA.getY()* -1);
    out.VecB.setX(this->VecB.getX()* -1);
    out.VecB.setZ(this->VecB.getZ()* -1);
    out.VecC.setY(this->VecC.getY()* -1);
    return out;
}

 std::array<Mat, 3> genRotation(double xRads, double yRads, double zRads) {
    std::array<Mat, 3>Rotation;
    Rotation[0].populate(1, 0, 0, 0, std::cos(xRads), std::sin(xRads), 0, -std::sin(xRads), std::cos(xRads));
    Rotation[1].populate(std::cos(yRads), 0, -std::sin(yRads), 0, 1, 0, std::sin(yRads), 0, std::cos(yRads));
    Rotation[2].populate(std::cos(zRads), std::sin(zRads), 0, -std::sin(zRads), std::cos(zRads), 0, 0, 0, 1);

    return Rotation;
}

void Mat::populate(double a, double b, double c,
                double d, double e, double f,
                double g, double h, double i){
    this->VecA.setX(a);
    this->VecB.setX(b);
    this->VecC.setX(c);
    this->VecA.setY(d);
    this->VecB.setY(e);
    this->VecC.setY(f);
    this->VecA.setZ(g);
    this->VecB.setZ(h);
    this->VecC.setZ(i);
}


std::ostream& operator<<(std::ostream& os, const Mat& Mat)
{
    Vec3 X(Mat.VecA.getX(), Mat.VecB.getX(), Mat.VecC.getX());
    Vec3 Y(Mat.VecA.getY(), Mat.VecB.getY(), Mat.VecC.getY());
    Vec3 Z(Mat.VecA.getZ(), Mat.VecB.getZ(), Mat.VecC.getZ());

    os  << X.getX() << ',' << X.getY() << ',' << X.getZ() <<std::endl;
    os  << Y.getX() << ',' << Y.getY() << ',' << Y.getZ() <<std::endl;
    os  << Z.getX() << ',' << Z.getY() << ',' << Z.getZ() <<std::endl;
    return os;
}

