// CameraView.h
   
#ifndef CAMERAVIEW_H
#define CAMERAVIEW_H
 
#include <iostream>
#include <windows.h>
#include <vector>
#include <cmath>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>

#include "Camera.h"
#include "Vector3d.h"
#include "Shape.h"

using namespace std;
 
class CCameraView  
{
private:
    int width;
    int height;
 
    Shape *shape;  // set shape
    CCamera camera; // set camera
 
public:
    CCameraView(int w, int h);
    virtual ~CCameraView();
    Shape& getShape()  {return *shape;}
 
public:
 
    void setShape(Shape& shape2) {shape = &shape2;}
 
    void projection(); // perspective projection for camera
    void draw();  
 
    void cameraTransformation(); // camera's viewing transformation
    void shapeTransformation(); // object transformation
 
 
};
 
#endif 
