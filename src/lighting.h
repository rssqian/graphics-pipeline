#ifndef _LIGHTING_H_
#define _LIGHTING_H_

#include "framebuffer.h"
#include <iostream>
using namespace std;

extern vec3 color;

vec3 lighting(vec3 normal);     //input 3 triangle vertex

#endif