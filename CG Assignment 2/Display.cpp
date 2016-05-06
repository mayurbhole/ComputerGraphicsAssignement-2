#include "View.h"
#include "Controller.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>

using namespace std;

ReadPlyFile rpfObj;

int View::lightFlag=1;
int View::lightSubFlag=1;
int View::spin=0;

View::View()
{

    readObj.parsePly();

}

View *vptr= NULL;

extern "C" void disp_callback_wrapper()
{
    vptr->dispCallBack();
}

void View::setupDisplayCallBack()
{
    vptr= this;
    glutDisplayFunc(disp_callback_wrapper);
}

void View::dispCallBack()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glOrtho(-0.25, 0.25, -0.25, 0.25, -0.25, 0.25);
    glPushMatrix();

    readObj.display();

    glPopMatrix();
    glutSwapBuffers();
}


void View::initLighting()
{
	if((View::lightFlag) == 1)
	{

		// Use light0
		glClearColor (0.0, 0.0, 0.0, 0.0);
		glDisable(GL_LIGHT1);
		glShadeModel (GL_SMOOTH);

		GLfloat specMat[] = { 1.0, 1.0, 1.0, 1.0 };   //directional
		GLfloat shineMat[] = { 50.0 };
		GLfloat lightPos[] = { -1.0, 1.0, -1.0, 0.0 };
		GLfloat ambient0[]={1.0, 1.0, 1.0, 1.0};
		GLfloat matClr[] = {0.0f, 1.0f, 0.5f, 1.0f};


		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient0);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, matClr);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specMat);
		glMaterialfv(GL_FRONT, GL_SHININESS, shineMat);

		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
//		glLightfv(GL_LIGHT0, GL_DIFFUSE, redLight);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_NORMALIZE);


	}

	else if(View::lightFlag == 2)
	{
     //   cout<<"\n\n\n\nInside lf2"<<endl;
		glShadeModel (GL_SMOOTH);
		GLfloat position[] = { 0.0, 0.0, -1.5, 1.0 };   // point source

		if(View::lightSubFlag==1)
		{

			glRotated ((GLdouble) View::spin, 1.0, 0.0, 0.0);
			glLightfv (GL_LIGHT0, GL_POSITION, position);
            glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,60.0f);
			glColor3f (10.0, 1.0, 1.0);
			glTranslatef (0.0, 0.0, 5.0);
			glutWireCube (0.1);

		}
		else if(View::lightSubFlag==2)
		{

			glRotated ((GLdouble) View::spin, 0.0, 1.0, 0.0);
			glLightfv (GL_LIGHT0, GL_POSITION, position);
			glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,60.0f);
			glColor3f (0.0, 1.0, 1.0);
			glTranslatef (0.0, 0.0, 5.0);
			glutWireCube (0.1);

		}

	}

glutPostRedisplay();

}
