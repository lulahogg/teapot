# teapot

OpenGL & C++

This program will create a teapot that upon receving a touch/click
event will respond with a geometry explosion and then reset


**SETUP (Windows)**

- Microsoft Visual Studio: https://www.visualstudio.com/vs/visual-studio-express/
- glew: https://sourceforge.net/projects/glew/files/glew/1.9.0/
- freeglut: http://www.transmissionzero.co.uk/software/freeglut-devel/
	- Download freeglut 3.0.0 for MSVC

- After glew and freeglut are downloaded:
	- glew
		- glew-1.9.0-win64.zip
			- glew-1.9.0
				- bin
				- doc
				- include
					- GL
				- lib 
	- freeglut
		- freeglut-MSVC-3.0.0-2.mp.zip
			- freeglut
				- bin
				- include
					- GL
				- lib
- Step 1:
	- open OS(C:)
	- find System32 and SysWOW64
		- drag glew32.dll (found in glew bin folder) into both
		- drag freeglut.dll (found in freeglut bin folder) into both
- Step 2:
	- open OS(C:)
	- Program Files (x86)
	- Microsoft Visual Studio 11.0
	- VC
	- include
		- create new folder named gl
	- gl
		- drag all header files into this folder from glew/freeglut GL folder   
- Step 3:
	- open Microsoft Visual Studio
		- create new project
			- Win32 Console Application
				- Name: HelloWorld
	- new project should be created
		- right click on Source Files
			- Add
				- New Item...
	- click C++ File(.cpp)
		- change name to main.cpp
		- click Add
	- click PROJECT
		- HelloWorld Properties...
			- Configuration Properties
				- Linker
					- Input
	- in Additional Dependencies add
		- opengl32.lib;glu32.lib;freeglut.lib;
	- hit ok and SETUP complete

**TEST CODE (add to main.cpp)**

#include <iostream>
#include <gl/freeglut.h>

using namespace std;

void display(void){

    glClear(GL_COLOR_BUFFER_BIT);
    glutSolidTeapot(.5);
    glFlush();

}

int main(int argc, char** argv){

    glutInit(&argc, argv);


    glutInitDisplayMode(GLUT_SINGLE);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Exploding Teapot");

    glutDisplayFunc(display); //calls display()

    glutMainLoop(); //keeps window up


    return 0;
}
	
