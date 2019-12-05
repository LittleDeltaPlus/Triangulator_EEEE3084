//
// Created by Seámus on 30/11/2019.
//
#include "VecList.h"

#include <utility>

/// Vector Specialisation
vecList<Vec3>::vecList(Vec3 vertex) : vertexList() {addVertex(std::move(vertex));};

void vecList<Vec3>::addVertex(Vec3 vertex) {
    vertexList.push_back(vertex);
}

void vecList<Vec3>::rmVertex(int index) {
    std::vector<Vec3>::iterator it;
    it = vertexList.begin() + index;
    vertexList.erase(it,it);
}

void vecList<Vec3>::rmVertices(int index1, int index2) {
    std::vector<Vec3>::iterator it1, it2;
    it1 = vertexList.begin() + index1;
    it2 = vertexList.begin() + index2;
    vertexList.erase(it1,it2);
}

void vecList<Vec3>::insVertext(int index, Vec3 vertex) {
    std::vector<Vec3>::iterator it;
    it = vertexList.begin() + index;
    vertexList.insert(it,vertex);
}

Vec3* vecList<Vec3>::getVertex(int index) {
    return &vertexList[index];
}

std::vector<Vec3>* vecList<Vec3>::getAllVertices() {
    return &vertexList;
}

//ToDo: finding algorithm


/// Triangle Specialisation
vecList<Triangle>::vecList(Triangle triangle) : triangleList() {addTriangle(triangle);} ;


void vecList<Triangle>::addTriangle(Triangle tri) {
    triangleList.push_back(tri);
    //ToDo: add member info to vertices
}

void vecList<Triangle>::rmTriangle(int index) {
    std::vector<Triangle>::iterator it;
    it = triangleList.begin() + index;
    triangleList.erase(it, it);
}

void vecList<Triangle>::rmTriangles(int index1, int index2) {
    std::vector<Triangle>::iterator it1, it2;
    it1 = triangleList.begin() + index1;
    it2 = triangleList.begin() + index2;
    triangleList.erase(it1, it2);
}

void vecList<Triangle>::insTriangle(int index, Triangle tri) {
    std::vector<Triangle>::iterator it;
    it = triangleList.begin() + index;
    triangleList.insert(it, tri);
}

Triangle vecList<Triangle>::getTriangle(int index) {
    return triangleList[index];
}

std::vector<Triangle>* vecList<Triangle>::getAllTriangles() {
    return &triangleList;
}

//ToDo: move for loop internal functionality to triangle
double vecList<Triangle>::integrateLinear(double (*func)(double x, double y)) {
    double S=0;
    for (int i =0; i < triangleList.size(); i++) {
        double a, b, c;
        //evaluate function at each point of the triangle
        a = func(triangleList[i].getPoint1()->getX(), triangleList[i].getPoint1()->getY());
        b = func(triangleList[i].getPoint2()->getX(), triangleList[i].getPoint2()->getY());
        c = func(triangleList[i].getPoint3()->getX(), triangleList[i].getPoint3()->getY());
        //find sub-triangle areas
        double A = triangleList[i].area()/3;
        //use linearly interpolated constant value approximation
        S+=A*(a+b+c);
    }
    return S;
}

double vecList<Triangle>::integrateConst(double(*func)(double x, double y)) {
    double S = 0;
    for (int i =0; i < triangleList.size(); i++) {
        double F;
        //evaulate function at the centre of the triangles circumcircle
        F = func(O.getX(), O.getY());
        Vec3 O = triangleList[i].getCcCentre();
        //get the area for the triangle
        double A = triangleList[i].area();
        //use supplied constant value approximation
        S+=A*(F);
    }
    return S;
}