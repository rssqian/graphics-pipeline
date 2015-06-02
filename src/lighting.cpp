#include "lighting.h"
#include <glm/glm.hpp>

vec3 Lighting::shading(glm::vec3 vertex, glm::vec3 normal)
{
  //ambient
  float ambientIntensity = 1;
  float ambient = ambientIntensity;
  //diffuse
  float diffuseIntensity = 1;
  normal = glm::normalize(normal);
  glm::vec3 lightDirection = glm::normalize(source - vertex);
  float diffuse = diffuseIntensity * glm::dot(normal, lightDirection);
  diffuse = diffuse > 0 ? diffuse : 0;
  //specular
  glm::vec3 viewDirection = cameraTarget - cameraPos;
  glm::vec3 reflectDirection(glm::reflect(glm::normalize(-lightDirection), glm::normalize(normal))); 
  float specularDot = glm::dot(reflectDirection, viewDirection);
  specularDot = specularDot > 0 ? specularDot : 0;
  float specular = glm::pow(specularDot, ns);

  float attenuation = 1;
  glm::vec3 color = ka * ambient + attenuation*(kd * diffuse + ks * specular);
  return vec3(color.x, color.y, color.z);
}
