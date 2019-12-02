//
// Created by Seámus on 09/11/18.
//
#pragma once

#include <numeric>
#include <cmath>
#include <array>
#include "Vec3.h"

/**
 * Matrix Class Definitions
 */

/**
 * 3x3 Matrix Class
 */
class Mat {
private:
    Vec3 VecA;
    Vec3 VecB;
    Vec3 VecC;
public:
    /**
     * Default Mat Constructor
     */
    Mat() : VecA(), VecB(), VecC() {};
    /**
     * Mat Constructor
     * @param VecA
     * @param VecB
     * @param VecC
     */
    Mat(Vec3 VecA, Vec3 VecB, Vec3 VecC);
    /**
     * VecA getter
     * @return VecA
     */
    const Vec3 &getVecA() const;
    /**
     * VecA setter
     * @param VecA
     */
    void setVecA(const Vec3 &VecA);

    /**
     * VecB getter
     * @return VecB
     */
    const Vec3 &getVecB() const;
    /**
     * VecB setter
     * @param VecB
     */
    void setVecB(const Vec3 &VecB);

    /**
     * VecC getter
     * @return VecC
     */
    const Vec3 &getVecC() const;
    /**
     * vec C setter
     * @param VecC
     */
    void setVecC(const Vec3 &VecC);


    /**
     * addition of two matrices
     * @param right
     * @return the resultant matrix
     */
    Mat operator+ (const Mat& right);
    /**
     * subtraction of two matrices
     * @param right
     * @return the resultant matrix
     */
    Mat operator-(const Mat& right);
    /**
     * Matrix multiplication
     * @param right
     * @return the product of LHS*RHS
     */
    Mat operator*(const Mat& right);
    /**
     * scalar multiplication of a matrix
     * @param right
     * @return the scalar factored matrix
     */
    Mat operator*(const double& right);
    /**
     * inverse matrix multiplication
     * @param right
     * @return the product of LHS * RHS^-1
     */
    Mat operator/(const Mat& right);
    /**
     * scalar division of a matrix
     * @param right
     * @return the factored matrix
     */
    Mat operator/(const double& right);
    /**
     * checks if lhs = rhs
     * @param rhs
     * @return true if left and right are the same
     */
    bool operator==(const Mat &rhs) const;
    /**
     * checks if lhs != rhs
     * @param rhs
     * @return True if left and right are different
     */
    bool operator!=(const Mat &rhs) const;


    /**
     * Calculates the determinant of a martix
     * @return the determinant
     */
    double calcDet() const;
    /**
     * transposes a matrix
     * @return the transposed matrix
     */
    Mat inverse() const;
    /**
     * inverts a matrix
     * @return the inverted matrix
     */
    Mat transpose() const;

    /**
     * creates cofactor matrix from current matrix
     * @return cofactor matrix
     */
    Mat cofactor();
    /**
     * creates a matrix of determinants using 2x2 minor matrices
     * @return matrix of determinants
     */
    Mat detMatrix();
    /**
     *  Generate Array of Rotation Matrices x, y, z
     * @param xRads
     * @param yRads
     * @param zRads
     * @return Array{X Rotation matrix, Y Rotation matrix, Z Rotation matrix}
     */
    friend std::array<Mat, 3> genRotation(double xRads, double yRads, double zRads);
    /**
     * fills a matrix with 9 arguments
     * @param a
     * @param b
     * @param c
     * @param d
     * @param e
     * @param f
     * @param g
     * @param h
     * @param i
     */
    void populate(double a, double b, double c,
                  double d, double e, double f,
                  double g, double h, double i);


    /**
     * stream output for displaying a matrix
     * @param os
     * @param Mat
     * @return
     */
    friend std::ostream& operator<<(std::ostream& os, const Mat& Mat);
};
