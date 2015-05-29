#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <glm/mat4x4.hpp>

#include "framebuffer.h"

void model2view_rotation(vec3& prev);
glm::mat4 modelMatrix(glm::vec3 translation,glm::vec3 rotation,double scale);
glm::mat4 rotationMatrix(glm::vec3 rotation);
glm::mat4 viewMatrix(glm::vec3 cameraPos,glm::vec3 cameraTarget,glm::vec3 upVector);
glm::mat4 projectionMatrix(float FoV);
void toScreenSpace(vec3& v,int& ix,int& iy,float& iz);
bool backFaceCulling(vec3* triangleV);

#endif