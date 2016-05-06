#ifndef QUATERNION_H_INCLUDED
#define QUATERNION_H_INCLUDED

#include <GL/gl.h>
#include <GL/glu.h>
#include<GL/glut.h>

class Quaternion
{
    private:
        GLsizei winWidth, winHeight;


    public:

        static bool trackballMove;
        bool trackingMouse=false;
        float angle = 0.0, axis[3], trans[3];
        float lastPos[3] = {0.0, 0.0, 0.0};
        static float qx,qy,qz,qw;
        bool redrawContinue = false;


        int curx, cury;
        int startX, startY;
        float sinAngle;

        Quaternion();
        void setupQuaternionCallBack();
        void mouseMotionCallBack(int x,int y);

        void quatNormalise();
        void createQuaternion();
        void trackball_ptov(int x, int y, int width, int height, float v[3]);
        void startMotion(int x, int y);
        void stopMotion(int x, int y);
        void mouseCallBack(int button, int state, int x, int y);

};





#endif // QUATERNION_H_INCLUDED
