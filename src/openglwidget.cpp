#include "openglwidget.h"
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
extern bool wireframe_filled; //0-wireframe, 1-filled surface
extern int shading; //0-no shading, 1-flat shading, 2-smooth shading
extern bool projection; //0-orthogonal, 1-perspective

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

    // Set MVP
    glm::mat4 modelMatrix = model_translation(translate) * model_scale(model_size) * model_rotation(theta);
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

      //ValueTriangle triangle;
  /*		vec3 triVertices[3];
      vec3 triNormals[3];*/

      glm::vec4 triVertices[3];
      glm::vec4 triNormals[3];

      for (int j=0; j<3; j++) {
          triVertices[j].x = verticePtr[3*(trianglePtr[i].vIndices[j])  ];
          triVertices[j].y = verticePtr[3*(trianglePtr[i].vIndices[j])+1];
          triVertices[j].z = verticePtr[3*(trianglePtr[i].vIndices[j])+2];
          triVertices[j].w = 1;
          if (shading==2) {
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
          MVPVertices[j] = projectionMatrix * viewVertices[j];
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
          if (shading==1) {
  /*				vec3 v1(triVertices[0].x-triVertices[1].x,triVertices[0].y-triVertices[1].y,triVertices[0].z-triVertices[1].z);
              vec3 v2(triVertices[0].x-triVertices[2].x,triVertices[0].y-triVertices[2].y,triVertices[0].z-triVertices[2].z);
              vec3 normal = crossProduct(v1,v2);*/
          glm::vec3 centerVertex = glm::vec3(viewVertices[0]+viewVertices[1]+viewVertices[2]) / 3.f;
              c = light.shading(centerVertex, faceNormals);
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

          glm::vec3* temp_vertex = new glm::vec3[3];
          for (int j=0; j<3;j++)
              temp_vertex[j] = glm::vec3(viewVertices[j].x,viewVertices[j].y,viewVertices[j].z);
          displayNormals.push_back(temp_vertex);

          //drawTriangle(ix,iy,iz,c);
          //====non glm type==== if (wireframe_filled==1) drawTriangle(displayVertices,triNormals,c);
          /*====glm type====*/ if (wireframe_filled==1) rasterTriangle(displayVertices,displayNormals,c);
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
  //  glutSwapBuffers();

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
  wireframe_filled = !wireframe_filled;
  cout << "Toggle wireframe to: " << wireframe_filled << endl;
  update();
}
void OpenGLWidget::switchToWireframe() {
  wireframe_filled = 0;
  cout << "Switch wireframe to: " << wireframe_filled << endl;
  update();
}
void OpenGLWidget::switchToSolid() {
  wireframe_filled = 1;
  cout << "Switch wireframe to: " << wireframe_filled << endl;
  update();
}

void OpenGLWidget::toggleProjection() {
  projection = !projection;
  cout << "Toggle projection view to: " << projection << endl;
  update();
}
void OpenGLWidget::toggleCulling() {
  culling = !culling;
  cout << "Toggle back-face culling to: " << culling << endl;
  update();
}
void OpenGLWidget::toggleBackground() {
  cout << "Toggle background color" << endl;
  static bool isBlack = true;
  isBlack = !isBlack;
  framebuffer.setClearColor(isBlack? vec3(0.f) : vec3(1.f));
  update();
}
void OpenGLWidget::changeShading() {
  if (shading == 2) shading = 0;
  else shading++;
  switch(shading) {
    case 0:
      cout << "Change to shading mode to: No shading" << endl;
      break;
    case 1:
      cout << "Change to shading mode to: Flat shading" << endl;
      break;
    case 2:
      cout << "Change to shading mode to: Phong shading" << endl;
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
void OpenGLWidget::panUp(int pace) {
  cout << "Pan up" << endl;
  translate.y += pace;
  update();
}
void OpenGLWidget::panDown(int pace) {
  cout << "Pan down" << endl;
  translate.y -= pace;
  update();
}
void OpenGLWidget::panLeft(int pace) {
  cout << "Pan left" << endl;
  translate.x -= pace;
  update();
}
void OpenGLWidget::panRight(int pace) {
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
            panLeft(10); break;
        case Qt::Key_D:
            panRight(10); break;
        case Qt::Key_W:
            panUp(10); break;
        case Qt::Key_S:
            panDown(10); break;
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

