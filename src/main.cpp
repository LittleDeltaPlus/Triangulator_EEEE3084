#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unistd.h>
#include "Vec3.h"
#include "Triangle.h"
#include "Matrix.h"
#include "VecList.h"


using namespace std;

struct arguments{
    string inputFile, toLocate;
    bool delaunay;
    int integrationType;
};

void ParseArguments(int argc, char *const *argv, arguments *argumentStruct);
void ProcessFile(vecList<Vec3> *vertices, vecList<Triangle> *triangles, const arguments& argumentStruct);
bool isDelaunay(Triangle tri, vecList<Vec3>* points);
int findTriangleContaining(vecList<Triangle> *triangleList, const Vec3& point);

int main(int argc, char *argv[]) {
    //Parse CommandLine Arguments
    arguments arguments {};
    arguments.delaunay = false;
    ParseArguments( argc, argv, &arguments);

    //Create Lists
    vecList<Vec3> vertices;
    vecList<Triangle> triangles;

    //Process File
    ProcessFile(&vertices, &triangles, arguments);

    if(!arguments.toLocate.empty()){
        double x,y,z;
        std::istringstream iss(arguments.toLocate);
        if (!(iss >> x >> y >> z)){ throw runtime_error("Error: Invalid x,y,z Co-ordinate");}
        int tri = findTriangleContaining(&triangles, Vec3(x,y,z));
        if(tri == -1){
            cout << "point " << arguments.toLocate << " is NOT contained within a triangle within file: " << arguments.inputFile <<endl;
        } else {
            cout << "point " << arguments.toLocate << " is contained within triangle" <<
                 tri << " within file: " << arguments.inputFile <<endl;
        }
    }

    bool delaunayFlag = true;
    if (arguments.delaunay){
        for (int i = 0; i < triangles.getAllTriangles()->size(); i++) {
            if(!isDelaunay(triangles.getTriangle(i), &vertices)){
                delaunayFlag = false;
            }
        }
        if(delaunayFlag){
            cout<<"Given mesh: " << arguments.inputFile << " IS delaunay" <<endl;
        } else {
            cout<<"Given mesh: " << arguments.inputFile << " is NOT delaunay" <<endl;
        }
    }

    //ToDo: Integration
    //switch(arguments.integrationType){
        //default:
            //break;
        //case 1:
            //triangles.ingegrate(1) VVV
                /*  Vec3 evaluateAt(Vec3 point);
                 *  double integrateConst(vecList<Triangle> triangleList, function evaluateAt())
                 */
            //break;
        //case 2:
            //double integrateLinear(vecList<Triangle> triangleList, function evaluateAt())
            //break;
        //}

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
                cout << "  -f \"x, y, z\"   : Returns the Triangle that contains the given point"<<endl;
                cout << "      -a{1 or 2} : Returns integral of the mesh using specified method "<<endl;
                cout << "---------------------------------------------------------------------  "<<endl;
                exit(0);
                break;
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
                cout << "unknown option: " << optopt;
                break;
        }
    }
    for(; optind < argc; optind++){
        printf("extra arguments: %s\n", argv[optind]);
    }
}

void ProcessFile(vecList<Vec3> *vertices, vecList<Triangle> *triangles, const arguments& argumentStruct){
    int objCount, coordCount, argCount;
    string line, token;

    //Try to open the input file
    ifstream fileIn(argumentStruct.inputFile);
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
        //line.replace(line.begin(), line.end(), ' ', '\n');
        std::istringstream processStream(line);

        vector<double> params;
        double tmp{};

        while(getline(processStream, token, ' ')){
            tmp = stod(token);
            params.push_back(tmp);
        }

        if(argCount != 0){
            vertices->addVertex(Vec3(params[1], params[2], params[3], vector<double>(params.end()-argCount, params.end())));
        } else {
            vertices->addVertex(Vec3(params[1], params[2], params[3]));
        }
        params.clear();
    }
    int triCount, vertCount, paramCount;
    getline(fileIn, line);
    std::istringstream iss2(line);
    if (!(iss2 >> triCount >> vertCount >> paramCount)){ exit(4);}

    for (int j = 0; j < objCount; j++) {
        getline(fileIn, line);
        //line.replace(line.begin(), line.end(), ' ', '\n');
        std::istringstream processStream(line);

        vector<double> params;
        double tmp{};

        while(getline(processStream, token, ' ')){
            tmp = stod(token);
            params.push_back(tmp);
        }

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

bool isDelaunay(Triangle tri, vecList<Vec3>* points) {
    for (int i = 0; i < points->getAllVertices()->size(); ++i) {
        Vec3 *point = points->getVertex(i);
        if(tri.isWithinCc(Vec3(point->getX(), point->getY(), point->getZ()))){
            return false;
        }
    }
    return true;
}

int findTriangleContaining(vecList<Triangle> *triangleList, const Vec3& point){
    for (int i = 0; i < triangleList->getAllTriangles()->size(); i++) {
        if(triangleList->getTriangle(i).isWithin(point)){
            return i;
        }
    }
    return -1;
}