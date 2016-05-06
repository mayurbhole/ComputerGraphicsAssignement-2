#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

#include "View.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class Controller
{
    private:

        View *vwObj;


    public:


       static  GLsizei winWidth;
       static  GLsizei winHeight;


        Controller(View *vw);  // Passing View object to constructor
        void setupControllerCallBack();
        void keyboardInputCallBack(unsigned char key, int x, int y);
        void specialKeysCallBack(int key, int x, int y);
        void reshapeCallBack(GLsizei w, GLsizei h);
        void mouseCallBack(int button,int state,int x,int y);

        static void specialKeys_wrapper(int key, int x, int y);
        static void keyboardInput_wrapper(unsigned char key, int x, int y);
        static void reshape_wrapper(GLsizei w, GLsizei h);
        static void mouse_wrapper(int button, int state, int x, int y);
        static void mouseMotion_wrapper(int x, int y);

};


#endif // CONTROLLER_H_INCLUDED
