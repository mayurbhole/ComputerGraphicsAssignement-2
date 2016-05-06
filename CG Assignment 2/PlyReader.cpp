#include "ReadPlyFile.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "View.h"
#include "Quaternion.h"

using namespace std;

float  Quaternion::qx=0.0;
float  Quaternion::qy=0.0;
float  Quaternion::qz=0.0;
float  Quaternion::qw=0.0;
bool Quaternion::trackballMove=false;


View vw2;

int ReadPlyFile::isPerPoly=1;

float ReadPlyFile::transX=0.0;
float ReadPlyFile::transY=0.0;
float ReadPlyFile::transZ=0.0;
float ReadPlyFile::scaling=1.0;


ReadPlyFile::ReadPlyFile()
{

}

void ReadPlyFile::parsePly()
{
	int i=0,j=1,headFlag=0,vertFlag=0,temp;
	char str[500],tempStr1[20],tempStr2[20],c;

	if ((fptr = fopen("bunny.ply", "r")) == NULL)
	{
//		printf("File not found !");
		return;
	}

	// Get the comments.
	while (strstr(str, "comment")) {

		fgets(str, 100, fptr);
	//	puts(str);
	}

	while(!feof(fptr))
	{
		if(fgets(str,200,fptr))
		{
			if(headFlag!=1)
			{  // Read header.                         // From internet tutorial
				if(strstr(str,"element vert"))
				{
					sscanf(str,"%s %s %d",tempStr1,tempStr2,&numVert);
				}
				if(strstr(str,"element face"))
				{
					sscanf(str,"%s %s %d",tempStr1,tempStr2,&numFaces);
				}
				if(strstr(str,"end_header"))
				{
						headFlag=1;
				}
				ReadPlyFile::initVertNorm();
			}

			else if(vertFlag!=1)
			{
				// Scan Vertices. In this ply file, each vertex has 5 properties. So 5 arrays
				if(i<numVert)
				{
					sscanf(str,"%f %f %f %f %f",&pVertex[i][0],&pVertex[i][1],&pVertex[i][2],&pVertex[i][3],&pVertex[i][4]);
					i++;
				}
				else
				{
					vertFlag=1;
					sscanf(str,"%d %d %d %d ",&temp,&pFace[0][0],&pFace[0][1],&pFace[0][2]);
					calcResNorm(0,pVertex[pFace[0][0]],pVertex[pFace[0][1]],pVertex[pFace[0][2]]);
				}
			}

			else
			{
				// Scan faces. The 3 which is stored in temp indicates the triangle. For quadrilateral 4 is stored.
				if(j<numFaces)
				{
					sscanf(str,"%d %d %d %d ",&temp,&pFace[j][0],&pFace[j][1],&pFace[j][2]);
					calcResNorm(j,pVertex[pFace[j][0]],pVertex[pFace[j][1]],pVertex[pFace[j][2]]);
					j++;
				}
			}
		}
	}
}

void ReadPlyFile::display()
{
   	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	vw2.initLighting();
   	glLoadIdentity();
    glTranslatef(ReadPlyFile::transX,ReadPlyFile::transY,ReadPlyFile::transZ);
    glScalef(ReadPlyFile::scaling,ReadPlyFile::scaling,ReadPlyFile::scaling);
    glOrtho(-0.25, 0.25, -0.25, 0.25, -0.25, 0.25);  // defines view volume.

    glPushMatrix();

	if (Quaternion::trackballMove)
	{
//	cout<<"Quat"<<Quaternion::qx<<endl;

		float x2 = Quaternion::qx * Quaternion::qx;
		float y2 = Quaternion::qy * Quaternion::qy;
		float z2 = Quaternion::qz * Quaternion::qz;
		float xy = Quaternion::qx * Quaternion::qy;
		float xz = Quaternion::qx * Quaternion::qz;
		float yz = Quaternion::qy * Quaternion::qz;
		float wx = Quaternion::qw * Quaternion::qx;
		float wy = Quaternion::qw * Quaternion::qy;
		float wz = Quaternion::qw * Quaternion::qz;

		GLdouble m[16] = {1.0 - 2.0 * (y2  + z2 ),2.0f * (xy - wz), 2.0f * (xz + wy),0.0f,2.0f * (xy + wz),1.0f - 2.0f * (x2 + z2),2.0f * (yz - wx),0.0f,2.0f * (xz - wy), 2.0f * (yz + wx),1.0f - 2.0f * (x2 + y2),0.0f,0.0f,0.0f,0.0f,1.0f};
		glMultMatrixd(m);

	}



	if(ReadPlyFile::isPerPoly==1)  // per Polygon                As explained in class. From notebook
	{
		for(int i=0;i<numFaces;i++)
		{
			glBegin(GL_TRIANGLE_STRIP);
			glNormal3f(norm[i][0],norm[i][1],norm[i][2]);  // Only one resNorm for each face

			for(j=0;j<3;j++)
			{
				glVertex3f(pVertex[pFace[i][j]][0],pVertex[pFace[i][j]][1],pVertex[pFace[i][j]][2]);
			}
			glEnd();
		}
	}

	else  				// per Vertex.
	{
		for(int i=0;i<numFaces;i++)
		{
			glBegin(GL_TRIANGLE_STRIP);

			for(j=0;j<3;j++)
			{   // resNorm for each vertex
				glNormal3f((pVertNorm[pFace[i][j]][0]/pVertNorm[pFace[i][j]][3]),(pVertNorm[pFace[i][j]][1]/pVertNorm[pFace[i][j]][3]),(pVertNorm[pFace[i][j]][2]/pVertNorm[pFace[i][j]][3]));
				glVertex3f(pVertex[pFace[i][j]][0],pVertex[pFace[i][j]][1],pVertex[pFace[i][j]][2]);
			}

			glEnd();
		}
	}


   glPopMatrix();
   glutSwapBuffers();

}

void ReadPlyFile::initVertNorm()
{
	int i;
	for(i=0;i<numVert;i++)
	{
		pVertNorm[i][0]=0;
		pVertNorm[i][1]=0;
		pVertNorm[i][2]=0;
		pVertNorm[i][3]=0;
	}
}

void ReadPlyFile::calcResNorm( int j,float *coord1, float *coord2, float *coord3 )     // From book: top down approach
{
   float vectP[3], vectQ[3], resNorm[3], mag;

  // Calculate vectors from coordinates.

   vectP[0] = coord1[0] - coord2[0];
   vectP[1] = coord1[1] - coord2[1];
   vectP[2] = coord1[2] - coord2[2];

   vectQ[0] = coord1[0] - coord3[0];
   vectQ[1] = coord1[1] - coord3[1];
   vectQ[2] = coord1[2] - coord3[2];

   // Find the resultant Normal

   resNorm[0] = vectP[1] * vectQ[2] - vectQ[1] * vectP[2];  // For x
   resNorm[1] = vectQ[0] * vectP[2] - vectP[0] * vectQ[2];  // For y
   resNorm[2] = vectP[0] * vectQ[1] - vectQ[0] * vectP[1];  // For z

	// Calculate magnitude and normalize

   // To obtain proper lighting, normalise the vector, i.e. make it unit length.
   // OpenGL takes into consideration the length of the normal vector when computing lighting.
   // Normalisation implies first computing the lenght of the vector, and then dividing each component by the vectors length.


	mag = sqrt( resNorm[0]*resNorm[0] + resNorm[1]*resNorm[1] + resNorm[2]*resNorm[2] );

	// Store the normalized resultant vector in norm array
	norm[j][0] = resNorm[0]/mag;  // for x coord
	norm[j][1] = resNorm[1]/mag;  // for y coord
	norm[j][2] = resNorm[2]/mag;  // for z coord

 	// For per vertex calculations:

 	// Since each vertex is shared by 4 faces,
 	// The normal at a vertex is computed as the normalised sum of all the unit length normals for each face the vertex shares.

	pVertNorm[pFace[j][0]][0]+= norm[j][0];
	pVertNorm[pFace[j][1]][0]+= norm[j][0];    // For x
	pVertNorm[pFace[j][2]][0]+= norm[j][0];

	pVertNorm[pFace[j][0]][1]+= norm[j][1];
	pVertNorm[pFace[j][1]][1]+= norm[j][1];    // For y
 	pVertNorm[pFace[j][2]][1]+= norm[j][1];

	pVertNorm[pFace[j][0]][2]+= norm[j][2];
	pVertNorm[pFace[j][1]][2]+= norm[j][2];    // For z
	pVertNorm[pFace[j][2]][2]+= norm[j][2];

	pVertNorm[pFace[j][0]][3]+= 1.0;
	pVertNorm[pFace[j][1]][3]+= 1.0;
 	pVertNorm[pFace[j][2]][3]+= 1.0;
}
