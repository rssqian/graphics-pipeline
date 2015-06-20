#include "lighting.h"
#include <glm/glm.hpp>

Lighting::Lighting() {
  source = glm::vec3(-3.f, 3.f, 1.f);
  ka = glm::vec3(0.f);
  kd = glm::vec3(0.f);
  ks = glm::vec3(0.f);
  ns = 1;
  attenuation = 0.5;
  displayLight = 0;
}
Lighting::~Lighting() {}

void Lighting::shading(const glm::vec3& vertex, const glm::vec3& normal, LightColor& c , float spotlightAngle)
{
  // Check if in spotlight
  glm::vec3 lightDirection(glm::normalize(source - vertex));
  float vertexSpotlightAngle = glm::dot(lightDirection, glm::normalize(source));
  if ( spotlightAngle > 0 && vertexSpotlightAngle < spotlightAngle) {
    c = LightColor(glm::vec3(0.1f), glm::vec3(0.f), glm::vec3(0.f));
    return;
  }

  // Ambient Light
  float ambientIntensity = 1;
  float ambient = ambientIntensity;
  // Diffuse Light
  float diffuseIntensity = 1.2;
  glm::vec3 normalN = glm::normalize(normal);
  float diffuse = diffuseIntensity * glm::dot(normalN, lightDirection);
  diffuse = diffuse > 0 ? diffuse : 0;
  // Specular Light
  glm::vec3 viewDirection = cameraTarget - cameraPos;
  glm::vec3 reflectDirection(glm::reflect(lightDirection, normalN)); 
  float specularDot = glm::dot(reflectDirection, viewDirection);
  specularDot = specularDot > 0 ? specularDot : 0;
  if (ns <= 0) ns = 1;
  float specular = glm::pow(specularDot, ns);

  // Write into LightColor
  if (displayLight==0 || displayLight==1) c.ambient = ka * ambient;
  else c.ambient = glm::vec3(0.f);
  if (displayLight==0 || displayLight==2) c.diffuse = attenuation * kd * diffuse;
  else c.diffuse = glm::vec3(0.f);
  if (displayLight==0 || displayLight==3) c.specular = attenuation * ks * specular;
  else c.specular = glm::vec3(0.f);
}

void Lighting::directionalShading(const glm::vec3& normal, LightColor& c)
{
  // Ambient Light
  float ambientIntensity = 1;
  float ambient = ambientIntensity;
  // Diffuse Light
  float diffuseIntensity = 1.2;
  glm::vec3 normalN = glm::normalize(normal);
  glm::vec3 sourceN = glm::normalize(source);
  float diffuse = diffuseIntensity * glm::dot(normalN, sourceN);
  diffuse = diffuse > 0 ? diffuse : 0;
  // Specular Light
  glm::vec3 viewDirection = cameraTarget - cameraPos;
  glm::vec3 reflectDirection(glm::reflect(sourceN, normalN)); 
  float specularDot = glm::dot(reflectDirection, viewDirection);
  specularDot = specularDot > 0 ? specularDot : 0;
  if (ns <= 0) ns = 1;
  float specular = glm::pow(specularDot, ns);

  // Write into LightColor
  if (displayLight==0 || displayLight==1) c.ambient = ka * ambient;
  else c.ambient = glm::vec3(0.f);
  if (displayLight==0 || displayLight==2) c.diffuse = attenuation * kd * diffuse;
  else c.diffuse = glm::vec3(0.f);
  if (displayLight==0 || displayLight==3) c.specular = attenuation * ks * specular;
  else c.specular = glm::vec3(0.f);
}

void Lighting::setParameter(const glm::vec3& Ka,const glm::vec3& Kd,const glm::vec3& Ks,const int& Ns)
{
	ka = Ka;
	kd = Kd;
	ks = Ks;
	ns = Ns;
}
