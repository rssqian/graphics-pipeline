#include "lighting.h"
#include <glm/glm.hpp>

void Lighting::shading(glm::vec3 vertex, glm::vec3 normal,Material* mtlptr,LightColor& c)
{
	//cout << vertex.x << " , " << vertex.y << " , " << vertex.z << endl;

  //ambient
  float ambientIntensity = 0.2;
  float ambient = ambientIntensity;
  //diffuse
  float diffuseIntensity = 1;
  normal = glm::normalize(normal);
  glm::vec3 lightDirection = glm::normalize(source - vertex);
  float diffuse = diffuseIntensity * glm::dot(normal, lightDirection);
  diffuse = diffuse > 0 ? diffuse : 0;
  //specular
  float specularIntensity = 0.5;
  glm::vec3 viewDirection = cameraTarget - cameraPos;
  glm::vec3 reflectDirection(glm::reflect(glm::normalize(lightDirection), glm::normalize(normal))); 
  float specularDot = glm::dot(reflectDirection, viewDirection);
  specularDot = specularDot > 0 ? specularDot : 0;
  float specular = specularIntensity * glm::pow(specularDot, ns);


  float attenuation = 1;
  //glm::vec3 color = ka * ambient + attenuation*(kd * diffuse + ks * specular);
  if (displayLight==0 || displayLight==1) c.ambient = ka * ambient;
  else c.ambient = glm::vec3(0.f);
  if (displayLight==0 || displayLight==2) c.diffuse = attenuation * kd * diffuse;
  else c.diffuse = glm::vec3(0.f);
  if (displayLight==0 || displayLight==3) c.specular = attenuation * ks * specular;
  else c.specular = glm::vec3(0.f);
  //return vec3(color.x, color.y, color.z);
  //return vec3(0.5, 0.5, 0.5);
}

void Lighting::setParameter(const glm::vec3& Ka,const glm::vec3& Kd,const glm::vec3& Ks,const int& Ns)
{
	ka = Ka;
	kd = Kd;
	ks = Ks;
	ns = Ns;
}