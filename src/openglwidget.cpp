#include "openglwidget.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>
#include <ctime>
#include <cmath>
#include "model.h"
#include "framebuffer.h"
#include "transform.h"
#include "rasterize.h"
#include "lighting.h"

#define PI 3.14159265

using namespace std;

extern Model** modelPtr;

/* frame size */
extern int screenWidth;
extern int screenHeight;
extern int screenWidth_half;
extern int screenHeight_half;

/* theta */
extern double rotateSpeed;
extern glm::vec3 theta;
extern glm::vec3 model_size;
extern glm::vec3 translate;

extern glm::vec3 cameraPos;
extern glm::vec3 cameraTarget;
extern glm::vec3 upVector;
extern float FoV;

/*mode*/
extern bool wireframe;
extern bool solid;
extern bool showNormals;
extern int shading; //0-no shading, 1-flat shading, 2-smooth shading
extern bool projection; //0-orthogonal, 1-perspective
extern bool textureDisplay;

extern int curModelIdx;
extern bool culling;
extern Framebuffer framebuffer;
extern char* modelNames[];
extern int numModels;

extern Lighting light;
extern glm::vec3 ka;
extern glm::vec3 kd;
extern glm::vec3 ks;

int lightswitch = 0;
QPoint offset;

void OpenGLWidget::fpsCounter() {
    static clock_t prev = clock();
    static clock_t curr;
    static double refreshTime = 0.5;
    static int count = 0;
    ++count;
    curr = clock();
    double t = (double)(curr - prev)/(double)CLOCKS_PER_SEC;

    if (t > refreshTime) {
      stringstream ss;
      string fpsStr;
      ss << (double)count/t << "fps";
      ss >> fpsStr;
      QString qstr(fpsStr.c_str());
      emit fpsChanged(qstr);
      prev = curr;
      count = 0;
    }
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    framebuffer.clear();

	// Set MVP and viewport
	glm::mat4 modelMatrix = model_translation(translate) 
                        * model_scale(model_size)
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

	for (int i=0; i<modelPtr[curModelIdx]->numTriangles; i++) {
		Triangle* trianglePtr = modelPtr[curModelIdx]->triangles;
		float* verticePtr = modelPtr[curModelIdx]->vertices;
		float* normalPtr = modelPtr[curModelIdx]->normals;
		/*===texCoord===*/
		float* texCoordPtr = modelPtr[curModelIdx]->texCoords;

		glm::vec4 triVertices[3];
		glm::vec4 triNormals[3];
		/*===texCoord===*/
		glm::vec3 triTexCoord[3];

		for (int j=0; j<3; j++) {
			triVertices[j].x = verticePtr[3*(trianglePtr[i].vIndices[j])	];
			triVertices[j].y = verticePtr[3*(trianglePtr[i].vIndices[j])+1];
			triVertices[j].z = verticePtr[3*(trianglePtr[i].vIndices[j])+2];
			triVertices[j].w = 1;
			/*===texCoord===*/
			if (textureDisplay==1 && solid==1 && modelPtr[curModelIdx]->numTexCoords!=0) {
				triTexCoord[j].x = texCoordPtr[2*(trianglePtr[i].tcIndices[j])	];
				triTexCoord[j].y = texCoordPtr[2*(trianglePtr[i].tcIndices[j])+1];
				triTexCoord[j].z = 1;
			} else {
				triTexCoord[j].x = 0;
				triTexCoord[j].y = 0;
				triTexCoord[j].z = 1;
			}
			if ((shading==2 || shading==3 || shading==4)&& modelPtr[curModelIdx]->numNormals!=0) {
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
		Material* mtl = trianglePtr -> mtlptr;

		glm::vec4 modelVertices[3];
		glm::vec4 MVPVertices[3];
		glm::vec4 modelNormals[3];
		glm::vec4 smallNormals[3];

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

			// Normal : rotation
			modelNormals[j] = model_rotation(theta) * triNormals[j];

			smallNormals[j] = glm::normalize(modelNormals[j]);
			smallNormals[j] = glm::vec4(smallNormals[j].x*30,smallNormals[j].y*30,smallNormals[j].z*30,0.f);
 		}
		glm::vec3 v1 ( modelVertices[0]-modelVertices[1] );
		glm::vec3 v2 ( modelVertices[0]-modelVertices[2] );
		glm::vec3 faceNormals = glm::normalize(glm::cross(v1,v2));

		//Back Face Culling
		if (!backFaceCulling(faceNormals, glm::vec3(modelVertices[0])) || !culling) {
			int ix[3],iy[3];
			float iz[3];
			vec3 c;
			LightColor RGBIntensity(glm::vec3(1.f),glm::vec3(1.f),glm::vec3(1.f));
			if (shading==1) {
				glm::vec3 centerVertex = glm::vec3(modelVertices[0]+modelVertices[1]+modelVertices[2]) / 3.f;
				glm::vec3 ambient_c,diffuse_c,specular_c;
				light.shading(centerVertex, faceNormals,mtl,RGBIntensity);
				//c.x = ambient_c.x + diffuse_c.x + specular_c.x;
				//c.y = ambient_c.y + diffuse_c.y + specular_c.y;
				//c.z = ambient_c.z + diffuse_c.z + specular_c.z;
			} //else c = color;
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

			/*===texCoord===*/
			if (textureDisplay==1 && solid==1) displayNormals.push_back(triTexCoord);

      if (solid) {
        rasterTriangle(displayVertices,displayNormals,mtl,RGBIntensity);
      }
			if (wireframe) {
        vec3 wireColor = vec3(1.f, 0.5f, 0.5f);
        // Move wireframe to the front, so not covered by solid view
        MVPVertices[0].z = 0.f;
        MVPVertices[1].z = 0.f;
        MVPVertices[2].z = 0.f;
				drawLine(MVPVertices[0], MVPVertices[1], wireColor);
				drawLine(MVPVertices[1], MVPVertices[2], wireColor);
				drawLine(MVPVertices[2], MVPVertices[0], wireColor);
      }
      // Display Normal
			if (showNormals) {
        vec3 colorNormal;
        for (int j=0; j<3;j++){
          colorNormal.x = (glm::dot(smallNormals[j],glm::vec4(1.f,0.f,0.f,0.f)) + 1.f) / 2.f;
          colorNormal.y = (glm::dot(smallNormals[j],glm::vec4(0.f,1.f,0.f,0.f)) + 1.f) / 2.f;
          colorNormal.z = (glm::dot(smallNormals[j],glm::vec4(0.f,0.f,1.f,0.f)) + 1.f) / 2.f;
          drawLine(MVPVertices[j],(smallNormals[j]+MVPVertices[j]),colorNormal);
        }
      }
		}
	}
      /* display */
    glDrawPixels(screenWidth, screenHeight, GL_RGB, GL_FLOAT, (const GLvoid*)framebuffer.getPixels());
  //  glutSwapBuffers();

    fpsCounter();
}

void OpenGLWidget::resizeGL(int width, int height)
{


}



void OpenGLWidget::printHelp()
{
    printf("===========================================\n");
    printf("  HELP MENU                                \n");
    printf("===========================================\n");
    printf("  h: Show help menu                      \n");
    printf("  M/m: Select model                      \n");
    printf("  UP/DOWN: Rotate along x-axis           \n");
    printf("  LEFT/RIGHT: Rotate along y-axis        \n");
    printf("  MOUSE MIDDLE DRAG: Rotate              \n");
    printf("  W/S/A/D / MOUSE LEFT DRAG: Moving aroun\n");
    printf("  PAGEUP/PAGEDN: Moving forward/backward \n");
    printf("  +/- / MOUSE WHEEL: Zoom in/out         \n");
    printf("  MOUSE RIGHT CLICK: Set light source position\n");
    printf("  c: Toggle back-face culling            \n");
    printf("  b: Toggle background color             \n");
    printf("  l: Toggle lighting mode                \n");
    printf("  k: Toggle ambient/diffuse/specular lights\n");
    printf("  w: Toggle wireframe mode               \n");
    printf("  p: Toggle projection mode              \n");
    printf("  r: Reset model                         \n");
    printf("  s: Save image as ppm format            \n");
    printf("  q: Quit                                \n");
    printf("===========================================\n\n");
}

void OpenGLWidget::reset() {
  theta = glm::vec3(0.f, 0.f, 0.f);
  model_size = glm::vec3(400.f, 400.f, 400.f);
  translate = glm::vec3(float(screenWidth_half), float(screenHeight_half), 0.f);
  update();
}

void OpenGLWidget::saveAsImage() {
  static time_t t;
  static char name[80];
  time(&t);
  strftime(name, sizeof(name), "%Y%m%d%H%M%S.ppm", localtime(&t));
  printf("Save framebuffer to %s\n", name);
  framebuffer.writePPM(name);
}

void OpenGLWidget::selectNextModel() {
  curModelIdx = (curModelIdx == numModels - 1)? 0 : (curModelIdx + 1);
  printf("Switch to model \"%s\"\n", modelNames[curModelIdx]);
  update();
}

void OpenGLWidget::selectPrevModel() {
  curModelIdx = (curModelIdx == 0)? (numModels - 1) : (curModelIdx - 1);
  printf("Switch to model \"%s\"\n", modelNames[curModelIdx]);
  update();
}

void OpenGLWidget::toggleWireframe() {
  wireframe = !wireframe;
  if (wireframe) cout << "Add wireframe to view" << endl;
  else cout << "Remove wireframe from view" << endl;
  update();
}
void OpenGLWidget::switchToWireframe() {
  wireframe = 1;
  cout << "Add wireframe to view" << endl;
  update();
}
void OpenGLWidget::toggleSolidView() {
  solid = !solid;
  if (solid) cout << "Add solid to view" << endl;
  else cout << "Remove solid from view" << endl;
  update();
}
void OpenGLWidget::switchToSolid() {
  solid = 1;
  cout << "Add solid to view" << endl;
  update();
}

void OpenGLWidget::toggleProjection() {
  projection = !projection;
  cout << "Toggle projection view to: " << projection << endl;
  update();
}
void OpenGLWidget::switchToOrthogonal() {
    projection = 0;
    cout << "Switch view to: " << projection << endl;
    update();
}
void OpenGLWidget::switchToPerspective() {
    projection = 1;
    cout << "Switch view to: " << projection << endl;
    update();
}

void OpenGLWidget::toggleCulling() {
  culling = !culling;
  cout << "Toggle back-face culling to: " << culling << endl;
  update();
}
void OpenGLWidget::toggleTexture() {
    textureDisplay = !textureDisplay;
    cout << "Toggle texture: ";
    if (textureDisplay) cout << "on" << endl;
    else cout << "off" << endl;
}
void OpenGLWidget::toggleBackground() {
  cout << "Toggle background color" << endl;
  static bool isBlack = true;
  isBlack = !isBlack;
  framebuffer.setClearColor(isBlack? vec3(0.f) : vec3(1.f));
  update();
}
void OpenGLWidget::changeShading() {
  if (shading == 4) shading = 0;
  else shading++;
  cout << "Change to shading mode to: ";
  switch(shading) {
    case 0:
      cout << "Z shading";
      break;
    case 1:
      cout << "Flat shading";
      break;
    case 2:
      cout << "Phong shading";
      break;
    case 3:
      cout << "Cell shading";
      break;
    case 4:
      cout << "Suface normal shading";
      break;
  }
  update();
}

void OpenGLWidget::switchToNoShading() {
  shading = 0;
  cout << "Change to shading mode to: No shading" << endl;
  update();
}
void OpenGLWidget::switchToFlatShading() {
  shading = 1;
  cout << "Change to shading mode to: Flat shading" << endl;
  update();
}
void OpenGLWidget::switchToPhongShading() {
  shading = 2;
  cout << "Change to shading mode to: Phong shading" << endl;
  update();
}

void OpenGLWidget::tuneAmbientLight(int v) {
  float value = float(v)/10;
  cout << "Tune ambient light:" << value << endl;
  light.ka = glm::vec3(value);
  update();
}
void OpenGLWidget::tuneDiffuseLight(int v) {
  float value = float(v)/10;
  cout << "Tune diffuse light:" << value << endl;
  light.kd = glm::vec3(value);
  update();
}
void OpenGLWidget::tuneSpecularLight(int v) {
  float value = float(v)/10;
  cout << "Tune specular light:" << value << endl;
  light.ks = glm::vec3(value);
  update();
}

void OpenGLWidget::switchKaKdKsLighting(){
  if (lightswitch == 3)  lightswitch= 0;
  else lightswitch++;
  switch(lightswitch) {
    case 0:
      cout << "Change to lights to: Full lighting" << endl;
      light.ka = ka;
      light.kd = kd;
      light.ks = ks;
      break;
    case 1:
      cout << "Change to lights to: Ambient light only" << endl;
      light.ka = ka;
      light.kd = glm::vec3(0.f);
      light.ks = glm::vec3(0.f);
      break;
    case 2:
      cout << "Change to lights to: Diffuse light only" << endl;
      light.ka = glm::vec3(0.f);
      light.kd = kd;
      light.ks = glm::vec3(0.f);
      break;
    case 3:
      cout << "Change to lights to: Specular light only" << endl;
      light.ka = glm::vec3(0.f);
      light.kd = glm::vec3(0.f);
      light.ks = ks;
      break;
  }

}

void OpenGLWidget::rotateUp() {
  cout << "Rotate up" << endl;
  theta.x = (theta.x < 0)? (PI*2) : (theta.x - rotateSpeed);
  update();
}
void OpenGLWidget::rotateDown() {
  cout << "Rotate down" << endl;
  theta.x = (theta.x > PI*2)? 0 : (theta.x + rotateSpeed);
  update();
}
void OpenGLWidget::rotateLeft() {
  cout << "Rotate left" << endl;
  theta.y = (theta.y < 0)? (PI*2) : (theta.y - rotateSpeed);
  update();
}
void OpenGLWidget::rotateRight() {
  cout << "Rotate right" << endl;
  theta.y = (theta.y > PI*2)? 0 : (theta.y + rotateSpeed);
  update();
}
void OpenGLWidget::pan(float xPace, float yPace) {
  cout << "Pan: " << xPace << ", " << yPace << endl;
  translate.x += xPace/5;
  translate.y -= yPace/5;
  update();
}
void OpenGLWidget::panUp(float pace) {
  cout << "Pan up" << endl;
  translate.y += pace;
  update();
}
void OpenGLWidget::panDown(float pace) {
  cout << "Pan down" << endl;
  translate.y -= pace;
  update();
}
void OpenGLWidget::panLeft(float pace) {
  cout << "Pan left" << endl;
  translate.x -= pace;
  update();
}
void OpenGLWidget::panRight(float pace) {
  cout << "Pan right" << endl;
  translate.x += pace;
  update();
}
void OpenGLWidget::zoomIn() {
  cout << "Zoom in" << endl;
  model_size.x += 10;
  model_size.y += 10;
  update();
}
void OpenGLWidget::zoomOut() {
  if(model_size.x>(0.01-1)){
    cout << "Zoom out" << endl;
    model_size.x -= 10;
    model_size.y -= 10;
    update();
  }
  else
    cout << "It can't be smaller!" << endl;
}
void OpenGLWidget::moveForward() {
  cout << "Move forward" << endl;
  translate.z -= 10;
  update();
}
void OpenGLWidget::moveBackward() {
  cout << "Move backward" << endl;
  translate.z += 10;
  update();
}
void OpenGLWidget::setLightSourcePosition(int x, int y) {
  light.source = glm::vec3(float(x), float(screenHeight - y), 500.f);
  cout << "Set light source to (" << x << ", " << screenHeight - y << ", 500)"<< endl;
  update();
}


void OpenGLWidget::keyPressEvent(QKeyEvent *event) {

  if( event->modifiers() == Qt::ShiftModifier ) {
    switch (event->key()) {
        case Qt::Key_M:
            selectPrevModel(); break;
        case Qt::Key_A:
            panLeft(0.1); break;
        case Qt::Key_D:
            panRight(0.1); break;
        case Qt::Key_W:
            panUp(0.1); break;
        case Qt::Key_S:
            panDown(0.1); break;
    }
  }
  else {
    switch (event->key()) {
        case Qt::Key_H:
            printHelp(); break;
        case Qt::Key_R:
            reset(); break;
        case Qt::Key_S:
            saveAsImage(); break;
        case Qt::Key_M:
            selectNextModel(); break;
        case Qt::Key_C:
            toggleCulling(); break;
        case Qt::Key_L:
            changeShading(); break;
        case Qt::Key_K:
            switchKaKdKsLighting(); break;
        case Qt::Key_W:
            toggleWireframe(); break;
        case Qt::Key_P:
            toggleProjection(); break;
        case Qt::Key_T:
          toggleTexture(); break;
        case Qt::Key_B:
            toggleBackground(); break;

        case Qt::Key_Plus:
        case Qt::Key_Equal:
            zoomIn(); break;
        case Qt::Key_Minus:
            zoomOut(); break;
        case Qt::Key_Right:
            rotateRight(); break;
        case Qt::Key_Left:
            rotateLeft(); break;
        case Qt::Key_Up:
            rotateUp(); break;
        case Qt::Key_Down:
            rotateDown(); break;

        case Qt::Key_PageUp:
            moveForward(); break;
        case Qt::Key_PageDown:
            moveBackward(); break;
      }
  }
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event) {
    QPoint delta = event->pos() - offset;
    if (event->modifiers() == Qt::SHIFT) {
        if (event->buttons() == Qt::LeftButton) {
            if (delta.x() < -20) rotateLeft();
            if (delta.x() > 20) rotateRight();
            if (delta.y() < -20) rotateUp();
            if (delta.y() > 20) rotateDown();
        }
    }
    else {
        if (event->buttons() == Qt::LeftButton) {
            if (delta.x() > 20)
                panRight(0.1);
            else if (delta.x() < -20)
                panLeft(0.1);
            if (delta.y() > 20)
                panDown(0.1);
            else if (delta.y() < -20)
                panUp(0.1);
        }
    }
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
        offset = event->pos();
    if (event->button() == Qt::RightButton)
        setLightSourcePosition(event->x(), event->y());
}

void OpenGLWidget::wheelEvent(QWheelEvent *event) {
    if (event->delta() > 20) zoomIn();
    else if (event->delta() < -20) zoomOut();
}
