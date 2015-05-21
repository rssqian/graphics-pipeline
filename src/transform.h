#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "framebuffer.h"

vec3 transform(vec3& prev);
void toScreenSpace(vec3& v,int& ix,int& iy,float& iz);
bool backFaceCulling(vec3* triangleV);

#endif