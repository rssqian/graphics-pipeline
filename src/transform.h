#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <glm/glm.hpp>
#include "framebuffer.h"

//void model2view_rotation(vec3& prev);

//glm::mat4 modelMatrix(glm::vec3 translation,glm::vec3 rotation,double scale);
glm::mat4 model_translation(glm::vec3);
glm::mat4 model_scale(glm::vec3);
glm::mat4 model_rotation(glm::vec3) ;

glm::mat4 viewMatrix(glm::vec3 cameraPos,glm::vec3 cameraTarget,glm::vec3 upVector);
glm::mat4 projectionMatrix(float FoV);

bool backFaceCulling(glm::vec3);

void toScreenSpace(vec3& v,int& ix,int& iy,float& iz);

#endif