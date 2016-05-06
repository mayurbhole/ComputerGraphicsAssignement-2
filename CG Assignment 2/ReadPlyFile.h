#ifndef READPLYFILE_H_INCLUDED
#define READPLYFILE_H_INCLUDED

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define VERTICES 50000
#define FACES 100000



class ReadPlyFile
{

    private:
        FILE *fptr;

    public:
        static int isPerPoly;
        static float transX,transY,transZ,scaling;
        int c,j,numVert,numFaces,pFace[FACES][4];
        float pVertex[VERTICES][5], pVertNorm[VERTICES][4], norm[FACES][3];


//        GLfloat redLight[] = { 1.0, 1.0, 1.0, 1.0 };

        ReadPlyFile();    // Constructor---------- Why to put constructor in public

        void parsePly();
        void initVertNorm();
        void calcResNorm(int j, float *coord1, float *coord2, float *coord3 );
        void display();

};


#endif // READPLYFILE_H_INCLUDED
