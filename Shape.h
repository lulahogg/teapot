// Shape.h

#ifndef SHAPE_H
#define SHAPE_H

#define PI 3.14159
class Mesh;
    
#include "Mesh.h"

// takes in obj file data and records data
class Shape
{
	public:
		Mesh* mesh;
		Shape();
		virtual	~Shape();
		void draw();
		void readfile(string filename);
		
		double getTx() {return tx;}
		double getTy() {return ty;}
		double getTz() {return tz;}
		double getRx() {return rx;}
		double getRy() {return ry;}
		double getRz() {return rz;}
		double getScale()  {return scale;}


		void setTx(double x) {tx=x;}
		void setTy(double y) {ty=y;}
		void setTz(double z) {tz=z;}
		void setRx(double x) {rx=x;}
		void setRy(double y) {ry=y;}
		void setRz(double z) {rz=z;}
		void setScale(double s)  {scale=s;}
		

		void setSmooth(bool s){smooth = s;};
		bool getSmooth(){return smooth;};
		void setNormals(bool n){normals = n;};
		bool getNormals(){return normals;};

		void setWire(bool w){wire = w;};
		bool getWire(){return wire;};
		Shape& operator=(const Shape& rhs);
		
	protected:
		double tx, ty, tz, rx, ry, rz, scale;
		bool smooth, normals, wire;
};

#endif
