#include <iostream>
#include <unistd.h>
#include "Vec3.h"
#include "Triangle.h"
#include "VecList.h"
#include "Matrix.h"
//ToDo: triangle.getCentre
//ToDo: tirangle.getCcCentre
//ToDo: trignagle.getCcRadius
//ToDo: triangle.isWithinCc(point)
//ToDo: triangle.area()



using namespace std;

struct arguments{
    string inputFile ="", toLocate = "";
    bool delaunay = false;
    int integrationType =0;
};

void ParseArguments(int argc, char *const *argv, arguments *argumentStruct);
void ProcessFile(vecList<Vec3> *vertices, vecList<Triangle> *triangles, const arguments& argumentStruct);

int main(int argc, char *argv[]) {
    //Parse CommandLine Arguments
    arguments arguments {};
    ParseArguments( argc, argv, &arguments);

    //Create Lists
    vecList<Vec3> vertices;
    vecList<Triangle> triangles;

    //Process File
    ProcessFile(&vertices, &triangles, arguments);
    int i=0;


    //ToDo: Locate algorithm
    //if toLocate != ""
        //findTriangle(x, y, z)

    //ToDo: Delaunay Check
    //if arguments.delaunay == true
        //for tris in triangles {check isDelaunay()}
            //ToDo: triangle.getCentre
            //ToDo: tirangle.getCcCentre
            //ToDo: trignagle.getCcRadius
            //toDo: triangle.isWithinCc( point)

    //ToDo: Integration
    //switch(arguments.integrationType){
        //default:
            //break;
        //case 1:
            //triangles.ingegrate(1) VVV
                // integrate( F, triangle.getCcCentre(), triangle.Area())
            //break;
        //case 2:
            //triangles.integrate(2) VVV
                //
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
    istringstream iss(line);
    if (!(iss >> objCount >> coordCount >> argCount)){ exit(3);}
    //Import vertices
    for (int i = 0; i < objCount; i++) {
        getline(fileIn, line);
        //line.replace(line.begin(), line.end(), ' ', '\n');
        istringstream processStream(line);

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
    istringstream iss2(line);
    if (!(iss2 >> triCount >> vertCount >> paramCount)){ exit(4);}

    for (int j = 0; j < objCount; j++) {
        getline(fileIn, line);
        //line.replace(line.begin(), line.end(), ' ', '\n');
        istringstream processStream(line);

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