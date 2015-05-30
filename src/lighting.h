#ifndef _LIGHTING_H_
#define _LIGHTING_H_

#include "framebuffer.h"
#include <glm/glm.hpp>
#include <iostream>
using namespace std;

extern vec3 color;

vec3 lighting(glm::vec3);     //input 3 triangle vertex

#endif