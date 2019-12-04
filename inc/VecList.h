//
// Created by Seámus on 30/11/2019.
//

#pragma once

#include <iomanip>
#include <iostream>
#include <cmath>
#include <fstream>
#include "Vec3.h"
#include "Triangle.h"

template<typename T>
class vecList {};

template<> class vecList<Vec3> {
private:
    std::vector<Vec3> vertexList;
public:
    /**
     * Default Constructor for a list of Vertices
     */
    vecList(): vertexList() {};
    /**
     * Construct a vertexList with a Vertex
     * @param vertex
     */
    vecList(Vec3 vertex);
    /**
     * Adds a Vertex to The List of Vertices
     * @param [in] vertex
     */
    void addVertex(Vec3 vertex);
    /**
     * Removes a Vertex at a Specified index
     * @param [in] index
     */
    void rmVertex(int index);
    /**
     * Removes ALL vertices Between (AND INCLUDING) two specified indices
     * @param [in] index1
     * @param [in] index2
     */
    void rmVertices(int index1, int index2);
    /**
     * Inserts a Vertex before an existing vertex at a specified index
     * @param [in] index
     * @param [in] vertex
     */
    void insVertext(int index, Vec3 vertex);
    /**
     * Returns a pointer to the Vertex stored at a specified index
     * @param [in] index
     * @return [out] Vertex at specified index
     */
    Vec3* getVertex(int index);
    /**
     * Returns ALL stored Vertices
     * @return [out] ALL Vertices
     */
    std::vector<Vec3>* getAllVertices();
    //todo: rangefind
};

template<> class vecList<Triangle> {
private:
    std::vector<Triangle> triangleList;
public:
    /**
     * Default Constructor for a list of Triangles
     */
    vecList(): triangleList() {};
    /**
     * Constructor for a triangleList supplying the first Triangle
     * @param [in] triangle
     */
    explicit vecList(Triangle triangle);
    /**
     * Adds a Triangle to The list
     * @param [in] tri
     */
    void addTriangle(Triangle tri);
    /**
     * Removes the Triangle at a specified index
     * @param [in] index
     */
    void rmTriangle(int index);
    /**
     * Removes ALL Triangles between (AND INCLUDING) two indices
     * @param [in] index1
     * @param [in] index2
     */
    void rmTriangles(int index1, int index2);
    /**
     * Inserts a Triangle before the Triangle that appears at the given index
     * @param [in] index
     * @param [in] tri
     */
    void insTriangle(int index, Triangle tri);
    /**
     * Returns the Triangle at a given index
     * @param [in] index
     * @return [out] Specified Triangle
     */
    Triangle getTriangle(int index);
    /**
     * Returns [in] ALL triangles
     * @return [out] All Triangles
     */
    std::vector<Triangle>* getAllTriangles();

    /**
     * Returns the linear interpolated integral of a provided function over the area of the mesh using
     * @param [in] func
     * @return [out] approximation for the integral of mesh
     */
    double integrateLinear(double(*func)(double x, double y));

    /**
     * Returns the linear interpolated integral of a provided function over the area of the mesh using
     * @param [in] func
     * @return [out] approximation for the integral of mesh
     */
    double integrateConst(double(*func)(double x, double y));
};