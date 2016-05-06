#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Controller.h"
#include <iostream>

GLsizei Controller::winWidth;
GLsizei Controller::winHeight;

Controller::Controller(View *vw): vwObj(vw)
{

}

static Controller* cptr=NULL;  // 2nd method-Declaring static


void Controller::keyboardInput_wrapper(unsigned char key, int x, int y)
{
    cptr->keyboardInputCallBack(key,x,y);

}

void Controller::specialKeys_wrapper(int key, int x, int y)
{
    cptr->specialKeysCallBack(key,x,y);
}

/*
void Controller::mouse_wrapper(int button, int state, int x, int y)
{
    cptr->mouseCallBack(button,state,x,y);
}

*/

void Controller::reshape_wrapper(GLsizei w, GLsizei h)
{
    cptr->reshapeCallBack(w,h);

}

void Controller::reshapeCallBack(GLsizei w, GLsizei h)
{
	glViewport(0,0,w,h);
	winWidth=w;
	winHeight=h;
   // glMatrixMode(GL_MODELVIEW);
}

void Controller::setupControllerCallBack()
{
    cptr = this;

    glutKeyboardFunc(keyboardInput_wrapper);
    glutSpecialFunc(specialKeys_wrapper);
    glutReshapeFunc(reshape_wrapper);
//    glutMouseFunc(mouse_wrapper);


}


