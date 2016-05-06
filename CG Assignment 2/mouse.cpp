#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Controller.h"
#include "Quaternion.h"
#include <iostream>
#include <string>

using namespace std;


Quaternion quat;

void Controller::mouseCallBack(int button,int state,int x, int y)
{
//	if(button==GLUT_RIGHT_BUTTON) exit(0);

/* holding down left button
      allows user to rotate cube */
	if(button==GLUT_LEFT_BUTTON)
	{
		 switch(state)
	 	{
			case GLUT_DOWN:
							y = winHeight-y;
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

/*
void Controller::mouseMotionCallBack(int x, int y)
{

     float curPos[3],dx, dy, dz;

     // compute position on hemisphere
     quat.trackball_ptov(x, y, winWidth, winHeight, curPos);

     if(Quaternion::trackingMouse)
    {
        // compute the change in position on the hemisphere
        dx = curPos[0]- Quaternion::lastPos[0];
        dy = curPos[1] -Quaternion::lastPos[1];
        dz = curPos[2] - Quaternion::lastPos[2];

	     if (dx || dy || dz)
		 {
		   // compute theta and cross product

		    Quaternion::angle = 90.0 * sqrt(dx*dx + dy*dy + dz*dz);
		    Quaternion::axis[0] = Quaternion::lastPos[1]*curPos[2] -Quaternion::lastPos[2]*curPos[1];
		    Quaternion::axis[1] = Quaternion::lastPos[2]*curPos[0] - Quaternion::lastPos[0]*curPos[2];
		    Quaternion::axis[2] = Quaternion::lastPos[0]*curPos[1] -Quaternion::lastPos[1]*curPos[0];
            quat.quatNormalise();
		    quat.createQuaternion();


		    Quaternion::lastPos[0] = curPos[0];
		    Quaternion::lastPos[1] = curPos[1];
		    Quaternion::lastPos[2] = curPos[2];
		  }
    }
 glutPostRedisplay();

}
*/
