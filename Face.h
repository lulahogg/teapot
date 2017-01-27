// Face.h

#ifndef FACE_H
#define FACE_H

#include <vector>
  
#include "VertexID.h"
#include "Vector3d.h"
#include "Normal.h"
  
using namespace std; 
 
#define NULL 0

class Face{
    public:
    int nVerts; // number of vertices in this face
    Normal faceNorm; // face normal vector
 
    vector <VertexID> vert; // the list of vertex and normal indices
    Face( ){nVerts = 0; }
     
    ~Face( ){ nVerts = 0;} 
};
 
#endif