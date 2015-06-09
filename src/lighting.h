#ifndef _LIGHTING_H_
#define _LIGHTING_H_

#include "material.h"
#include "framebuffer.h"
#include <glm/glm.hpp>
#include <iostream>
using namespace std;

extern vec3 color;
extern glm::vec3 cameraPos;
extern glm::vec3 cameraTarget;

class Lighting
{
public:
  Lighting() {
    source = glm::vec3(1.f, 1.f, 500.f);
    ka = glm::vec3(0.f);
    kd = glm::vec3(1.f);
    ks = glm::vec3(0.f);
    ns = 1;
  };
  ~Lighting() {};

  vec3 shading(glm::vec3 vertex, glm::vec3 normal);

  glm::vec3 source;
  glm::vec3 ka;
  glm::vec3 kd;
  glm::vec3 ks;
  int ns;
};

//void lighting(glm::vec3& normal,glm::vec3& ambient_c,glm::vec3& diffuse_c,glm::vec3& specular_c);
#endif
