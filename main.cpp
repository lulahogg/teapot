/* main.cpp
 * Last updated: Jan. 27, 2017
 *
 * This program will create a 3D teapot that can be moved by mouse drag or screen touch.
 * See README file for SETUP and ACTION commands.
 *
 * Helpful websites: 
 * https://www.opengl.org/sdk/docs/man/html/glPolygonMode.xhtml
 * https://www.khronos.org/opengles/sdk/docs/man/xhtml/glEnable.xml
 * https://www.ntu.edu.sg/home/ehchua/programming/opengl/CG_Examples.html
*/


#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <cmath>
// GL includes
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>

#include "CameraView.h"
#include "Face.h"

using namespace std;

#define Null 0
#define PI 3.14159 // for calculation use

// Globals
int window_1; // camera view
int screenWidth = 600;
int screenHeight = 600;

CCameraView viewWindow(screenWidth, screenHeight);
bool pan_win1 = true;
int x_win1, y_win1; // mouse cords for window_1
char rotateAxis_win1 = 'z'; // sets rotate to z axis for start

// initialize shape
Shape* shape = new Shape();


// Camera View (normal setup)
void display(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear screen and depth buffer

    // define lighting
    float lt_posit[4] = {   5.0f,   5.0f,   30.0f, 0.0f };
    float lt_ambi[4]  = {   0.5f,   0.5f,   0.5f,  1.0f };
    float lt_diff[4]  = {   0.0f,   1.0f,   0.0f,  0.0f }; // set teapot to green
    
    // define material
    float mat_ambi[4] = {   0.1f,   0.3f,   0.3f,  1.0f };
    float mat_diff[4] = {   0.4f,   0.6f,   0.6f,  1.0f };
    float mat_spec[4] = {   0.3f,   0.3f,   0.3f,  1.0f };
    
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambi);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_diff);
    glMaterialf( GL_FRONT, GL_SHININESS, 5);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, lt_ambi);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lt_diff);
    glEnable(GL_LIGHT0);
    
    glLightfv(GL_LIGHT0, GL_POSITION, lt_posit);

    // call functions
    viewWindow.setShape(*shape);
    viewWindow.projection();
    viewWindow.draw();
    
    glFlush();
    glutSwapBuffers(); // swaps buffers for smooth animation
    
}

// Keys to activate movement or change aspects of object (listed in README file)
void myKeys(unsigned char key, int x, int y)
{
    string filename;
    
    switch(key)
    {
        // exit/quit
        case 'q':
            exit(0); // quit
            
        // scaling
        case '+':   // scaling up object
            shape->setScale(shape->getScale()+0.1);
            break;
        case '-':
            shape->setScale(shape->getScale()-0.1);
            break;
            
        // explode * needs worked on
        case 'e': 
            printf("Explode!\n");
            break;
            
        // shape: polygon
        case 'p':
            shape->setWire(false);
            break;
            
        // shape: wire
        case 'w':
            shape->setWire(true);
            break;
            
        // shading: smooth
        case 's':
            glShadeModel(GL_SMOOTH);
            shape->setSmooth(true);
            break;
            
        // shading: flat
        case 'f':
            glShadeModel(GL_FLAT);
            shape->setSmooth(false);
            break;
            
        // normals: add
        case 'n':
            shape->setNormals(true);
            break;
            
        // normals: remove
        case 'r': 
            shape->setNormals(false);
            break;

		// add teapot * needs worked on
		case '1':
			printf("add teapot\n");
			break;
            
        default: break;
    }
    
    display(); // update camera view
    
}

// Mouse Button (records current mouse coords)
void MouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        x_win1 = x;
        y_win1 = y;
    }
}

// Mouse Movement
void MouseMotion(int x, int y)
{
    
    // changes object parameters
    double dx = (double)x-x_win1;
    double dy = (double)y-y_win1;
    
    
    if(pan_win1){   // change translation
        
        
        shape->setTx(shape->getTx()+dx/50);
        shape->setTy(shape->getTy()-dy/50);
        
        
    }else { // change rotation, only use the x distance
        
        switch(rotateAxis_win1){
            case 'x':
                shape->setRx(shape->getRx()+dx/5);
                break;
            case 'y':
                shape->setRy(shape->getRy()+dx/5);
                break;
            case 'z':
                shape->setRz(shape->getRz()+dx/5);
                break;
            default:
                break;
        }
        
    }
    
    x_win1=x;
    y_win1=y;
    
    display(); // update camera view
}

// Initialize
void myInit(int id) //window_id **************************************
{
    glutSetWindow(id);
    glClearColor(0.0f,0.0f,0.0f,0.0f);  // set background to black
    glViewport(0, 0, screenWidth, screenHeight);
    
    glEnable(GL_DEPTH_TEST); // if enabled, do depth comparisons and update the depth buffer.
    
    // Set the shading model
    
    glShadeModel(GL_SMOOTH);
    
    glEnable(GL_NORMALIZE);
    
    // glPolygonMode(face, mode)
    // GL_FRONT_AND_BACK - front and back polygons
    // GL_FILL - initial value for both front and back facing polygons
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // other obj files can be found at: people.sc.fsu.edu/~jburkardt/data/obj.html
    // GNU LESSER GENERAL PUBLIC LICENSE can be found on sight    
    shape->readfile("teapot.obj"); // read in obj file 
}

// Main
void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(100, 100);
    
    window_1 = glutCreateWindow("3D Creation");
    // function calls
    glutDisplayFunc(display);
    glutKeyboardFunc(myKeys);
    glutMouseFunc (MouseButton);
    glutMotionFunc(MouseMotion);
    
    myInit(window_1);
    
    glutMainLoop();
}





