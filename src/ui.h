#ifndef _UI_H
#define _UI_H

#include <GL/freeglut.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <ctime>
#include <cmath>
#include "framebuffer.h"
#include "lighting.h"
#include "transform.h"

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
extern glm::vec3 cameraPos;
extern glm::vec3 cameraTarget;
extern glm::vec3 upVector;

extern glm::mat4 modelMatrix;
extern glm::mat4 model_rotation_natural;

extern int shading;
extern bool wireframe;
extern bool normalDisplay;
extern bool solid;
extern bool culling;
extern bool projection;
extern bool textureDisplay;
extern int textureAddressing;
extern bool showShadow;
extern bool showAxes;

extern Lighting light;
extern glm::vec3 ka;
extern glm::vec3 kd;
extern glm::vec3 ks;
extern bool pointLight;
extern float spotlightAngle;

#endif

/* Basic functions */
void printHelp(); 

/* User interfaces */
void motionFunc(int x, int y);
void mouseFunc(int button, int direction, int x, int y);
void keyboardFunc(unsigned char key, int x, int y);
void specialFunc(int key, int x, int y);

#endif
