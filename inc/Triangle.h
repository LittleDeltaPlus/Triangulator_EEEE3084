//
// Created by matt on 08/11/18.
//

#pragma once

#include <iomanip>
#include <iostream>
#include <cmath>
#include <fstream>
#include "Vec3.h"
#include "Matrix.h"

/**
 * @file Triangle Class Definitions
 */

class Triangle {
private:
    Vec3 *point1;
    Vec3 *point2;
    Vec3 *point3;
    Vec3 CcCentre;
    double CcRadius;
    std::vector<double> params;
    void calcCc();
    static Vec3 localise(Vec3 *vector);

public:
    /**
     * Default Triangle Constructor
     * @param point1
     * @param point2
     * @param point3
     */
    Triangle() : point1(NULL), point2(NULL), point3(NULL), params(){};
    /**
     * Triangle Constructor
     * @param point1
     * @param point2
     * @param point3
     */
    Triangle(Vec3 *point1, Vec3 *point2, Vec3 *point3);
    /**
     * Triangle Constructor with output index
     * @param point1
     * @param point2
     * @param point3
     * @param params
     */
    Triangle(Vec3 *point1, Vec3 *point2, Vec3 *point3, std::vector<double> params);

    /**
     * Point1 getter
     * @return Point1
     */
    Vec3* getPoint1() const;
    /**
     * Point1 Setter
     * @param point1
     */
    void setPoint1(Vec3 *vertex1);

    /**
     * Point2 Getter
     * @return
     */
    Vec3* getPoint2() const;
    /**
     * Point2 Setter
     * @param point2
     */
    void setPoint2(Vec3 *vertex2);
    /**
     * Point3 Getter
     * @return
     */
    Vec3* getPoint3() const;
    /**
     * Point3 Setter
     * @param point3
     */
    void setPoint3(Vec3 *vertex3);
    /**
     * Index Getter
     * @return Index
     */
    std::vector<double>* getParams();
    /**
     * Index Setter
     * @param index
     */
    void setParams(std::vector<double> parameters);

    Vec3 getCcCentre();

    double getCcRadius();

    bool isWithinCc(const Vec3& point);

    bool isWithin(Vec3 point);

    double area();

    static double area(Vec3 *pointa, Vec3 *pointb, Vec3 *pointc);

    Vec3 centre();

    //ToDo: double integrate(int type);

    /**
     * Stream output for writing vectors to a file
     * @param ofs
     * @param vec
     * @return
     */
    friend std::ofstream& operator<<(std::ofstream& ofs, const Triangle& vec);
    /**
     * stream output for displaying vectors
     * @param os
     * @param vec
     * @return
     */
    friend std::ostream& operator<<(std::ostream& os, const Triangle& vec);

    /**
     * stream input for reading in Triangle
     * @param is
     * @param vec
     * @return
     */
    friend std::istream &operator>>(std::istream &is, Triangle &vec);
};
