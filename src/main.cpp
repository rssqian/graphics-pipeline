#define _GLOBAL_VAR
#include <QApplication>
#include <QStyleFactory>
#include <GL/freeglut.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <ctime>
#include <cmath>
#include "model/model.h"
#include "pipeline/framebuffer.h"
#include "pipeline/transform.h"
#include "pipeline/rasterize.h"
#include "pipeline/lighting.h"
#include "mainwindow.h"
using namespace std;

#define PI 3.14159265

Model** modelPtr;

/* frame size */
int screenWidth = 600;
int screenHeight = 400;
int screenWidth_half = 300;
int screenHeight_half = 200;

/* theta */
double rotateSpeed = 0.05;
glm::vec3 theta (0.0f, 0.0f, 0.0f);
glm::vec3 model_size (400.0f, 400.0f, 400.0f);
glm::vec3 translate (float(screenWidth_half), float(screenHeight_half), 0.0f);

glm::vec3 cameraPos (0.0f, 0.0f, 1.0f);
glm::vec3 cameraTarget (0.0f, 0.0f, 0.0f);
glm::vec3 upVector (0.0f, 1.0f, 0.0f);
float FoV=45.0f;

/*mode*/
bool wireframe_filled; //0-wireframe, 1-filled surface
int shading; //0-no shading, 1-flat shading, 2-smooth shading
bool projection; //0-orthogonal, 1-perspective

int curModelIdx;
bool culling;
Framebuffer framebuffer(screenWidth, screenHeight);
vec3 color(1.f);

Lighting light;
glm::vec3 ka(0.2f);
glm::vec3 kd(0.5f);
glm::vec3 ks(0.8f);

/* model names */
const char* modelNames[] = {
  //"../model/quad.obj",
  //"../model/couch.obj",
  //"model/cessna7KC.obj",
  //"model/santa7KC.obj",
  //"model/laurana2KC.obj",
  //"model/shuttle.obj",
  //"model/sphere.obj",
  //"model/Miku.obj",
  //"model/blaze.obj",
  //"model/ateneal.obj",
  //"model/venusm.obj",
  "../model/bunnyC.obj"
  //"model/duck4KN.obj",
  //"model/happy10KN.obj",
  //"model/dragon10KN.obj",
  //"model/elephant16KN.obj",
  //"model/Statue_of_Liberty.obj",
  //"model/Nissan_Pathfinder.obj"
};
int numModels = sizeof(modelNames) / sizeof(char*);

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
  wireframe_filled = 1; //0-wireframe, 1-filled surface
  shading = 1; //0-no shading, 1-flat shading, 2-smooth shading
  projection = 0; //0-orthogonal, 1-perspective
}

void idleFunc() 
{
  glutPostRedisplay();
}

int main(int argc, char** argv)
{
  init();

  glutInit(&argc, argv);

  QApplication app(argc, argv);

  /* Begin Set Dark UI Theme */

  qApp->setStyle(QStyleFactory::create("Fusion"));

  QPalette darkPalette;
  darkPalette.setColor(QPalette::Window, QColor(53,53,53));
  darkPalette.setColor(QPalette::WindowText, Qt::white);
  darkPalette.setColor(QPalette::Base, QColor(25,25,25));
  darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
  darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
  darkPalette.setColor(QPalette::ToolTipText, Qt::white);
  darkPalette.setColor(QPalette::Text, Qt::white);
  darkPalette.setColor(QPalette::Button, QColor(53,53,53));
  darkPalette.setColor(QPalette::ButtonText, Qt::white);
  darkPalette.setColor(QPalette::BrightText, Qt::red);
  darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

  darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
  darkPalette.setColor(QPalette::HighlightedText, Qt::black);

  qApp->setPalette(darkPalette);

  //qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");

  /* End Set Dark UI Theme */

  MainWindow window;
  window.show();



//  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//  glutInitWindowSize(screenWidth, screenHeight);
//  glutCreateWindow("3D Graphics Engine");

//  glutDisplayFunc(displayFunc);
//  glutIdleFunc(idleFunc);
//  glutMotionFunc(motionFunc);
//  glutMouseFunc(mouseFunc);
//  glutKeyboardFunc(keyboardFunc);
//  glutSpecialFunc(specialFunc);

//  glutMainLoop();
  
//  for(int i = 0; i < numModels; ++i) {
//  	if(modelPtr[i]) delete [] modelPtr[i];
//  }
//  if(modelPtr) delete [] modelPtr;

  return app.exec();
}
