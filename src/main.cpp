#define _GLOBAL_VAR
#include <GL/freeglut.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <WinBase.h>
#include "model.h"
#include "framebuffer.h"
#include "transform.h"
#include "rasterize.h"
#include "lighting.h"
#include "ui.h"
using namespace std;

#define PI 3.14159265

Model** modelPtr;

/* frame size */
int screenWidth = 1280;
int screenHeight = 720;
int screenWidth_half = screenWidth/2;
int screenHeight_half = screenHeight/2;

/* theta */
double rotateSpeed = 0.05;
glm::vec3 theta (0.0f, 0.5f, 0.0f);
glm::vec3 size (1.5f, 1.5f, 1.5f);
glm::vec3 translate (0.0f, 0.0f, 0.0f);

glm::vec3 cameraPos (0.0f, 0.0f, 1.0f);
glm::vec3 cameraTarget (0.0f, 0.0f, 0.0f);
glm::vec3 upVector (0.0f, 1.0f, 0.0f);
float FoV=45.0f;

/*mode*/
bool wireframe;		//0-wireframe off, 1-wireframe on
bool normalDisplay;
bool solid;			//0-solid mode off, 1-solid mode on
int shading;		//0-z shading, 1-flat shading, 2-smooth shading, 3-cell shading, 4-normal shading
bool projection;	 //0-orthogonal, 1-perspective
int textureAddressing; //0-wrapping, 1-mirror, 2-clamping
bool textureDisplay;
int filterMode;		//0-off, 1-nearest, 2-linear, 3-nearest_mipmap_nearest, 
					//4-Linear-Mipmap-Nearest, 5-Nearest-Mipmap-Linear, 6-Linear-Mipmap-Linear
int demoMode;		//0-off, 1-wireframe, 2-flat shading, 3-phong shading, 4-cel shading, 5-phong shading with texture,6-normal shading

int curModelIdx;
int numDrawTriangleIdx = 0;
bool culling;
Framebuffer framebuffer(screenWidth, screenHeight);
vec3 color(1.f);

Lighting light;
glm::vec3 ka(0.2f);
glm::vec3 kd(0.8f);
glm::vec3 ks(0.5f);
int ns = 1;

/* model names */
const char* modelNames[] = {
	"model/Deer.obj",
	"model/quad.obj",
	"model/couch.obj",
	//"model/cubeT.obj",
	"model/Nala.obj",
	"model/ball.obj",
	"model/duck.obj",
	"model/ZEBRA.obj",
	"model/Dog.obj",
	"model/texturedknot.obj",
	"model/laurana500.obj",
	//"model/cessna7KC.obj",
	//"model/santa7KC.obj",
	//"model/laurana2KC.obj",
	//"model/shuttle.obj",
	//"model/sphere.obj",
	//"model/KioMiku/Miku.obj",
	"model/Giraffe.obj",
	//"model/blaze.obj"
	//"model/ateneal.obj",
	//"model/venusm.obj",
	//"model/bunnyC.obj"
	//"model/duck4KN.obj",
	//"model/happy10KN.obj",
	//"model/dragon10KN.obj",
	//"model/elephant16KN.obj",
	//"model/Statue_of_Liberty.obj",
	//"model/Nissan_Pathfinder.obj"
};
int numModels = sizeof(modelNames) / sizeof(char*);

void demoModeTransition()
{
	static int demoMode6 = 0;
	switch (demoMode) {
	case 0:
		break;
	case 1:  //wireframe
		demoMode++;
		cout << "DEMO mode: switching to flat shading" << endl;
		culling = true;
		wireframe = 0;
		normalDisplay = 0;
		solid = 1;
		shading = 1; 
		textureAddressing = 0; 
		textureDisplay = 0;
		filterMode = 0;
		numDrawTriangleIdx = 0;
		break;
	case 2:  //flat shading
		demoMode++;
		cout << "DEMO mode: switching to phong shading" << endl;
		culling = true;
		wireframe = 0;
		normalDisplay = 0;
		solid = 1;
		shading = 2;  
		textureAddressing = 0; 
		textureDisplay = 0;
		filterMode = 0;
		numDrawTriangleIdx = 0;
		break;
	case 3:  //phong shading
		demoMode++;
		cout << "DEMO mode: switching to cel shading" << endl;
		culling = true;
		wireframe = 0;
		normalDisplay = 0;
		solid = 1;
		shading = 3; 
		textureAddressing = 0; 
		textureDisplay = 0;
		filterMode = 0;
		numDrawTriangleIdx = 0;
		break;
	case 4:  //cel shading
		demoMode++;
		cout << "DEMO mode: switching to phong shading with texture" << endl;
		culling = true;
		wireframe = 0;
		normalDisplay = 0;
		solid = 1;
		shading = 2; 
		textureAddressing = 0; 
		textureDisplay = 1;
		filterMode = 1;
		numDrawTriangleIdx = 0;
		break;
	case 5:  //phong shading with texture
		demoMode++;
		cout << "DEMO mode: switching to normal shading" << endl;
		culling = true;
		wireframe = 0;
		normalDisplay = 0;
		solid = 1;
		shading = 4; 
		textureAddressing = 0; 
		textureDisplay = 0;
		filterMode = 0;
		numDrawTriangleIdx = 0;
		break;
	case 6:  //normal shading
		if (demoMode6==300) {
			demoMode = 1;
			cout << "DEMO mode: switching to wireframe" << endl;
			culling = false;
			wireframe = 1;
			normalDisplay = 0;
			solid = 0;
			shading = 1; 
			textureAddressing = 0; 
			textureDisplay = 0;
			filterMode = 0;
			numDrawTriangleIdx = 0;
			demoMode6 = 0;
		} else {
			demoMode6++;
		}
		break;
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
			modelPtr[i]->vertices[3*v	] = (modelPtr[i]->vertices[3*v	] - xmean)/longest;
			modelPtr[i]->vertices[3*v+1] = (modelPtr[i]->vertices[3*v+1] - ymean)/longest;
			modelPtr[i]->vertices[3*v+2] = (modelPtr[i]->vertices[3*v+2] - zmean)/longest;
		}
	}

	/* initialize parameters */
	curModelIdx = 0;
	culling = true;
	wireframe = 0;
	normalDisplay = 0;
	solid = 1;
	shading = 1; //0-no shading, 1-flat shading, 2-smooth shading 3-Cell shading, 4-normal shading 
	projection = 0; //0-orthogonal, 1-perspective
	textureAddressing = 0; //0-wrapping, 1-mirror, 2-clamping
	textureDisplay = 0;
	filterMode = 0;
	demoMode = 0;
}

void displayFunc() 
{
	//if (demoMode==0 || demoMode==1) 
		framebuffer.clear();

	// Set MVP and viewport
	glm::mat4 modelMatrix = model_translation(translate) 
						* model_scale(size) 
						* model_rotation(theta);
	glm::mat4 viewMatrix = glm::lookAt(cameraPos,cameraTarget,upVector);
	glm::mat4 projectionMatrix;
	if (projection==1) {
		projectionMatrix = glm::mat4(1);
		projectionMatrix[3][3]=0;
		projectionMatrix[2][3]=-1;
	} else {
		projectionMatrix = glm::mat4(1);
		projectionMatrix[2][2]=0;
	}
	glm::mat4 viewportMatrix = glm::mat4(1);
	/*scale*/
	viewportMatrix[0][0]=screenHeight_half;
	viewportMatrix[1][1]=screenHeight_half;
	/*trans*/
	viewportMatrix[0][3]=screenWidth_half;
	viewportMatrix[1][3]=screenHeight_half;

	if (demoMode==0) numDrawTriangleIdx = modelPtr[curModelIdx]->numTriangles;
	else {
		//cout << numDrawTriangleIdx << endl;
		if (demoMode==1) numDrawTriangleIdx += 16;
		else numDrawTriangleIdx += (40);
		if (numDrawTriangleIdx>modelPtr[curModelIdx]->numTriangles) numDrawTriangleIdx = modelPtr[curModelIdx]->numTriangles;
	}
	for (int i=0; i<modelPtr[curModelIdx]->numTriangles; i++) {
		if (i>=numDrawTriangleIdx) {
			switch (demoMode) {
			case 1:
				culling = true;
				wireframe = 0;
				normalDisplay = 0;
				solid = 0;
				shading = 1;
				break;
			case 2:
				culling = false;
				wireframe = 1;
				normalDisplay = 0;
				solid = 0;
				shading = 1;
				break;
			case 3:
				culling = true;
				wireframe = 0;
				normalDisplay = 0;
				solid = 1;
				shading = 1; 
				textureDisplay = 0;
				break;
			case 4:
				culling = true;
				wireframe = 0;
				normalDisplay = 0;
				solid = 1;
				shading = 2;  
				textureDisplay = 0;
				break;
			case 5:
				culling = true;
				wireframe = 0;
				normalDisplay = 0;
				solid = 1;
				shading = 3; 
				textureDisplay = 0;
				break;
			case 6:
				culling = true;
				wireframe = 0;
				normalDisplay = 0;
				solid = 1;
				shading = 2; 
				textureAddressing = 0; 
				textureDisplay = 1;
				filterMode = 1;
				break;
			}
		} else {
			switch (demoMode) {
			case 1:
				culling = false;
				wireframe = 1;
				normalDisplay = 0;
				solid = 0;
				shading = 1;
				break;
			case 2:
				culling = true;
				wireframe = 0;
				normalDisplay = 0;
				solid = 1;
				shading = 1; 
				textureDisplay = 0;
				break;
			case 3:
				culling = true;
				wireframe = 0;
				normalDisplay = 0;
				solid = 1;
				shading = 2;  
				textureDisplay = 0;
				break;
			case 4:
				culling = true;
				wireframe = 0;
				normalDisplay = 0;
				solid = 1;
				shading = 3; 
				textureDisplay = 0;
				break;
			case 5:
				culling = true;
				wireframe = 0;
				normalDisplay = 0;
				solid = 1;
				shading = 2; 
				textureAddressing = 0; 
				textureDisplay = 1;
				filterMode = 1;
				break;
			case 6:
				culling = true;
				wireframe = 0;
				normalDisplay = 0;
				solid = 1;
				shading = 4; 
				textureDisplay = 0;
				break;
			}
		}
		Triangle* trianglePtr = modelPtr[curModelIdx]->triangles;
		float* verticePtr = modelPtr[curModelIdx]->vertices;
		float* normalPtr = modelPtr[curModelIdx]->normals;
		float* texCoordPtr = modelPtr[curModelIdx]->texCoords;

		glm::vec4 triVertices[3];
		glm::vec4 triNormals[3];
		glm::vec3 triTexCoord[3];

		for (int j=0; j<3; j++) {
			triVertices[j].x = verticePtr[3*(trianglePtr[i].vIndices[j])	];
			triVertices[j].y = verticePtr[3*(trianglePtr[i].vIndices[j])+1];
			triVertices[j].z = verticePtr[3*(trianglePtr[i].vIndices[j])+2];
			triVertices[j].w = 1;
			if (textureDisplay==1 && solid==1 && modelPtr[curModelIdx]->numTexCoords!=0) {
				triTexCoord[j].x = texCoordPtr[2*(trianglePtr[i].tcIndices[j])	];
				triTexCoord[j].y = texCoordPtr[2*(trianglePtr[i].tcIndices[j])+1];
				triTexCoord[j].z = 1;
			} else {
				triTexCoord[j].x = 0;
				triTexCoord[j].y = 0;
				triTexCoord[j].z = 1;
			}
			if ((shading==2 || shading==3 || shading==4) && modelPtr[curModelIdx]->numNormals!=0) {
				triNormals[j].x = normalPtr[3*(trianglePtr[i].nIndices[j])	];
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
		Material* mtl = trianglePtr[i].mtlptr;

		/*===transformation===*/
		glm::vec4 modelVertices[3];
		glm::vec4 MVPVertices[3];
		glm::vec4 modelNormals[3];

 		for(int j=0;j<3;j++) {
			// model space (scaling->rotation->translation)
			modelVertices[j] = modelMatrix * triVertices[j];
			// view space
			modelVertices[j] = viewMatrix * modelVertices[j];
			// projection space
			MVPVertices[j] = projectionMatrix * modelVertices[j];
			MVPVertices[j] = MVPVertices[j] * glm::mat4(1/MVPVertices[j].w);
			// Display space
			MVPVertices[j] = MVPVertices[j]*viewportMatrix;
			MVPVertices[j].z = modelVertices[j].z;
			// Normal : rotation
			modelNormals[j] = model_rotation(theta) * triNormals[j];
 		}
		glm::vec3 v1 ( modelVertices[0]-modelVertices[1] );
		glm::vec3 v2 ( modelVertices[0]-modelVertices[2] );
		glm::vec3 faceNormals = glm::normalize(glm::cross(v1,v2));

		/*===Back Face Culling===*/
		bool cull = backFaceCulling(faceNormals, glm::vec3(modelVertices[0])); //true-need to be culled
		/*if (cull==true && toonShading==true) {
			//MVPVertices[0].z = -1e20;
			//MVPVertices[1].z = -1e20;
			//MVPVertices[2].z = -1e20;
			drawLine(MVPVertices[0],MVPVertices[1],vec3(1.f,0.f,0.f));
			drawLine(MVPVertices[1],MVPVertices[2],vec3(1.f,0.f,0.f));
			drawLine(MVPVertices[2],MVPVertices[0],vec3(1.f,0.f,0.f));
		}*/
		
		if ((cull==false&&culling==true) || culling==false) { 
			int ix[3],iy[3];
			float iz[3];
			vec3 c;
			LightColor KaKdKsIntensity(glm::vec3(1.f),glm::vec3(1.f),glm::vec3(1.f));

			/*===flat shading===*/
			if (shading==1) {
				glm::vec3 centerVertex = glm::vec3(modelVertices[0]+modelVertices[1]+modelVertices[2]) / 3.f;
				//glm::vec3 ambient_c,diffuse_c,specular_c;
				if (textureDisplay && mtl!=nullptr) light.setParameter(mtl->Ka,mtl->Kd,mtl->Ks,mtl->Ns);
				else light.setParameter(ka,kd,ks,ns);
				light.shading(centerVertex, faceNormals,mtl,KaKdKsIntensity);
			}

			/*===Rasteriztion===*/
			glm::vec3* displayVertices = new glm::vec3[3];
			for (int j=0; j<3;j++)
				displayVertices[j] = glm::vec3(MVPVertices[j].x,MVPVertices[j].y,modelVertices[j].z);

			vector<glm::vec3*> displayNormals;
			glm::vec3* temp_normal = new glm::vec3[3];
			for (int j=0; j<3;j++)
				temp_normal[j] = glm::vec3(modelNormals[j].x,modelNormals[j].y,modelNormals[j].z);
			displayNormals.push_back(temp_normal);

			glm::vec3* temp_vertex = new glm::vec3[3];
			for (int j=0; j<3;j++)
				temp_vertex[j] = glm::vec3(modelVertices[j].x,modelVertices[j].y,modelVertices[j].z);
			displayNormals.push_back(temp_vertex);

			if (textureDisplay==1 && solid==1) displayNormals.push_back(triTexCoord);

			if (solid==1) rasterTriangle(displayVertices,displayNormals,mtl,KaKdKsIntensity);

			/*===wireframe mode===*/
			if (wireframe==1) {
				vec3 wireframeColor(1.f);
				if (demoMode != 0) {
					MVPVertices[0].z = -1e20;
					MVPVertices[1].z = -1e20;
					MVPVertices[2].z = -1e20;
					wireframeColor = vec3(0.5f);
				} else {
					MVPVertices[0].z += 0.01f;
					MVPVertices[1].z += 0.01f;
					MVPVertices[2].z += 0.01f;
					wireframeColor.x = 1.f;
				}
				drawLine(MVPVertices[0],MVPVertices[1],wireframeColor);
				drawLine(MVPVertices[1],MVPVertices[2],wireframeColor);
				drawLine(MVPVertices[2],MVPVertices[0],wireframeColor);
			}

			/*===display normal===*/
			if (normalDisplay) {
				glm::vec4 smallNormals[3];
				vec3 colorNormal;
				for (int j=0; j<3;j++){
					smallNormals[j] = glm::normalize(modelNormals[j]);
					smallNormals[j] = glm::vec4(smallNormals[j].x*30,smallNormals[j].y*30,smallNormals[j].z*30,0.f);
					colorNormal.x = (glm::dot(smallNormals[j],glm::vec4(1.f,0.f,0.f,0.f)) + 1.f) / 2.f;
					colorNormal.y = (glm::dot(smallNormals[j],glm::vec4(0.f,1.f,0.f,0.f)) + 1.f) / 2.f;
					colorNormal.z = (glm::dot(smallNormals[j],glm::vec4(0.f,0.f,1.f,0.f)) + 1.f) / 2.f;
					drawLine(MVPVertices[j],(smallNormals[j]+MVPVertices[j]),colorNormal);
				}
			}

			/*if (demoMode!=0) {
				if ((demoMode==1 && i%5==0) || (demoMode!=1 && i%2==0)) {
					Sleep(1);
					glDrawPixels(screenWidth, screenHeight, GL_RGB, GL_FLOAT, (const GLvoid*)framebuffer.getPixels());
					glutSwapBuffers();
				}
			}*/
		}
	}
	
	/* Per Pixel Shading */ 
	for (int i=0; i<screenWidth; i++) {
		for (int j=0; j<screenHeight; j++) {
			
			//cel shading
			//if (shading==3) {
			//	framebuffer.celShading(i,j);
			//}

			//texturing
			if (textureDisplay==1 && solid==1 && shading!=0 && shading!=4 && (filterMode>=3)) {
				framebuffer.texturing(i,j,filterMode);
			}

		}
	}

	/* display */
	glDrawPixels(screenWidth, screenHeight, GL_RGB, GL_FLOAT, (const GLvoid*)framebuffer.getPixels());
	glutSwapBuffers();

	if (demoMode!=0) {
		if (numDrawTriangleIdx == modelPtr[curModelIdx]->numTriangles) demoModeTransition();
		if (demoMode==1) theta.y = (theta.y>PI*2) ? 0 : (theta.y + 0.02);
		else if (demoMode==2) theta.y = (theta.y>PI*2) ? 0 : (theta.y + 0.025);
		else if (demoMode==3) theta.y = (theta.y>PI*2) ? 0 : (theta.y + 0.03);
		else if (demoMode==4) theta.y = (theta.y>PI*2) ? 0 : (theta.y + 0.035);
		else if (demoMode==5) theta.y = (theta.y>PI*2) ? 0 : (theta.y + 0.04);
		else if (demoMode==6) theta.y = (theta.y>PI*2) ? 0 : (theta.y + 0.035);
	}

	/* FPS counter */
	static clock_t prev = clock();
	static clock_t curr;
	static char title[50];
	static double refreshTime = 0.5;
	static int count = 0;
	++count;
	curr = clock();
	//cout << "0: curr = " << curr << "\tprev = " << prev << endl;
	double t = (double)(curr - prev)/(double)CLOCKS_PER_SEC;
	//cout << "1: curr = " << curr << "\tprev = " << prev << "\tdelta = " << curr - prev <<  endl;
	//Sleep(800-(curr - prev));
	
	if (t > refreshTime) {
		//cout << "2: curr = " << curr << "\tprev = " << prev <<	"\tt = " << t << endl;
		//cout << "fps = " << (double)count/t << endl;
		sprintf(title, "3D Graphics Engine: %.2lf fps",	(double)count/t);
		//cout << "3: curr = " << curr << "\tprev = " << prev <<	"\tt = " << t << endl;
		glutSetWindowTitle(title);
		prev = curr;
		count = 0;
	}
}

void idleFunc() 
{
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(screenWidth, screenHeight);
	glutCreateWindow("3D Graphics Engine");

	init();

	glutDisplayFunc(displayFunc);
	glutIdleFunc(idleFunc);
	glutMotionFunc(motionFunc);
	glutMouseFunc(mouseFunc);
	glutKeyboardFunc(keyboardFunc);
	glutSpecialFunc(specialFunc);

	glutMainLoop();
	
	for(int i = 0; i < numModels; ++i) {
		if(modelPtr[i]) delete [] modelPtr[i];
	}
	if(modelPtr) delete [] modelPtr;

	return 0;
}
