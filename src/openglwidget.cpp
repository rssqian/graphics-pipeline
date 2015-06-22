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
extern bool normalDisplay;
extern int shading; //0-no shading, 1-flat shading, 2-smooth shading
extern bool projection; //0-orthogonal, 1-perspective
extern bool textureDisplay;
extern int textureAddressing; //0-wrapping, 1-mirror, 2-clamping
extern bool toonShading;
extern bool showShadow;
extern bool showAxes;
extern int filterMode;

extern int curModelIdx;
extern bool culling;
extern Framebuffer framebuffer;
extern char* modelNames[];
extern int numModels;

extern glm::mat4 modelMatrix;
extern glm::mat4 model_rotation_natural;

extern Lighting light;
extern glm::vec3 ka;
extern glm::vec3 kd;
extern glm::vec3 ks;

extern bool pointLight;
extern float spotlightAngle;

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
    //framebuffer.setClearColor(vec3(0.1, 0.3, 0.5));

    // Set MVP and viewport
    modelMatrix = model_translation(translate)
                        * model_scale(model_size)
                        * model_rotation(theta) * model_rotation_natural;
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
        float* texCoordPtr = modelPtr[curModelIdx]->texCoords;

        glm::vec4 triVertices[3];
        glm::vec4 triNormals[3];
        glm::vec3 triTexCoord[3];

        for (int j=0; j<3; j++) {
            triVertices[j].x = verticePtr[3*(trianglePtr[i].vIndices[j])	];
            triVertices[j].y = verticePtr[3*(trianglePtr[i].vIndices[j])+1];
            triVertices[j].z = verticePtr[3*(trianglePtr[i].vIndices[j])+2]; triVertices[j].w = 1;
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
        glm::vec4 MmodelVertices[3];
        glm::vec4 MVPVertices[3];
        glm::vec4 modelNormals[3];


        for(int j=0; j<3; ++j) {
            // model space (scaling->rotation->translation)
            modelVertices[j] = modelMatrix * triVertices[j];
      MmodelVertices[j] = modelVertices[j];
      //cout << "MODEL: " << modelVertices[j].x << ", " << modelVertices[j].y << ", " << modelVertices[j].z << endl;
            // view space
            modelVertices[j] = viewMatrix * modelVertices[j];
      //cout << "VIEW:  " << modelVertices[j].x << ", " << modelVertices[j].y << ", " << modelVertices[j].z << endl;
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
        if (cull==true && toonShading==true) {
            MVPVertices[0].z = -1e20;
            MVPVertices[1].z = -1e20;
            MVPVertices[2].z = -1e20;
            drawLine(MVPVertices[0],MVPVertices[1],vec3(1.f,0.f,0.f));
            drawLine(MVPVertices[1],MVPVertices[2],vec3(1.f,0.f,0.f));
            drawLine(MVPVertices[2],MVPVertices[0],vec3(1.f,0.f,0.f));
        }

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
        if (pointLight)
                  light.shading(centerVertex, faceNormals, KaKdKsIntensity, spotlightAngle);
        else
                  light.directionalShading(faceNormals, KaKdKsIntensity);
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

      if (showShadow) {
        glm::vec4 projectVertices[3];
        glm::vec4 MVPProjectVertices[3];
        if ( light.projectionShadow(modelVertices[0], projectVertices[0]) &&
             light.projectionShadow(modelVertices[1], projectVertices[1]) &&
             light.projectionShadow(modelVertices[2], projectVertices[2]) ) {
          MVPProjectVertices[0] = projectVertices[0] * viewportMatrix;
          MVPProjectVertices[1] = projectVertices[1] * viewportMatrix;
          MVPProjectVertices[2] = projectVertices[2] * viewportMatrix;
          drawShadow(glm::vec3(MVPProjectVertices[0]), glm::vec3(MVPProjectVertices[1]), glm::vec3(MVPProjectVertices[2]), vec3(0.15f, 0.12f, 0.1f));
        }
      }

            /*===wireframe mode===*/
            if (wireframe==1) {
        vec3 colorWireframe = vec3(0.8f, 0.6f, 0.2f);
                MVPVertices[0].z = 0.f;
                MVPVertices[1].z = 0.f;
                MVPVertices[2].z = 0.f;
                drawLine(MVPVertices[0], MVPVertices[1], colorWireframe);
                drawLine(MVPVertices[1], MVPVertices[2], colorWireframe);
                drawLine(MVPVertices[2], MVPVertices[0], colorWireframe);
            }

            /*===display normal===*/
            if (normalDisplay) {
                glm::vec4 smallNormals[3];
                vec3 colorNormal;
                for (int j=0; j<3;j++){
                    smallNormals[j] = glm::normalize(modelNormals[j]);
                    smallNormals[j] = glm::vec4(smallNormals[j].x*130,smallNormals[j].y*130,smallNormals[j].z*130,0.f);
                    colorNormal.x = (glm::dot(smallNormals[j],glm::vec4(1.f,0.f,0.f,0.f)) + 1.f) / 2.f;
                    colorNormal.y = (glm::dot(smallNormals[j],glm::vec4(0.f,1.f,0.f,0.f)) + 1.f) / 2.f;
                    colorNormal.z = (glm::dot(smallNormals[j],glm::vec4(0.f,0.f,1.f,0.f)) + 1.f) / 2.f;
                    drawLine(MVPVertices[j],(smallNormals[j]+MVPVertices[j]),colorNormal);
                }
            }


        } // end if culling
    } // end for each triangle

  /*===show axes===*/
  if (showAxes) {
    glm::vec4 axis[4];
    axis[0] = glm::vec4(0.f, 0.f, 0.f, 1.f);
    axis[1] = glm::vec4(1.f, 0.f, 0.f, 1.f);
    axis[2] = glm::vec4(0.f, 1.f, 0.f, 1.f);
    axis[3] = glm::vec4(0.f, 0.f, 1.f, 1.f);

    for(int j=0; j<4; ++j) {
      // model space (scaling->rotation->translation)
      axis[j] = modelMatrix * axis[j];
      // view space
      axis[j] = viewMatrix * axis[j];
      // projection space
      axis[j] = projectionMatrix * axis[j];
      // Display space
      axis[j] = axis[j] * viewportMatrix;
    }
    vec3 colorAxisX = vec3(1.f, 0.f, 0.f);
    vec3 colorAxisY = vec3(0.f, 1.f, 0.f);
    vec3 colorAxisZ = vec3(0.f, 0.f, 1.f);
    drawLine(axis[0], axis[1], colorAxisX);
    drawLine(axis[0], axis[2], colorAxisY);
    drawLine(axis[0], axis[3], colorAxisZ);
  }

    /* Per Pixel Shading */

    for (int i=0; i<screenWidth; i++) {
        for (int j=0; j<screenHeight; j++) {
            //cel shading
            if (shading==3) {
                framebuffer.celShading(i,j);
            }

            //texturing
            if (textureDisplay==1 && solid==1 && shading!=0 && shading!=4) {
                framebuffer.texturing(i,j,filterMode);
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
	cout << "===========================================" << endl;
	cout << "  HELP MENU                                " << endl;
	cout << "===========================================" << endl;
	cout << "  h: Show help menu                       " << endl;
	cout << "  M/m: Select model                       " << endl;
	cout << "  r: Reset model                          " << endl;
	cout << "  s: Save image as ppm format             " << endl;
	cout << "  q: Quit                                 " << endl;
  cout << endl;
	cout << "  <Moving around with keyboard>           " << endl;
	cout << "  --------------------------------------- " << endl;
	cout << "  Up/Down: Rotate along x-axis            " << endl;
	cout << "  Left/Right: Rotate along y-axis         " << endl;
	cout << "  PageUp/PageDown: Moving forward/backward  " << endl;
	cout << "  +/- : Zoom in/out          " << endl;
  cout << endl;
	cout << "  <Moving around with mouse>              " << endl;
	cout << "  --------------------------------------- " << endl;
	cout << "  Mouse Middle Drag: Rotate               " << endl;
	cout << "  W/S/A/D / MOUSE LEFT DRAG: Moving aroun " << endl;
	cout << "  Mouse Wheel: Zoom in/out                " << endl;
	cout << "  Mouse Right Click: Set light source position " << endl;
  cout << endl;
	cout << "  <View options>                          " << endl;
	cout << "  --------------------------------------- " << endl;
	cout << "  w: Toggle wireframe mode                " << endl;
	cout << "  n: Toggle normal-display mode           " << endl;
	cout << "  f: Toggle Solid mode                    " << endl;
	cout << "  p: Toggle projection mode               " << endl;
	cout << "  c: Toggle back-face culling             " << endl;
	cout << "  a: Toggle axes (X-axis: Red, Y-axis: Green, Z-axis: Blue) " << endl;
	cout << "  b: Toggle background color              " << endl;
	cout << "  l: Toggle lighting mode                 " << endl;
	cout << "  k: Switch ambient/diffuse/specular lights " << endl;
	cout << "  d: Toggle point/directional light source  " << endl;
	cout << "  o: Toggle shadow                         " << endl;
	cout << "  z/x: Increase/Decrease spotlight angle (point light) " << endl;
	cout << "  t: Toggle texture/texture filtering mode  " << endl;
	cout << "  T: Switch texture addressing mode         " << endl;
	cout << "  z: Toon shading                           " << endl;
	cout << "=========================================== " << endl;
}

void OpenGLWidget::reset() {
  theta = glm::vec3(0.f, 0.f, 0.f);
  model_size = glm::vec3(1.f, 1.f, 1.f);
  translate = glm::vec3(0.f, 0.f, 0.f);
  model_rotation_natural = glm::mat4(1);
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
void OpenGLWidget::switchToWireframe(bool on) {
  wireframe = on;
  if (wireframe) cout << "Add wireframe to view" << endl;
  else cout << "Remove wireframe from view" << endl;
  update();
}
void OpenGLWidget::toggleNormalDisplay() {
    normalDisplay = !normalDisplay;
    cout << "Toggle normal display: ";
    if (normalDisplay) cout << "on" << endl;
    else cout << "off" << endl;
    update();
}
void OpenGLWidget::toggleSolidView() {
  solid = !solid;
  if (solid) cout << "Add solid to view" << endl;
  else cout << "Remove solid from view" << endl;
  update();
}
void OpenGLWidget::switchToSolid(bool on) {
  solid = on;
  if (solid) cout << "Add solid to view" << endl;
  else cout << "Remove solid from view" << endl;
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
void OpenGLWidget::toggleShadow() {
  showShadow = !showShadow;
  if (showShadow) cout << "Show shadow. Please turn off back-face culling." << endl;
  else cout << "Hide shadow. You may turn on back-face culling." << endl;
  update();
}
void OpenGLWidget::toggleShowAxes() {
  showAxes = !showAxes;
  if (showAxes) cout << "Show axes" << endl;
  else cout << "Hide axes" << endl;
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
  if (shading == 5) shading = 0;
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
    case 5:
      cout << "Toon shading";
      break;
  }
  update();
}

void OpenGLWidget::toggleToonShading() {
  toonShading = !toonShading;
  cout << "Toggle toon shading: ";
  if (toonShading) cout << "ON";
  else cout << "OFF";
  cout << endl;
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
  light.displayLight = lightswitch;
  switch(lightswitch) {
    case 0:
      cout << "Change to lights to: Full lighting" << endl;
      break;
    case 1:
      cout << "Change to lights to: Ambient light only" << endl;
      break;
    case 2:
      cout << "Change to lights to: Diffuse light only" << endl;
      break;
    case 3:
      cout << "Change to lights to: Specular light only" << endl;
      break;
  }
  update();
}
void OpenGLWidget::togglePointLight() {
  pointLight = !pointLight;
  if (pointLight) cout << "Point light source" << endl;
  else cout << "Directional light source" << endl;
  update();
}
void OpenGLWidget::changeSpotlightAngle(float angle) {
  spotlightAngle += angle;
  if (spotlightAngle > 1) spotlightAngle = 1;
  if (spotlightAngle < 0) spotlightAngle = 0;
  cout << "Spotlight angle: " << spotlightAngle << endl;
  update();
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
  model_size.x += 0.1;
  model_size.y += 0.1;
  update();
}
void OpenGLWidget::zoomOut() {
  if(model_size.x>(0.01-1)){
    cout << "Zoom out" << endl;
    model_size.x -= 0.1;
    model_size.y -= 0.1;
    update();
  }
  else
    cout << "It can't be smaller!" << endl;
}
void OpenGLWidget::moveForward() {
  cout << "Move forward" << endl;
  translate.z -= 0.1;
  update();
}
void OpenGLWidget::moveBackward() {
  cout << "Move backward" << endl;
  translate.z += 0.1;
  update();
}
void OpenGLWidget::setLightSourcePosition(int x, int y) {
  light.source = glm::vec3(float(x), float(screenHeight - y), 500.f);
  cout << "Set light source to (" << x << ", " << screenHeight - y << ", 500)"<< endl;
  update();
}

void OpenGLWidget::toggleTexture() {
  
  if (filterMode==6) 
  {
	  filterMode=0; 
	  textureDisplay = !textureDisplay;
  }
  else if(filterMode==0) 
  {
	  filterMode++;
	  textureDisplay = !textureDisplay;
  }
  else filterMode++;
  cout << "Toggle texture: ";
  if (filterMode==0) cout << "Off" << endl;
  else if(filterMode==1) cout << "Nearest Mode" << endl;
  else if(filterMode==2) cout << "Linear Mode" << endl;
  else if(filterMode==3) cout << "Nearest-Mipmap-Nearest Mode" << endl;
  else if(filterMode==4) cout << "Linear-Mipmap-Nearest Mode" << endl;
  else if(filterMode==5) cout << "Nearest-Mipmap-Linear Mode" << endl;
  else if(filterMode==6) cout << "Linear-Mipmap-Linear Mode" << endl;
  //if (textureDisplay) cout << "on" << endl;
  //else cout << "off" << endl;
  update();
}

void OpenGLWidget::switchTextureModes() {
  if (textureAddressing == 2) textureAddressing = 0;
  else textureAddressing++;
  cout << "Switch texture addressing to: " << textureAddressing << endl;
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
        case Qt::Key_T:
            switchTextureModes(); break;
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
        case Qt::Key_D:
          togglePointLight(); break;
        case Qt::Key_X:
          changeSpotlightAngle(-0.001); break;
        case Qt::Key_Y:
          changeSpotlightAngle(0.001); break;
        case Qt::Key_W:
            toggleWireframe(); break;
        case Qt::Key_N:
            toggleNormalDisplay(); break;
        case Qt::Key_F:
            toggleSolidView(); break;
        case Qt::Key_P:
            toggleProjection(); break;
        case Qt::Key_O:
          toggleShadow(); break;
        case Qt::Key_A:
          toggleShowAxes(); break;
        case Qt::Key_T:
          toggleTexture(); break;
        case Qt::Key_B:
            toggleBackground(); break;
        case Qt::Key_Z:
          toggleToonShading(); break;

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
