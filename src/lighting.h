#ifndef _LIGHTING_H_
#define _LIGHTING_H_

#include "material.h"
#include "vec3.h"
#include <glm/glm.hpp>
#include <iostream>
using namespace std;

extern glm::vec3 cameraPos;
extern glm::vec3 cameraTarget;
extern bool textureDisplay;

class LightColor
{
public:
	LightColor() {}
	LightColor(glm::vec3 a,glm::vec3 d,glm::vec3 s):ambient(a),diffuse(d),specular(s) {}
	LightColor(vec3 a,vec3 d,vec3 s) {
		ambient = glm::vec3(a.x,a.y,a.z);
		diffuse = glm::vec3(d.x,d.y,d.z);
		specular = glm::vec3(s.x,s.y,s.z);
	}
	~LightColor() {}

	vec3 output1C() {
		vec3 c;
		c.x = ambient.x + diffuse.x + specular.x;
		c.y = ambient.y + diffuse.y + specular.y;
		c.z = ambient.z + diffuse.z + specular.z;
	}

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

class Lighting
{
public:
  Lighting();
  ~Lighting();

  void setParameter(const glm::vec3& Ka,const glm::vec3& Kd,const glm::vec3& Ks,const int& Ns);
  void shading(const glm::vec3& vertex, const glm::vec3& normal, LightColor& c, float spotlightAngle = 0);
  void directionalShading(const glm::vec3& normal, LightColor& c);

  glm::vec3 source;
  glm::vec3 ka;
  glm::vec3 kd;
  glm::vec3 ks;
  int ns;

  float attenuation;

  int displayLight; //0-KaKdKs, 1-Ka, 2-Kd, 3-Ks
};

//void lighting(glm::vec3& normal,glm::vec3& ambient_c,glm::vec3& diffuse_c,glm::vec3& specular_c);
#endif
