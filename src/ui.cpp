#include "ui.h"

/* mouse */
bool isFirstTime = true;
bool rotating = false;
bool panning = false;
int prevMouseX;
int prevMouseY;

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
	printf("  c: Toggle back-face culling            \n");
	printf("  b: Toggle background color             \n");
	printf("  l: Toggle lighting mode                \n");
	printf("  w: Toggle wireframe mode               \n");
	printf("  p: Toggle projection mode              \n");
	printf("  s: Save image                          \n");
	printf("  q: Quit                                \n");
	printf("===========================================\n\n");
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
  cout << "Toggle wireframe" << endl;
  wireframe_filled = !wireframe_filled;
}
inline void toggleProjection() {
  cout << "Toggle projection view" << endl;
  projection = !projection;
}
inline void toggleCulling() {
  cout << "Toggle back-face culling" << endl;
  culling = !culling;
}
inline void toggleBackground() {
  cout << "Toggle background color" << endl;
  static bool isBlack = true;
  isBlack = !isBlack;
  framebuffer.setClearColor(isBlack? vec3(0.f) : vec3(1.f));
}
inline void changeShading() {
  cout << "Change shading mode" << endl;
  if (shading == 2) shading = 0;
  else shading++;
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
inline void panUp() {
  cout << "Pan up" << endl;
  translate.y +=10;
}
inline void panDown() {
  cout << "Pan down" << endl;
  translate.y -= 10;
}
inline void panLeft() {
  cout << "Pan left" << endl;
  translate.x -= 10;
}
inline void panRight() {
  cout << "Pan right" << endl;
	translate.x += 10;
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
    if ( deltaMouseY < -100 )
      panUp();
    if ( deltaMouseY > 100 )
      panDown();
    if ( deltaMouseX < -100 )
      panLeft();
    if ( deltaMouseX > 100 )
      panRight();
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
  case 0:
    rotating = true;
    panning = false;
    break;
  case 1:
    rotating = false;
    panning = true;
    break;
  case 4:
    zoomIn(); break;
  case 3:
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
	case 'w':
    toggleWireframe(); break;
	case 'p':
    toggleProjection(); break;
	case 'b':
    toggleBackground(); break;
  case 'A':
    panLeft(); break;
  case 'D':
    panRight(); break;
  case 'W':
    panUp(); break;
  case 'S':
    panDown(); break;
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
