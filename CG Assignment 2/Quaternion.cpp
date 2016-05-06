
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Quaternion.h"
#include "Controller.h"

#include <iostream>

using namespace std;


Quaternion::Quaternion()
{

}

Quaternion* qptr=NULL;


extern "C" void mouseMotion_wrapper(int x, int y)
{
    qptr->mouseMotionCallBack(x,y);

}
extern "C" void mouse_wrapper(int button, int state, int x, int y)
{
    qptr->mouseCallBack(button,state,x,y);
}

void Quaternion::setupQuaternionCallBack()
{
    qptr= this;
    glutMouseFunc(mouse_wrapper);
    glutMotionFunc(mouseMotion_wrapper);

}


void Quaternion::quatNormalise()
{
	float mag = sqrt((axis[0] *  axis[0] +  axis[1] *  axis[1] +  axis[2] *  axis[2]));

	axis[2] /= mag;
	axis[1] /= mag;
	axis[0]/= mag;


}


void Quaternion::createQuaternion()
{
	sinAngle = sin(angle);

	qw = cos(angle);
	qx = (axis[0] * sinAngle);
	qy = (axis[1]* sinAngle);
	qz = (axis[2]* sinAngle);


}


void Quaternion::trackball_ptov(int x, int y, int width, int height, float v[3])
{

	float d, a;
	// project x,y onto a hemisphere centered within width, height

	v[0] = (2.0*x - width) / width;
	v[1] = (height - 2.0F*y) / height;

	d = sqrt(v[0]*v[0] + v[1]*v[1]);

	v[2] = cos((M_PI/2.0) * ((d < 1.0) ? d : 1.0));
	a = 1.0 / sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);

	v[0] *= a;
	v[1] *= a;
	v[2] *= a;


}

void Quaternion::mouseMotionCallBack(int x, int y)
{
    float curPos[3]={0.0,0.0,0.0};
    float  dx, dy, dz;

     // compute position on hemisphere
     Quaternion::trackball_ptov(x, y, Controller::winWidth, Controller::winHeight, curPos);


     if(trackingMouse)
    {
        // compute the change in position on the hemisphere
        dx = curPos[0]- lastPos[0];
        dy = curPos[1] -lastPos[1];
        dz = curPos[2] - lastPos[2];


	     if (dx || dy || dz)
		 {
		   // compute theta and cross product

		    angle = 90.0 * sqrt(dx*dx + dy*dy + dz*dz);
		    axis[0] = lastPos[1]*curPos[2] -lastPos[2]*curPos[1];
		    axis[1] = lastPos[2]*curPos[0] - lastPos[0]*curPos[2];
		    axis[2] = lastPos[0]*curPos[1] -lastPos[1]*curPos[0];
		    Quaternion::quatNormalise();
		    Quaternion::createQuaternion();

		    lastPos[0] = curPos[0];
		    lastPos[1] = curPos[1];
		    lastPos[2] = curPos[2];
		  }
    }
 glutPostRedisplay();

}


void Quaternion::startMotion(int x, int y)
{

  trackingMouse = true;
  redrawContinue = false;
  startX = x;
  startY = y;
  curx = x;
  cury = y;


  Quaternion::trackball_ptov(x, y, Controller::winWidth, Controller::winHeight, lastPos);
  trackballMove=true;
}

void Quaternion::stopMotion(int x, int y)
{
    trackingMouse = false;

  /* check if position has changed */
    if (startX != x || startY != y)
	     redrawContinue = false;
    else
    {
	     angle = 0.0;
	     redrawContinue = false;
	     trackballMove = false;
    }
}


void Quaternion::mouseCallBack(int button, int state, int x, int y)
{

/* holding down left button
      allows user to rotate cube */
	if(button==GLUT_LEFT_BUTTON)
	{
		 switch(state)
	 	{
			case GLUT_DOWN:
							y = Controller::winHeight-y;
							Quaternion::startMotion( x,y);


					break;
			case GLUT_UP:
							Quaternion::stopMotion( x,y);
					break;

		}
	}

	else if(button==GLUT_RIGHT_BUTTON)
	{
		exit(0);
	}
 }
