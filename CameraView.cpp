// CameraView.cpp
// CCameraView class
// https://www.opengl.org/archives/resources/faq/technical/viewing.htm
// https://www.opengl.org/sdk/docs/man2/xhtml/gluLookAt.xml

#include <iostream>
#include <windows.h>
#include <vector>
#include <cmath>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>

#include "CameraView.h"
 
using namespace std;
 
CCameraView::CCameraView(int w, int h)
{
    width = w;
    height = h;
 
    camera.init();
}

CCameraView::~CCameraView()
{
    delete shape;
}
 
void CCameraView::projection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(camera.getLeft(), camera.getRight(), camera.getBottom(), camera.getTop(), camera.getNear(), camera.getFar());
}
 
void CCameraView::draw()  
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
 
    cameraTransformation();
 
    glPushMatrix();
        shapeTransformation();
        shape->draw();
    
    glPopMatrix();
}
 

void CCameraView::cameraTransformation()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
 
 
void CCameraView::shapeTransformation()
{
    glTranslated(shape->getTx(), shape->getTy(), shape->getTz());
    
    glRotated(shape->getRx(), 1, 0, 0);
    glRotated(shape->getRy(), 0, 1, 0);
    glRotated(shape->getRz(), 0, 0, 1);
    
    glScaled(shape->getScale(), shape->getScale(), shape->getScale());
}









