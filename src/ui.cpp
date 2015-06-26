#include "ui.h"
#include <iostream>
//#include <time.h>
using namespace std;

/* mouse */
bool isFirstTime = true;
bool rotating = false;
bool panning = false;
int prevMouseX;
int prevMouseY;

int lightswitch = 0;

void printHelp() 
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
	cout << "  b: Toggle background color              " << endl;
	cout << "  l: Toggle lighting mode                 " << endl;
	cout << "  k: Switch ambient/diffuse/specular lights " << endl;
	cout << "  Z: Toggle poit/directional light source  " << endl;
	cout << "  z/x: Increase/Decrease spotlight angle (point light) " << endl;
	cout << "  t: Toggle texture/texture filtering mode  " << endl;
	cout << "  T: Switch texture addressing mode         " << endl;
	cout << "  d: Toggle demo mode                       " << endl;
	cout << "=========================================== " << endl;
}

inline void reset() {
  theta = glm::vec3(0.f, 0.f, 0.f);
  size = glm::vec3(400.f, 400.f, 400.f);
  translate = glm::vec3(float(screenWidth_half), float(screenHeight_half), 0.f);
}

inline void saveAsImage() {
  static time_t t;
  static char name[80];
  time(&t);
  strftime(name, sizeof(name), "%Y%m%d%H%M%S.ppm", localtime(&t));
  cout << "Save framebuffer to " << name << endl;
  framebuffer.writePPM(name);
}

inline void selectNextModel() {
  curModelIdx = (curModelIdx == numModels - 1)? 0 : (curModelIdx + 1);
  cout << "Switch to model " << modelNames[curModelIdx] << endl;
}

inline void selectPrevModel() {
  curModelIdx = (curModelIdx == 0)? (numModels - 1) : (curModelIdx - 1);
  cout << "Switch to model " << modelNames[curModelIdx] << endl;
}

inline void toggleWireframe() {
  wireframe = !wireframe;
  cout << "Toggle object to: ";
  if (wireframe) cout << "Wireframe on" << endl;
  else cout << "Wireframe off" << endl;
}
inline void toggleNormalDisplay() {
	normalDisplay = !normalDisplay;
	cout << "Toggle normal display: ";
	if (normalDisplay) cout << "on" << endl;
	else cout << "off" << endl;
}
inline void toggleSolid() {
  solid = !solid;
  cout << "Toggle object to: ";
  if (wireframe) cout << "Solid on" << endl;
  else cout << "Solid off" << endl;
}
inline void toggleProjection() {
  projection = !projection;
  cout << "Toggle view to: ";
  if (projection) cout << "Projection View" << endl;
  else cout << "Orthogonal View" << endl;
}
inline void toggleCulling() {
  culling = !culling;
  cout << "Toggle back-face culling to: ";
  if (culling) cout << "ON";
  else cout << "OFF";
  cout << endl;
}
inline void toggleBackground() {
  cout << "Toggle background color" << endl;
  static bool isBlack = true;
  isBlack = !isBlack;
  framebuffer.setClearColor(isBlack? vec3(0.f) : vec3(1.f));
}
inline void changeShading() {
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
  cout << endl;
}
inline void switchKaKdKsLighting(){
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
}

inline void togglePointLight() {
  pointLight = !pointLight;
  if (pointLight) cout << "Point light source" << endl;
  else cout << "Directional light source" << endl;
}
inline void changeSpotlightAngle(float angle) {
  spotlightAngle += angle;
  if (spotlightAngle > 1) spotlightAngle = 1;
  if (spotlightAngle < 0) spotlightAngle = 0;
  cout << "Spotlight angle: " << spotlightAngle << endl;
}

inline void rotateUp() {
  //cout << "Rotate up" << endl;
  theta.x = (theta.x < 0)? (PI*2) : (theta.x - rotateSpeed);
}
inline void rotateDown() {
  //cout << "Rotate down" << endl;
  theta.x = (theta.x > PI*2)? 0 : (theta.x + rotateSpeed);
}
inline void rotateLeftY() {
  //cout << "Rotate left" << endl;
  theta.y = (theta.y < 0)? (PI*2) : (theta.y - rotateSpeed);
}
inline void rotateRightY() {
  //cout << "Rotate right" << endl;
  theta.y = (theta.y > PI*2)? 0 : (theta.y + rotateSpeed);
}
inline void rotateLeftX() {
  //cout << "Rotate left" << endl;
  theta.z = (theta.z < 0)? (PI*2) : (theta.z - rotateSpeed);
}
inline void rotateRightX() {
  //cout << "Rotate right" << endl;
  theta.z = (theta.z > PI*2)? 0 : (theta.z + rotateSpeed);
}
inline void panUp(float pace) {
  //cout << "Pan up" << endl;
  translate.y += pace;
}
inline void panDown(float pace) {
  //cout << "Pan down" << endl;
  translate.y -= pace;
}
inline void panLeft(float pace) {
  //cout << "Pan left" << endl;
  translate.x -= pace;
}
inline void panRight(float pace) {
  //cout << "Pan right" << endl;
	translate.x += pace;
}
inline void zoomIn() {
  //cout << "Zoom in" << endl;
  size.x += 0.1;
  size.y += 0.1;
}
inline void zoomOut() {
  if(size.x>(0.01-1)){
    //cout << "Zoom out" << endl;
    size.x -= 0.1;
    size.y -= 0.1;
  }
  else
    cout << "It can't be smaller!" << endl;
}
inline void moveForward() {
  //cout << "Move forward" << endl;
  translate.z -= 0.1;
}
inline void moveBackward() {
  //cout << "Move backward" << endl;
  translate.z += 0.1;
}
inline void setLightSourcePosition(int x, int y) {
  float lightX = float(x - screenWidth_half)/screenWidth_half*5;
  float lightY = float(screenHeight_half - y)/screenHeight_half*5;
  light.source = glm::vec3(lightX, lightY, 1.f);
  cout << "Set light source to (" << lightX << ", " << lightY << ", 5)"<< endl;
} 

inline void toggleTexture() {
  
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
}

inline void switchTextureModes() {
  if (textureAddressing == 2) textureAddressing = 0;
  else textureAddressing++;
  cout << "Switch texture addressing to: " << textureAddressing << endl;
}

inline void toggleDemo() {
  if (demoMode == 0) { 
    demoMode = 1;
    cout << "Switching to DEMO mode" << endl;
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
	theta = glm::vec3(0.f);
  } else {
	demoMode = 0;
	cout << "Switching to MANUAL mode" << endl;
	culling = true;
	wireframe = 0;
	normalDisplay = 0;
	solid = 1;
	shading = 1; 
	textureAddressing = 0; 
	textureDisplay = 0;
	filterMode = 0;
	
  }
}

void motionFunc(int x, int y) {
  if ( rotating ) {
    int deltaMouseX = x - prevMouseX;
    int deltaMouseY = y - prevMouseY;
    if ( deltaMouseY > 100 )
      rotateUp();
    else if ( deltaMouseY < -100 )
      rotateDown();
    else if ( deltaMouseX < -100 )
      rotateLeftY();
    else if ( deltaMouseX > 100 )
      rotateRightY();
  }
  if ( panning ) {
    int deltaMouseX = x - prevMouseX;
    int deltaMouseY = y - prevMouseY;
    int paceX = deltaMouseX > 0 ? deltaMouseX : -deltaMouseX;
    int paceY = deltaMouseY > 0 ? deltaMouseY : -deltaMouseY;
    paceX = paceX / 40;
    paceY = paceY / 40;
    if ( deltaMouseY < -20 )
      panUp(paceY);
    if ( deltaMouseY > 20 )
      panDown(paceY);
    if ( deltaMouseX < -20 )
      panLeft(paceX);
    if ( deltaMouseX > 20 )
      panRight(paceX);
  }
}

void mouseFunc(int button, int direction, int x, int y)
{
  if ( isFirstTime ) {
    isFirstTime = false;
    prevMouseX = x;
    prevMouseY = y;
    return;
  }
  prevMouseX = x;
  prevMouseY = y;

  switch (button) {
  case 0: // Left button
    rotating = true;
    panning = false;
    break;
  case 1: // Middle button
    rotating = false;
    panning = true;
    break;
  case 2: // Right button
    setLightSourcePosition(x, y);
    break;
  case 4: // Scroll down
    zoomIn(); break;
  case 3: // Scroll up
    zoomOut(); break;
  default:
    rotating = false;
    panning = false;
  }
}

void keyboardFunc(unsigned char key, int x, int y) 
{
	switch (key) {
	case 'q':
		exit(0); break;
	case 'h':
		printHelp(); break;
	case 'r':
		reset(); break;
	case 's':
    saveAsImage(); break;
	case 'm':
    selectNextModel(); break;
	case 'M':
    selectPrevModel(); break;
	case 'c':
    toggleCulling(); break;
	case 'l':
    changeShading(); break;
	case 'k':
    switchKaKdKsLighting(); break;
	case 'Z':
    togglePointLight(); break;
	case 'z':
    changeSpotlightAngle(-0.001); break;
	case 'x':
    changeSpotlightAngle(0.001); break;
	case 'w':
    toggleWireframe(); break;
	case 'n':
	toggleNormalDisplay(); break;
	case 'f':
	toggleSolid(); break;
	case 'p':
    toggleProjection(); break;
	case 'b':
    toggleBackground(); break;
  case 't':
    toggleTexture(); break;
  case 'T':
    switchTextureModes(); break;
  case 'A':
    panLeft(0.1); break;
  case 'D':
    panRight(0.1); break;
  case 'W':
    panUp(0.1); break;
  case 'S':
    panDown(0.1); break;
  case '=':
    zoomIn(); break;
  case '-':
    zoomOut(); break;
  case 'd':
    toggleDemo(); break;
  case '/':
	rotateRightX(); break;
  case '.':
	rotateLeftX(); break;
	}
	glutPostRedisplay();
}

// Special keys
void specialFunc(int key, int x, int y) 
{
	switch (key) {
	case GLUT_KEY_RIGHT:
    rotateRightY(); break;
	case GLUT_KEY_LEFT:
    rotateLeftY(); break;
	case GLUT_KEY_UP:
    rotateUp(); break;
	case GLUT_KEY_DOWN:
    rotateDown(); break;

	case GLUT_KEY_PAGE_UP:
    moveForward(); break;
	case GLUT_KEY_PAGE_DOWN:
    moveBackward(); break;
  }
}
