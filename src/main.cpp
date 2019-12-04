#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unistd.h>
#include "Vec3.h"
#include "Triangle.h"
#include "VecList.h"


using namespace std;

/**
 * Placeholder function of x and y
 * @param [in] x
 * @param [in] y
 * @return function TBD by client
 */
double FunctionOfXandY(double x, double y){
    return x+y;
}

/**
 * structure containing CL input flags, strings and options
 */
struct arguments{
    string inputFile, toLocate;
    bool delaunay;
    int integrationType;
};

/**
 * Parses Command Line Arguments & Parameters
 * @param argc
 * @param argv
 * @param [in,out] argumentStruct
 */
void ParseArguments(int argc, char *const *argv, arguments *argumentStruct);
/**
 * Reads supplied input file, with validation.
 * @param [in,out] vertices
 * @param [in,out] triangles
 * @param [in] inputFile
 */
void ProcessFile(vecList<Vec3> *vertices, vecList<Triangle> *triangles, const string& inputFile);
/**
 * Checks if a provided triangle is delaunay, given the other vertices in the mesh
 * @param [in] tri
 * @param [in] points
 * @return Whether or not the triangle IS Delaunay
 */
bool IsDelaunay(Triangle tri, vecList<Vec3>* points);
/**
 * Checks if a given point is within a list of triangles
 * @param triangleList
 * @param point
 * @return Index of the containing triangle in the supplied list (-1 on fail)
 */
int findTriangleContaining(vecList<Triangle> *triangleList, const Vec3& point);

int main(int argc, char *argv[]) {
    //Parse CommandLine Arguments
    arguments arguments {};
    arguments.delaunay = false;
    arguments.integrationType =0;
    ParseArguments( argc, argv, &arguments);

    //Create Lists
    vecList<Vec3> vertices;
    vecList<Triangle> triangles;

    //Process File
    ProcessFile(&vertices, &triangles, arguments.inputFile);

    if(!arguments.toLocate.empty()){
        double x,y,z;
        std::istringstream iss(arguments.toLocate);
        if (!(iss >> x >> y >> z)){ throw runtime_error("Error: Invalid x,y,z Co-ordinate");}
        int tri = findTriangleContaining(&triangles, Vec3(x,y,z));
        if(tri == -1){
            cout << "point " << arguments.toLocate << " is NOT contained within a triangle within file: " << arguments.inputFile <<endl;
        } else {
            cout << "point " << arguments.toLocate << " is contained within triangle " <<
                 tri << " within file: " << arguments.inputFile <<endl;
        }
    }

    //ToDo: Delaunay TestMesh
    bool delaunayFlag = true;
    if (arguments.delaunay){
        for (int i = 0; i < triangles.getAllTriangles()->size(); i++) {
            if(!IsDelaunay(triangles.getTriangle(i), &vertices)){
                delaunayFlag = false;
            }
        }
        if(delaunayFlag){
            cout<<"Given mesh: " << arguments.inputFile << " IS delaunay" <<endl;
        } else {
            cout<<"Given mesh: " << arguments.inputFile << " is NOT delaunay" <<endl;
        }
    }

    //ToDo: MASSIVE difference bug
    switch(arguments.integrationType){
        default:
            cout << "invalid Integration Type Selected, Please choose from the following options; " << endl;
            cout << "       1 - use of constant value approximation. "<<endl;
            cout << "       2 - use of linear interpolation. "<<endl;
            break;
        case 1:
            cout << "The estimated value of the integral of F(x,y) is: " << triangles.integrateConst(FunctionOfXandY) <<
            " for the mesh Provided in: " << arguments.inputFile <<endl;
            break;
        case 2:
            cout << "The estimated value of the integral of F(x,y) is: " << triangles.integrateLinear(FunctionOfXandY) <<
                 " using Linear interpolation for the mesh Provided in: " << arguments.inputFile <<endl;
            break;
        case 0:
            break;
        }

    exit(0);
}

void ParseArguments(int argc, char *const *argv, arguments *ArgumentStruct){
    int opt;
    while((opt = getopt(argc, argv, "i:h:f:d:a:b:")) != -1)
    {
        switch(opt)
        {
            default:
                break;
            case 'i':
                ArgumentStruct->inputFile = optarg;
                break;
            case ':':
                cout << "option needs a value";
                break;
            case 'h':
                cout << "             Triangulator - SCPS_CW2 - Seamus Doran                    "<<endl;
                cout << "----------------------------Help Menu--------------------------------  "<<endl;
                cout << "           -help : Displays this help menu                             "<<endl;
                cout << "   -i <FilePath> : Specifies an Input file                             "<<endl;
                cout << "   -o <FilePath> : Specifies a Location for an output file             "<<endl;
                cout << "       -delaunay : Checks if the Mesh Provided is Delaunay             "<<endl;
                cout << "    -f \"x y z\"   : Returns the Triangle that contains the given point"<<endl;
                cout << "     -a {1 or 2} : Returns integral of the mesh using specified method "<<endl;
                cout << "---------------------------------------------------------------------  "<<endl;
                exit(0);
            case 'f':
                ArgumentStruct->toLocate = optarg;
                break;
            case 'd':
                ArgumentStruct->delaunay = true;
                break;
            case 'a':
                ArgumentStruct->integrationType = stoi(optarg);
                break;
            case '?':
                cout << "unknown option: " << optopt <<endl;
                cout << "   add argument -help for a list of commands"<<endl;
                break;
        }
    }
    for(; optind < argc; optind++){
        printf("extra arguments: %s\n", argv[optind]);
    }
}

void ProcessFile(vecList<Vec3> *vertices, vecList<Triangle> *triangles, const string& inputFile){
    //ToDo: implement vecList stream operators
    int objCount, coordCount, argCount;
    string line, token;

    //Try to open the input file
    ifstream fileIn(inputFile);
    if (fileIn.fail()){
        throw runtime_error("Error opening Input File");
    }
    //Get the first line of the file and process it
    getline(fileIn, line);
    std::istringstream iss(line);
    if (!(iss >> objCount >> coordCount >> argCount)){ exit(3);}
    //Import vertices
    for (int i = 0; i < objCount; i++) {
        getline(fileIn, line);
        std::istringstream processStream(line);

        vector<double> params;
        double tmp{};

        //stream input to temporary vector
        while(getline(processStream, token, ' ')){
            tmp = stod(token);
            params.push_back(tmp);
        }

        //add vertex to the list
        if(argCount != 0){
            vertices->addVertex(Vec3(params[1], params[2], params[3], vector<double>(params.end()-argCount, params.end())));
        } else {
            vertices->addVertex(Vec3(params[1], params[2], params[3]));
        }
        params.clear();
    }
    //find triangle info
    int triCount, vertCount, paramCount;
    getline(fileIn, line);
    std::istringstream iss2(line);
    if (!(iss2 >> triCount >> vertCount >> paramCount)){ exit(4);}

    for (int j = 0; j < objCount; j++) {
        getline(fileIn, line);
        std::istringstream processStream(line);

        vector<double> params;
        double tmp{};

        //stream input to temporary vector
        while(getline(processStream, token, ' ')){
            tmp = stod(token);
            params.push_back(tmp);
        }

        //add triangle to the list
        if(paramCount != 0){
            vector<double> addParams =params;
            addParams.erase(addParams.begin(), addParams.end()+1-paramCount);
            triangles->addTriangle(Triangle(vertices->getVertex(params[1]),vertices->getVertex(params[2]),vertices->getVertex(params[3]), addParams));
        } else {
            triangles->addTriangle(Triangle(vertices->getVertex(params[1]),vertices->getVertex(params[2]),vertices->getVertex(params[3])));
        }
        params.clear();
    }
}

bool IsDelaunay(Triangle tri, vecList<Vec3>* points) {
    for (int i = 0; i < points->getAllVertices()->size(); ++i) {
        Vec3 *point = points->getVertex(i);
        if(tri.isWithinCc(Vec3(point->getX(), point->getY(), point->getZ()))){
            //if any point is within a circum circle the mesh isn't delaunay, thus return false.
            return false;
        }
    }//else return true
    return true;
}

int findTriangleContaining(vecList<Triangle> *triangleList, const Vec3& point){
    for (int i = 0; i < triangleList->getAllTriangles()->size(); i++) {
        if(triangleList->getTriangle(i).isWithin(point)){
            //if a triangle is within a triangle return its index
            return i;
        }
    }//else return -1
    return -1;
}