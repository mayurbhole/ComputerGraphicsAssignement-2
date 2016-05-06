#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "Controller.h"
#include "ReadPlyFile.h"
#include <iostream>
#include <string>

using namespace std;



void Controller::keyboardInputCallBack(unsigned char key, int x, int y)
{

    //cout<<"Key : "<<key<<endl;

	switch(key)
	{


		case 's':
                    // Toggle with 's' for lighting
				if(ReadPlyFile::isPerPoly==0)
				{
					ReadPlyFile::isPerPoly=1;
				}
				else
				{
					ReadPlyFile::isPerPoly=0;
				}
				break;

		case '1':

				View::lightFlag=1;

			//	cout<<"lightflag is 1"<<endl;




			break;

		case '2' :				// Moving light
				View::lightFlag=2;

			//	cout<<"lightflag is 2"<<endl;

			break;

		case 'l':
				ReadPlyFile::transX  = ReadPlyFile::transX + 0.5;  // Translation
				break;
		case 'j':
				ReadPlyFile::transX  = ReadPlyFile::transX - 0.5;
				break;
		case 'i':
				ReadPlyFile::transY  = ReadPlyFile::transY + 0.5;
				break;
		case 'k':
				ReadPlyFile::transY  = ReadPlyFile::transY - 0.5;
				break;
		case '+':
				ReadPlyFile::scaling = ReadPlyFile::scaling + 0.05;  // Scaling
				break;
		case '-':
				ReadPlyFile::scaling = ReadPlyFile::scaling - 0.05;
				break;

	}
 glutPostRedisplay();
}


void Controller::specialKeysCallBack(int k, int x, int y)
{

	switch(k)
	{
		case GLUT_KEY_UP:
						View::lightSubFlag=1;
						View::spin = (View::spin + 30) % 360;
						glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN:
						View::lightSubFlag=1;
						View::spin = (View::spin - 30) % 360;
						glutPostRedisplay();
			break;
		case GLUT_KEY_LEFT:
						View::lightSubFlag=2;
						View::spin = (View::spin + 30) % 360;
						glutPostRedisplay();
			break;
		case GLUT_KEY_RIGHT:
						View::lightSubFlag=2;
						View::spin = (View::spin - 30) % 360;
						glutPostRedisplay();
			break;

	}

}
