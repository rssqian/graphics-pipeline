#ifndef _UI_H
#define _UI_H

#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <iostream>
#include "framebuffer.h"

#define PI 3.14159265

#ifndef _GLOBAL_VAR

extern int curModelIdx;
extern Framebuffer framebuffer;
extern char* modelNames[];
extern int numModels;

/* theta */
extern double rotateSpeed;
extern glm::vec3 theta;
extern glm::vec3 size;
extern glm::vec3 translate;

extern int shading;
extern bool wireframe_filled;
extern bool culling;
extern bool projection;

#endif

/* Basic functions */
void printHelp(); 
inline void saveImage();
inline void selectNextModel();
inline void selectPrevModel();
inline void toggleWireframe();
inline void toggleProjection();
inline void toggleCulling();
inline void toggleBackground();
inline void changeShading();
inline void rotateUp();
inline void rotateDown();
inline void rotateLeft();
inline void rotateRight();
inline void panUp();
inline void panDown();
inline void panLeft();
inline void panRight();
inline void zoomIn();
inline void zoomOut();
inline void moveForward();
inline void moveBackward();

/* User interfaces */
void motionFunc(int x, int y);
void mouseFunc(int button, int direction, int x, int y);
void keyboardFunc(unsigned char key, int x, int y);
void specialFunc(int key, int x, int y);

#endif
