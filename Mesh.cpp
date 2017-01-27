// Mesh.cpp

// http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-13-normal-mapping/

#include <windows.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>
#include <iostream>
#include <fstream>
#include <string>

#include "Mesh.h"
   
using namespace std;
 
 
Mesh::Mesh()
{
    shape = new Shape();
 
}
 
 
Mesh::Mesh(Shape *shape2)
{
    shape = shape2;
}

 
Mesh::~Mesh()
{
 
}
 
 
 
// Mesh
void Mesh::makeSurfaceMesh()
{

   // readfile("cube.obj");
}
 
 
 // draw mesh
void Mesh::draw()
{
    // do for each side of the mesh (face)
    for(unsigned int f = 0;f <face.size();f++)
    {
        glColor3f(1,0,1); // creates pink wire view
        // wire or solid
        if(!shape->getWire())
        {
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
            glBegin(GL_POLYGON);
        }
        else
        {
            glDisable(GL_LIGHTING);
            glBegin(GL_LINE_LOOP);
        }
        // each vertex
        for(int v=0;v<face[f].nVerts;v++)
        {
            // normal
            int in = face[f].vert[v].normIndex;
            // vertex
            int iv = face[f].vert[v].vertIndex;
            // smooth
            if(shape->getSmooth())
                glNormal3f(norm[in].norm.x, norm[in].norm.y, norm[in].norm.z);
            // normal
            else
                glNormal3f(face[f].faceNorm.norm.x, face[f].faceNorm.norm.y, face[f].faceNorm.norm.z);
 
            glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
         
        }
        glEnd();
 
    }

	//draw normals
	if(shape->getNormals())
	{
		glDisable(GL_LIGHTING);
		glColor3f(1,0,0); // red
		glBegin(GL_LINES);

		//if smooth draw
		if(1)
		{
			for(unsigned int i =0; i<norm.size(); i++)
			{
				glVertex3d(pt.at(i).x, pt.at(i).y, pt.at(i).z); 

				glVertex3d(pt.at(i).x + norm.at(i).norm.x*.2/shape->getScale() , 
					pt.at(i).y + norm.at(i).norm.y*.2/shape->getScale(), 
					pt.at(i).z+ norm.at(i).norm.z*.2/shape->getScale());
				
			}
		}
		
		glEnd();
	}
 
}
 
 
// Calculate Newell Face Normal 
void Mesh::calcNewell()
{
    for(unsigned int i = 0; i < face.size(); i++) {
        face[i].faceNorm.norm.x = 0;
        face[i].faceNorm.norm.y = 0;
        face[i].faceNorm.norm.z = 0;
        
        // loop x, y and z
        for(int j = 0; j < face[i].nVerts; j++) {
            
            Vector3d current = pt[face[i].vert[j].vertIndex];
            Vector3d next;
            
            if(j == face[i].nVerts - 1) {
                next = pt[face[i].vert[0].vertIndex];
            }
            else {
                next = pt[face[i].vert[j + 1].vertIndex];
            }
            face[i].faceNorm.norm.x += (current.y - next.y * current.z + next.z);
            face[i].faceNorm.norm.y += (current.z - next.z * current.x + next.x);
            face[i].faceNorm.norm.z += (current.x - next.x * current.y + next.y);
        }

    }

}
 
 
// calculate normal at Vertices
void Mesh::calcGourand()
{
     
    for(unsigned int i = 0; i < face.size(); i++) {
        for(int j = 0; j < face[i].nVerts; j++) {
            norm[face[i].vert[j].normIndex].norm.x = 0;
            norm[face[i].vert[j].normIndex].norm.y = 0;
            norm[face[i].vert[j].normIndex].norm.z = 0;
        }
    }
 
    for(unsigned int i = 0; i < face.size(); i++) {
        for(int j = 0; j < face[i].nVerts; j++) {
            norm[face[i].vert[j].normIndex].norm = face[i].faceNorm.norm;
        }
    }
 
    for(int i = 0; i < numNorms; i++) {
        norm[i].norm.normalize();
    }
}
 
// reads in a mesh from a Wavefront OBJ object model file
void Mesh::readfile(string filename)
{
 
    ifstream in(filename.c_str());
    string s;
    double x,y,z;
    int vindex;
 
    Vector3d v;
    Face f;
    VertexID vid;
 
    norm.resize(0);
    face.resize(0);
    pt.resize(0);
 
    in >> s;
    while(1)
    {
        // vertex
        if(s == "v")
        {
            in >> x >> y >> z;
            v.set(x,y,z);
            pt.push_back(v);
            
            if(!(in >> s))
                break;
 
        }
        // face
        else if(s == "f")
        {
 
            while((in >> s) && s[0]>='0' && s[0]<='9')
            {
     
                vindex = atoi(s.c_str());
     
                vid.vertIndex = vid.normIndex = vindex-1;
                f.vert.push_back(vid);
                f.nVerts=f.vert.size();
            }
            face.push_back(f);
            f.vert.resize(0);
        }
        else
        {
            getline(in,s);
            if(!(in>>s))
                break;
        }
    } 
 
    norm.resize(pt.size());
 
    numVerts = pt.size();
    numFaces = face.size();
    numNorms = norm.size();
 
    // function calls
    calcNewell();
    calcGourand();
 
 
    in.close();
}
