#include "ui.h"

/* mouse */
bool isFirstTime = true;
bool rotating = false;
bool panning = false;
int prevMouseX;
int prevMouseY;

int lightswitch = 0;

void printHelp() 
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
  printf("Save framebuffer to %s\n", name);
  framebuffer.writePPM(name);
}

inline void selectNextModel() {
  curModelIdx = (curModelIdx == numModels - 1)? 0 : (curModelIdx + 1);
  printf("Switch to model \"%s\"\n", modelNames[curModelIdx]);
}

inline void selectPrevModel() {
  curModelIdx = (curModelIdx == 0)? (numModels - 1) : (curModelIdx - 1);
  printf("Switch to model \"%s\"\n", modelNames[curModelIdx]);
}

inline void toggleWireframe() {
  wireframe_filled = !wireframe_filled;
  cout << "Toggle wireframe to: " << wireframe_filled << endl;
}
inline void toggleProjection() {
  projection = !projection;
  cout << "Toggle projection view to: " << projection << endl;
}
inline void toggleCulling() {
  culling = !culling;
  cout << "Toggle back-face culling to: " << culling << endl;
}
inline void toggleBackground() {
  cout << "Toggle background color" << endl;
  static bool isBlack = true;
  isBlack = !isBlack;
  framebuffer.setClearColor(isBlack? vec3(0.f) : vec3(1.f));
}
inline void changeShading() {
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
}
inline void switchKaKdKsLighting(){
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
inline void rotateUp() {
  cout << "Rotate up" << endl;
  theta.x = (theta.x < 0)? (PI*2) : (theta.x - rotateSpeed);
}
inline void rotateDown() {
  cout << "Rotate down" << endl;
  theta.x = (theta.x > PI*2)? 0 : (theta.x + rotateSpeed);
}
inline void rotateLeft() {
  cout << "Rotate left" << endl;
  theta.y = (theta.y < 0)? (PI*2) : (theta.y - rotateSpeed);
}
inline void rotateRight() {
  cout << "Rotate right" << endl;
  theta.y = (theta.y > PI*2)? 0 : (theta.y + rotateSpeed);
}
inline void panUp(int pace) {
  cout << "Pan up" << endl;
  translate.y += pace;
}
inline void panDown(int pace) {
  cout << "Pan down" << endl;
  translate.y -= pace;
}
inline void panLeft(int pace) {
  cout << "Pan left" << endl;
  translate.x -= pace;
}
inline void panRight(int pace) {
  cout << "Pan right" << endl;
	translate.x += pace;
}
inline void zoomIn() {
  cout << "Zoom in" << endl;
  size.x += 10;
  size.y += 10;
}
inline void zoomOut() {
  if(size.x>(0.01-1)){
    cout << "Zoom out" << endl;
    size.x -= 10;
    size.y -= 10;
  }
  else
    cout << "It can't be smaller!" << endl;
}
inline void moveForward() {
  cout << "Move forward" << endl;
  translate.z -= 10;
}
inline void moveBackward() {
  cout << "Move backward" << endl;
  translate.z += 10;
}
inline void setLightSourcePosition(int x, int y) {
  light.source = glm::vec3(float(x), float(screenHeight - y), 500.f);
  cout << "Set light source to (" << x << ", " << screenHeight - y << ", 500)"<< endl;
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
      rotateLeft();
    else if ( deltaMouseX > 100 )
      rotateRight();
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
	case 'w':
    toggleWireframe(); break;
	case 'p':
    toggleProjection(); break;
	case 'b':
    toggleBackground(); break;
  case 'A':
    panLeft(10); break;
  case 'D':
    panRight(10); break;
  case 'W':
    panUp(10); break;
  case 'S':
    panDown(10); break;
  case '=':
    zoomIn(); break;
  case '-':
    zoomOut(); break;
	}
	glutPostRedisplay();
}

// Special keys
void specialFunc(int key, int x, int y) 
{
	switch (key) {
	case GLUT_KEY_RIGHT:
    rotateRight(); break;
	case GLUT_KEY_LEFT:
    rotateLeft(); break;
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
