#ifndef _LIGHTING_H_
#define _LIGHTING_H_

#include "material.h"
#include "framebuffer.h"
#include <glm/glm.hpp>
#include <iostream>
using namespace std;

extern vec3 color;

//glm::vec3 lighting(glm::vec3 normal,Material* mtl,glm::vec3& ambient_c,glm::vec3& diffuse_c,glm::vec3& specular_c);     //input 3 triangle vertex
void lighting(glm::vec3& normal,glm::vec3& ambient_c,glm::vec3& diffuse_c,glm::vec3& specular_c);

#endif