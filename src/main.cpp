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
#include "model.h"
#include "framebuffer.h"
#include "transform.h"
#include "rasterize.h"
#include "lighting.h"
#include "mainwindow.h"
using namespace std;

#define PI 3.14159265

Model** modelPtr;

/* frame size */
int screenWidth = 1075;
int screenHeight = 660;
int screenWidth_half = screenWidth/2;
int screenHeight_half = screenHeight/2;

/* theta */
double rotateSpeed = 0.02;
glm::vec3 theta (0.0f, 0.0f, 0.0f);
glm::vec3 model_size (1.5f, 1.5f, 1.5f);
glm::vec3 translate (0.0f, 0.0f, 0.0f);

glm::vec3 cameraPos (0.0f, 0.0f, 1.0f);
glm::vec3 cameraTarget (0.0f, 0.0f, 0.0f);
glm::vec3 upVector (0.0f, 1.0f, 0.0f);
float FoV=45.0f;

/*mode*/
bool wireframe; //0-wireframe off, 1-wireframe on
bool normalDisplay;
bool solid; //0-solid mode off, 1-solid mode on
int shading; //0-z shading, 1-flat shading, 2-smooth shading, 3-cell shading, 4-normal shading
bool toonShading; 
bool projection; //0-orthogonal, 1-perspective
int textureAddressing; //0-wrapping, 1-mirror, 2-clamping
bool textureDisplay;
bool showShadow;
bool showAxes;
int filterMode;	//0-off, 1-nearest, 2-linear, 3-nearest_mipmap_nearest, 4-Linear-Mipmap-Nearest, 5-Nearest-Mipmap-Linear, 6-Linear-Mipmap-Linear
int demoMode; //0-off, 1-wireframe, 2-flat shading, 3-phong shading, 4-cel shading, 5-phong shading with texture,6-normal shading

int curModelIdx;
bool culling;
Framebuffer framebuffer(screenWidth, screenHeight);
vec3 color(1.f);
glm::mat4 modelMatrix(1);
glm::mat4 model_rotation_natural(1);
bool rotationNatural;

Lighting light;
glm::vec3 ka(1.f);
glm::vec3 kd(1.f);
glm::vec3 ks(1.f);
float ambientIntensity = 0.2;
float diffuseIntensity = 1.0;
float specularIntensity = 0.2;
int ns = 1;
bool pointLight; // 0 - directional light source, 1 - point light source
bool spotlight;
float spotlightAngle = 0; // 0 to turn off

/* model names */
const char* modelNames[] = {
    "model/about.obj",

  //"model/couch.obj",
    "model/bunnyC.obj",


  //"model/ball.obj",
    "model/duck.obj",
    "model/cubeT.obj",

  /* Animals with textures */

    "model/ZEBRA.obj",
    "model/Nala.obj",
  //"model/Dog.obj",
    "model/Tiger.obj",
    "model/Giraffe.obj",
  //"model/cat.obj",
    "model/Deer.obj",
    "model/Rabbit.obj",
    "model/quad.obj"
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
    pointLight = 1;
	projection = 0; //0-orthogonal, 1-perspective
	textureAddressing = 0; //0-wrapping, 1-mirror, 2-clamping
    textureDisplay = 1;
    showShadow = 0;
    showAxes = 0;
    filterMode = 1;
	toonShading = 0;
    spotlight = 0;
    demoMode = 0;
    rotationNatural = 1;
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
  return app.exec();
}
