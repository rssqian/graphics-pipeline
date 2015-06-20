#ifndef _UI_H
#define _UI_H

#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <iostream>
#include <ctime>
#include "framebuffer.h"
#include "lighting.h"

#define PI 3.14159265

#ifndef _GLOBAL_VAR

extern int screenWidth;
extern int screenHeight;
extern int screenWidth_half;
extern int screenHeight_half;

extern int curModelIdx;
extern Framebuffer framebuffer;
extern const char* modelNames[];
extern int numModels;

/* theta */
extern double rotateSpeed;
extern glm::vec3 theta;
extern glm::vec3 size;
extern glm::vec3 translate;

extern int shading;
extern bool wireframe;
extern bool normalDisplay;
extern bool solid;
extern bool culling;
extern bool projection;
extern bool textureDisplay;
extern int textureAddressing;

extern Lighting light;
extern glm::vec3 ka;
extern glm::vec3 kd;
extern glm::vec3 ks;
extern bool pointLight;
extern float spotlightAngle;

#endif

/* Basic functions */
void printHelp(); 
inline void reset();
inline void saveImage();
inline void selectNextModel();
inline void selectPrevModel();
inline void toggleWireframe();
inline void toggleNormalDisplay();
inline void toggleSolid();
inline void toggleProjection();
inline void toggleCulling();
inline void toggleBackground();
inline void changeShading();
inline void switchKaKdKsLighting();
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
inline void setLightSourcePosition();
inline void toggleTexture();
inline void switchTextureModes();

/* User interfaces */
void motionFunc(int x, int y);
void mouseFunc(int button, int direction, int x, int y);
void keyboardFunc(unsigned char key, int x, int y);
void specialFunc(int key, int x, int y);

#endif
