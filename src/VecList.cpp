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

double vecList<Triangle>::integrateLinear(double (*func)(Vec3 *point)) {
    double S=0;
    for (auto & i : triangleList) {
        double a, b, c;
        a = func(i.getPoint1());
        b = func(i.getPoint2());
        c = func(i.getPoint3());
        double A = i.area()/3;
        S+=A*(a+b+c);
    }
    return S;
}

double vecList<Triangle>::integrateConst(double(*func)(Vec3 *point)) {
    double S = 0;
    for (auto & i : triangleList) {
        double F;
        Vec3 O = i.getCcCentre();
        F = func(&O);
        double A = i.area();
        S+=A*(F);
    }
    return S;
}