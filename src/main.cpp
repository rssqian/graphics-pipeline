#include <GL/glut.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <ctime>
#include <cmath>
#include "model.h"
#include "framebuffer.h"
#include "transform.h"
#include "rasterize.h"
#include "lighting.h"
using namespace std;

#define PI 3.14159265

Model** modelPtr;

/* frame size */
int screenWidth = 800;
int screenHeight = 600;
int screenWidth_half = 400;
int screenHeight_half = 300;

/* default font */
void* font = GLUT_BITMAP_9_BY_15;

/* theta */
double rotateSpeed = 0.05;
/*double thetaX = 0;
double thetaY = 0;
double deltaSize=0;
double deltaX=0;
double deltaY=0;
double deltaZ=0;*/
glm::vec3 theta (0.0f,0.0f,0.0f);
glm::vec3 size (1.0f,1.0f,1.0f);
glm::vec3 translate (0.0f,0.0f,0.0f);

glm::vec3 cameraPos (0.0f,0.0f,1.0f);
glm::vec3 cameraTarget (0.0f,0.0f,0.0f);
glm::vec3 upVector (0.0f,1.0f,0.0f);
float FoV=45.0f;

/*mode*/
//int wireframe_filled; //0-wireframe, 1-filled surface
bool wireframe_filled; //0-wireframe, 1-filled surface
int shading; //0-no shading, 1-flat shading, 2-smooth shading, 3-cell shading
bool projection; //0-orthogonal, 1-perspective
int textureAddressing; //0-wrapping, 1-mirror, 2-clamping

int curModelIdx;
bool culling;
Framebuffer framebuffer(screenWidth, screenHeight);
vec3 color(1.f);

/* model names */
char* modelNames[] = {
	"model/quad.obj"/*,
	"model/couch.obj",
	"model/cessna7KC.obj",
	"model/santa7KC.obj",
	"model/laurana2KC.obj",
	"model/shuttle.obj",
	"model/sphere.obj",
	"model/Miku.obj",
	"model/blaze.obj",
	"model/ateneal.obj",
	"model/venusm.obj",
	"model/bunnyC.obj",
	"model/duck4KN.obj",
	"model/happy10KN.obj",
	"model/dragon10KN.obj",
	"model/elephant16KN.obj",
	"model/Statue_of_Liberty.obj",
	"model/Nissan_Pathfinder.obj"*/
};
const int numModels = sizeof(modelNames) / sizeof(char*);

void printHelp() 
{
	printf("===========================================\n");
	printf("  H/h: Show help menu                      \n");
	printf("  B/b: Toggle background color             \n");
	printf("  F1: Save image                           \n");
	printf("  F2/F3: Select model                      \n");
	printf("  F4: Toggle back-face culling             \n");
	printf("  F5: Toggle lighting mode                 \n");
	printf("  F6: Toggle wireframe mode                \n");
	printf("  F7: Toggle texture addressing mode       \n");
	printf("  F12: Quit                                \n");
	printf("  q/e: scale                               \n");
	printf("  w/s: Up and down                         \n");
	printf("  a/d: Left and right                      \n");
	printf("  UP/DOWN: Rotate along x-axis             \n");
	printf("  LEFT/RIGHT: Rotate along y-axis          \n");
	printf("  PU/PD: forward and backward              \n");
	printf("===========================================\n\n");
}

void renderBitmapString(glm::vec3 pos,void* font,char* string)
{
	char* c;
	glRasterPos2f(pos.x,pos.y);
	for (c=string; *c != '\0'; c++) {
		glutBitmapCharacter(font,*c);
	}
}

void init() 
{
	modelPtr = new Model*[numModels];
	for(int i = 0; i < numModels; ++i) {
		/* load models */
		modelPtr[i] = readObj(modelNames[i]);

		/* normalize coordinates to [-0.5, +0.5] */
		float xmax, xmin, ymax, ymin, zmax, zmin, longest;
		float xmean, ymean, zmean;
		xmax = xmin = modelPtr[i]->vertices[3];
		ymax = ymin = modelPtr[i]->vertices[4];
		zmax = zmin = modelPtr[i]->vertices[5];
		for(int v = 2; v <= modelPtr[i]->numVertices; ++v) {
			xmax = max(xmax, modelPtr[i]->vertices[3*v]);
			xmin = min(xmin, modelPtr[i]->vertices[3*v]);
			ymax = max(ymax, modelPtr[i]->vertices[3*v+1]);
			ymin = min(ymin, modelPtr[i]->vertices[3*v+1]);
			zmax = max(zmax, modelPtr[i]->vertices[3*v+2]);
			zmin = min(zmin, modelPtr[i]->vertices[3*v+2]);
		}
		longest = max(xmax - xmin, ymax - ymin);
		longest = max(longest, zmax - zmin);
		xmean = 0.5f*(xmax + xmin);
		ymean = 0.5f*(ymax + ymin);
		zmean = 0.5f*(zmax + zmin);
		
		for(int v = 1; v <= modelPtr[i]->numVertices; ++v) {
			modelPtr[i]->vertices[3*v  ] = (modelPtr[i]->vertices[3*v  ] - xmean)/longest;
			modelPtr[i]->vertices[3*v+1] = (modelPtr[i]->vertices[3*v+1] - ymean)/longest;
			modelPtr[i]->vertices[3*v+2] = (modelPtr[i]->vertices[3*v+2] - zmean)/longest;
		}
	}

	/* initialize parameters */
	curModelIdx = 0;
	culling = true;
	wireframe_filled = 0; //0-wireframe, 1-filled surface
	shading = 0; //0-no shading, 1-flat shading, 2-smooth shading
	projection = 0; //0-orthogonal, 1-perspective
	textureAddressing = 0; //0-wrapping, 1-mirror, 2-clamping
}

void displayFunc() 
{
	framebuffer.clear();

	// Set MVP
	glm::mat4 modelMatrix = model_translation(translate) 
						* model_scale(size) 
						* model_rotation(theta);
	glm::mat4 viewMatrix = glm::lookAt(cameraPos,cameraTarget,upVector);
	glm::mat4 projectionMatrix;
	if (projection==1) {
		projectionMatrix = glm::perspective(FoV,1.0f/1.0f,0.1f,100.0f);
	} else {
		projectionMatrix = glm::ortho(-1.0f,1.0f,-1.0f,1.0f,-1.0f,1.0f);
	}

	for (int i=0; i<modelPtr[curModelIdx]->numTriangles; i++) {
		Triangle* trianglePtr = modelPtr[curModelIdx]->triangles;
		float* verticePtr = modelPtr[curModelIdx]->vertices;
		float* normalPtr = modelPtr[curModelIdx]->normals;
		/*===texCoord===*/float* texCoordPtr = modelPtr[curModelIdx]->texCoords;
		//ValueTriangle triangle;
/*		vec3 triVertices[3];
		vec3 triNormals[3];*/

		glm::vec4 triVertices[3];
		glm::vec4 triNormals[3];
		/*===texCoord===*/glm::vec3 triTexCoord[3];

		for (int j=0; j<3; j++) {
			triVertices[j].x = verticePtr[3*(trianglePtr[i].vIndices[j])  ];
			triVertices[j].y = verticePtr[3*(trianglePtr[i].vIndices[j])+1];
			triVertices[j].z = verticePtr[3*(trianglePtr[i].vIndices[j])+2];
			triVertices[j].w = 1;
			/*===texCoord===*/
			//if (wireframe_filled==1 && modelPtr[curModelIdx]->numTexCoords!=0) {
				triTexCoord[j].x = texCoordPtr[2*(trianglePtr[i].tcIndices[j])  ];
				triTexCoord[j].y = texCoordPtr[2*(trianglePtr[i].tcIndices[j])+1];
				triTexCoord[j].z = 1;
			//}
			if (shading==2 && modelPtr[curModelIdx]->numNormals!=0) {
				triNormals[j].x = normalPtr[3*(trianglePtr[i].nIndices[j])  ];
				triNormals[j].y = normalPtr[3*(trianglePtr[i].nIndices[j])+1];
				triNormals[j].z = normalPtr[3*(trianglePtr[i].nIndices[j])+2];
				triNormals[j].w = 1;
			} else {
				triNormals[j].x = 0;
				triNormals[j].y = 0;
				triNormals[j].z = 0;
				triNormals[j].w = 1; // unsure
			}
		}
		Material* mtl = trianglePtr -> mtlptr;

		//model to view space

/*		model2view_rotation(triVertices[0]);
		model2view_rotation(triVertices[1]);
		model2view_rotation(triVertices[2]);*/

/*		model2view_rotation(triNormals[0]);
		model2view_rotation(triNormals[1]);
		model2view_rotation(triNormals[2]);*/

/*		glm::mat4 modelMatrix = model_translation(translate) 
								* model_scale(size) 
								* model_rotation(theta);*/
		
		glm::vec4 modelVertices[3];
		glm::vec4 viewVertices[3];
		glm::vec4 MVPVertices[3];
		glm::vec4 modelNormals[3];

		//vertex: scaling->rotation->translation
		//normal: rotation
		for(int j=0;j<3;j++){
			modelVertices[j] = modelMatrix * triVertices[j];
			viewVertices[j] = viewMatrix * modelVertices[j];
			MVPVertices[j] = viewVertices[j];
			MVPVertices[j] = projectionMatrix * viewVertices[j];
			MVPVertices[j].x *= (screenHeight * 0.9);
			MVPVertices[j].y *= (screenHeight * 0.9);
			modelNormals[j] = model_rotation(theta) * triNormals[j];
		}

		glm::vec3 v1 ( modelVertices[0]-modelVertices[1] );
		glm::vec3 v2 ( modelVertices[0]-modelVertices[2] );
		glm::vec3 faceNormals = glm::normalize(glm::cross(v1,v2));

		//glm::mat4 MVPmatrix = projectionMatrix(45.0f) * 
		//					  viewMatrix(glm::vec3(0.0f,0.0f,1.0f)) *
		//					  modelMatrix(glm::vec3(0.0f),glm::vec3(thetaX,thetaY,0.0f),0.0f);

		//Back Face Culling
		if (!backFaceCulling(faceNormals) || !culling) {
			int ix[3],iy[3];
			float iz[3];
			vec3 c;
			glm::vec3 ambient_c,diffuse_c,specular_c;
			if (shading!=0) {
/*				vec3 v1(triVertices[0].x-triVertices[1].x,triVertices[0].y-triVertices[1].y,triVertices[0].z-triVertices[1].z);
				vec3 v2(triVertices[0].x-triVertices[2].x,triVertices[0].y-triVertices[2].y,triVertices[0].z-triVertices[2].z);
				vec3 normal = crossProduct(v1,v2);*/
				lighting(faceNormals,ambient_c,diffuse_c,specular_c);
				c.x = ambient_c.x + diffuse_c.x + specular_c.x;
				c.y = ambient_c.y + diffuse_c.y + specular_c.y;
				c.z = ambient_c.z + diffuse_c.z + specular_c.z;
			} else c = color;
			//toScreenSpace(modelVertices_nglm[0],ix[0],iy[0],iz[0]);
			//toScreenSpace(modelVertices_nglm[1],ix[1],iy[1],iz[1]);
			//toScreenSpace(modelVertices_nglm[2],ix[2],iy[2],iz[2]);

			//====non-glm type====
			//vec3 displayVertices[3];
			//displayVertices[0] = vec3(ix[0],iy[0],iz[0]);
			//displayVertices[1] = vec3(ix[1],iy[1],iz[1]);
			//displayVertices[2] = vec3(ix[2],iy[2],iz[2]);
			//=====glm type=======
			glm::vec3* displayVertices = new glm::vec3[3];
			for (int j=0; j<3;j++)
				displayVertices[j] = glm::vec3(MVPVertices[j].x,MVPVertices[j].y,viewVertices[j].z);
			
			vector<glm::vec3*> displayNormals;
			glm::vec3* temp_normal = new glm::vec3[3];
			for (int j=0; j<3;j++)
				temp_normal[j] = glm::vec3(modelNormals[j].x,modelNormals[j].y,modelNormals[j].z);
			displayNormals.push_back(temp_normal);
			/*===texCoord===*/displayNormals.push_back(triTexCoord);
			//cout << "--- Printing Vertex Data of Triangle ---" << endl; 
			//for (int k=0; k<3; k++) {
			//	cout << MVPVertices[k].x << "," << MVPVertices[k].y << "," << viewVertices[k].z << endl;
			//	cout << triTexCoord[k].x << "," << triTexCoord[k].y << "," << triTexCoord[k].z << endl;
 			//}

			//drawTriangle(ix,iy,iz,c);
			//====non glm type==== if (wireframe_filled==1) drawTriangle(displayVertices,triNormals,c);
			/*====glm type====*/ if (wireframe_filled==1) rasterTriangle(displayVertices,displayNormals,c,mtl);
			else {
				drawLine(MVPVertices[0],MVPVertices[1],vec3(1.f,0.f,0.f));
				drawLine(MVPVertices[1],MVPVertices[2],vec3(1.f,0.f,0.f));
				drawLine(MVPVertices[2],MVPVertices[0],vec3(1.f,0.f,0.f));
			}
			//else drawEdge(ix,iy,iz,vec3(1.f,0.f,0.f));
			//delete [] displayVertices;
			//delete [] temp_normal;

			//cout << "--- Printing Vertex Data of Triangle ---" << endl; 
			//for (int k=0; k<3; k++) {
			//	cout << MVPVertices[k].x << "," << MVPVertices[k].y << "," << viewVertices[k].z << endl;
			//}
		}

		//for Debug purpose (will draw back face culling wireframe)
		/*else {
			int ix[3],iy[3];
			float iz[3];
			toScreenSpace(triVertices[0],ix[0],iy[0],iz[0]);
			toScreenSpace(triVertices[1],ix[1],iy[1],iz[1]);
			toScreenSpace(triVertices[2],ix[2],iy[2],iz[2]);
			//drawTriangle(ix,iy,iz);
			if (wireframe_filled==1) drawEdge(ix,iy,iz,vec3(0.f,0.f,0.5f));
		}*/
	}

    /* display */
	glDrawPixels(screenWidth, screenHeight, GL_RGB, GL_FLOAT, (const GLvoid*)framebuffer.getPixels());
	//renderBitmapString(glm::vec3(-1.f,-1.f,0.f),(void*)font,"TEST");
	glutSwapBuffers();

	/* FPS counter */
	static clock_t prev = clock();
	static clock_t curr;
	static char title[20];
	static double refreshTime = 0.5;
	static int count = 0;
	++count;
	curr = clock();
	double t = (double)(curr - prev)/(double)CLOCKS_PER_SEC;
	//cout << "curr = " << curr << "\tprev = " << prev <<  "\tt = " << t << endl;
	if (t > refreshTime) {
		//cout << ">>  curr = " << curr << "\tprev = " << prev <<  "\tt = " << t << "\tcount = " << count << endl;
		prev = curr;
		if (prev > 1000000) 
			cout << "DEBUG: curr = " << curr << "\tprev = " << prev << endl;
		sprintf(title, "3DMM GPU Pipelining: %.2lf fps",  (double)count/t);
		glutSetWindowTitle(title);
		count = 0;
	}
}


void idleFunc() 
{
	glutPostRedisplay();
}

void keyboardFunc(unsigned char key, int x, int y) 
{
	switch (key) {
/*	// Quit
	case 'q':
	case 'Q':
		exit(0);
		break;*/

	// Help
	case 'h':
	case 'H':
		printHelp();
		break;
/*	// Save image
	case 's':
	case 'S':
		static time_t t;
		static char name[80];
		time(&t);
		strftime(name, sizeof(name), "%Y%m%d%H%M%S.ppm", localtime(&t));
		printf("Save framebuffer to %s\n", name);
		framebuffer.writePPM(name);
		break;
	// Select model
	case 'm':
		curModelIdx = (curModelIdx == numModels - 1)? 0 : (curModelIdx + 1);
		printf("Switch to model \"%s\"\n", modelNames[curModelIdx]);
		break;
	case 'M':
		curModelIdx = (curModelIdx == 0)? (numModels - 1) : (curModelIdx - 1);
		printf("Switch to model \"%s\"\n", modelNames[curModelIdx]);
		break;
	// Back-face culling
	case 'c':
	case 'C':
		culling = !culling;
		break;
	//Shading Mode
	case 'l':
	case 'L':
		if (shading == 2) shading = 0;
		else shading++;
		break;
	//Wireframe Mode
	case 'w':
	case 'W':
		if (wireframe_filled == 1) wireframe_filled = 0;
		else wireframe_filled++;
		break;*/
	//Projection Mode
	case 'p':
	case 'P':
		cout << "change the projection mode \n";
		projection = !projection;
		break;
	// Background color

	// To right or left
	case 'a':
	case 'A':
		//cout << "Toward left \n";
		translate.x-=0.01;
		break;
	case 'd':
	case 'D':
		//cout << "Toward right \n";
		translate.x+=0.01;
		break;

	// Up and down
	case 'w':
	case 'W':
		//cout << "Toward up \n";
		translate.y +=0.01;
		break;
	case 's':
	case 'S':
		//cout << "Toward down \n";
		translate.y-=0.01;
		break;

	// Scale
	case 'Q':
	case 'q':
		//cout << "bigger \n";
		size.x +=10;
		break;
	case 'E':
	case 'e':
		if(size.x>(0.01-1)){
			//cout << "smaller \n";
			size.x -=10;
		}
		else
			cout << "It can's be smaller! \n";
		break;

	// You can add more functions as you like before background.

	case 'b':
	case 'B':
		static bool isBlack = true;
		isBlack = !isBlack;
		framebuffer.setClearColor(isBlack? vec3(0.f) : vec3(1.f));
		break;
	}
	glutPostRedisplay();
}

// Special keys
void specialFunc(int key, int x, int y) 
{
	switch (key) {
	case GLUT_KEY_RIGHT:
		theta.y = (theta.y > PI*2)? 0 : (theta.y + rotateSpeed);
		break;
	case GLUT_KEY_LEFT:
		theta.y = (theta.y < 0)? (PI*2) : (theta.y - rotateSpeed);
		break;
	case GLUT_KEY_UP:
		theta.x = (theta.x < 0)? (PI*2) : (theta.x - rotateSpeed);
		break;
	case GLUT_KEY_DOWN:
		theta.x = (theta.x > PI*2)? 0 : (theta.x + rotateSpeed);
		break;


	// forward or backward
	case GLUT_KEY_PAGE_UP:
		//cout << "Forward \n";
        translate.z-=10;
		break;
	case GLUT_KEY_PAGE_DOWN:
		//cout << "Backward \n";
		translate.z+=10;
		break;


	// Save image
	case GLUT_KEY_F1:
		static time_t t;
		static char name[80];
		time(&t);
		strftime(name, sizeof(name), "%Y%m%d%H%M%S.ppm", localtime(&t));
		printf("Save framebuffer to %s\n", name);
		framebuffer.writePPM(name);
		break;
	// Select model
	case GLUT_KEY_F2:
		curModelIdx = (curModelIdx == numModels - 1)? 0 : (curModelIdx + 1);
		printf("Switch to model \"%s\"\n", modelNames[curModelIdx]);
		break;
	case GLUT_KEY_F3:
		curModelIdx = (curModelIdx == 0)? (numModels - 1) : (curModelIdx - 1);
		printf("Switch to model \"%s\"\n", modelNames[curModelIdx]);
		break;
	// Back-face culling
	case GLUT_KEY_F4:
		culling = !culling;
		break;
	//Shading Mode
	case GLUT_KEY_F5:
		if (shading == 3) shading = 0;
		else shading++;
		break;
	//Wireframe Mode
	case GLUT_KEY_F6:
//		if (wireframe_filled == 1) wireframe_filled = 0;
//		else wireframe_filled++;
		wireframe_filled = !wireframe_filled;
		break;
	case GLUT_KEY_F7:
		if (textureAddressing == 2) textureAddressing = 0;
		else textureAddressing++;
		break;
	// Quit
	case GLUT_KEY_F12:
		exit(0);
		break;

	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(screenWidth, screenHeight);
	glutCreateWindow("3DMM HW#1 Rasterization");

	init();

	glutDisplayFunc(displayFunc);
	glutIdleFunc(idleFunc);
	// glutMouseFunc(mouseFunc);
	glutKeyboardFunc(keyboardFunc);
	glutSpecialFunc(specialFunc);

	glutMainLoop();
	
	for(int i = 0; i < numModels; ++i) {
		if(modelPtr[i]) delete [] modelPtr[i];
	}
	if(modelPtr) delete [] modelPtr;

	return 0;
}