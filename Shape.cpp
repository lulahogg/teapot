// Shape.cpp

#include "Shape.h"
 
Shape::Shape()
{
	// customized to teapot
	tx = -.98;
	ty = -.20;
	tz = -1;
	rx = -0.2;
	ry = 20;
	rz = 0.4;
	scale = 0.1;
    
	smooth = true;
	normals = false;  
	wire =  false;
	
    // read in mesh
	mesh = new Mesh(this);
	mesh->makeSurfaceMesh();
}

// remove mesh
Shape::~Shape(){

	delete mesh;
}

// rhs: right hand side
Shape& Shape::operator=(const Shape& rhs)
{
	tx = rhs.tx;
	ty = rhs.ty;
	tz = rhs.tz;
	rx = rhs.rx;
	ry = rhs.ry;
	rz = rhs.rz;
	scale = rhs.scale;
	smooth = rhs.smooth;
	normals = rhs.normals;
	wire = rhs.wire;
	return * this;
}


void Shape::draw()
{
	mesh->draw();
}

void Shape::readfile(string filename)
{
	mesh->readfile(filename);
}

