#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Controller.h"
#include "Quaternion.h"
#include "View.h"
#include <iostream>
#include <string.h>

using namespace std;




int main(int argc, char** argv)
{

	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Assignment 2 ");

    View vw;
    vw.setupDisplayCallBack();

    Controller cntr(&vw);
    cntr.setupControllerCallBack();
    Quaternion qua;
    qua.setupQuaternionCallBack();

    glFlush();
	glutMainLoop();
	return 0;
}
