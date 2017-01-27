// Mesh.h

#ifndef MESH_H
#define MESH_H
  
  
#include "Face.h"
#include "Vector3d.h"
#include <vector>
 
 
class Shape;
 
#include "Shape.h"
#include "Normal.h"
 
using namespace std;
 
#define PI 3.14159

// Mesh
class Mesh{
   public:
    int numVerts; // number of vertices in the mesh
    int numNorms; // number of normal vertices for the mesh
    int numFaces; // number of faces in the mesh
    
    vector <Vector3d> pt; // 3D vertices
    vector <Normal> norm; // normals
    vector <Face> face;
 
    Shape *shape;
   
    Mesh();         // constructor
    Mesh(Shape *shape); // constructor
    ~Mesh();            // destructor
    void draw();
    void makeSurfaceMesh();
    void calcNewell();
    void calcGourand();
 
    void readfile(string filename);
};
 
#endif
