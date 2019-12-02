//
// Modified from ModelLoader
//

#pragma once

#include <iomanip>
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

/**
 * @file Vec3 Class Definitions
 */

class Vec3 {
private:
    std::vector<int> triangles;
    std::vector<double> params;
    double x;
    double y;
    double z;
public:
    /**
     * Default Vec3 Constructor
     * @param x
     * @param y
     * @param z
     */
    Vec3() : x(0), y(0), z(0), params(), triangles() {};
    /**
     * Vec3 Constructor without additional parameters
     * @param x
     * @param y
     * @param z
     */
    Vec3(double x, double y, double z);
    /**
     * Vec3 Constructor with additional parameters
     * @param x
     * @param y
     * @param z
     * @param parameter array
     */
    Vec3(double x, double y, double z, std::vector<double> params);

    /**
     * X getter
     * @return X
     */
    double getX() const;
    /**
     * X Setter
     * @param x
     */
    void setX(double x_val);

    /**
     * Y Getter
     * @return
     */
    double getY() const;
    /**
     * Y Setter
     * @param y
     */
    void setY(double y_val);
    /**
     * Z Getter
     * @return
     */
    double getZ() const;
    /**
     * Z Setter
     * @param z
     */
    void setZ(double z_val);
    /**
     * Additional Parameter Getter
     * @return Index
     */
    std::vector<double>* getParams();
    /**
     * Additional Parameter Setter
     * @param params
     */
    void setParams(std::vector<double> parameters);
    /**
    * Triangle List Getter
    * @return Triangles
    */
    int* getTriangles();
    /**
     * params Setter
     * @param params
     */
    void addTriangle(int triangle);






    /**
     * Addition of two Vec3s
     * @param right
     * @return the resultant vector
     */
    Vec3 operator+(const Vec3& right) const;
    /**
     * Subtraction of two Vec3s
     * @param right
     * @return
     */
    Vec3 operator-(const Vec3& right) const;
    /**
     * Multiplication of a Vec3 by a scalar
     * @param right
     * @return scalar factored vector
     */
    Vec3 operator*(const double& right) const;
    /**
     * Cross product of two Vec3s
     * @param right
     * @return Cross product
     */
    Vec3 operator*(const Vec3& right) const;
    /**
     * Division of a Vec3 by a scalar
     * @param right
     * @return vector factored by a scalar
     */
    Vec3 operator/(const double& right) const;
    /**
     * checks if lhs = rhs
     * @param rhs
     * @return true if lhs and rhs are the same
     */
    bool operator==(const Vec3 &rhs) const;
    /**
     * checks if lhs != rhs
     * @param rhs
     * @return true if lhs and rhs are different
     */
    bool operator!=(const Vec3 &rhs) const;

    /**
     * Dot (Scalar) product of two Vec3s
     * @param right
     * @return Scalar product
     */
    double dot(const Vec3 &right);
    /**
     * calculates the magnitude of a vector
     * @return magnitude
     */
    double mag();


    /**
     * Stream output for writing vectors to a file
     * @param ofs
     * @param vec
     * @return
     */
    friend std::ofstream& operator<<(std::ofstream& ofs, const Vec3& vec);
    /**
     * stream output for displaying vectors
     * @param os
     * @param vec
     * @return
     */
    friend std::ostream& operator<<(std::ostream& os, const Vec3& vec);

    /**
     * stream input for reading in Vec3
     * @param is
     * @param vec
     * @return
     */
    friend std::istream &operator>>(std::istream &is, Vec3 &vec);
};
