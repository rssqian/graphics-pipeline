#include "material.h"
#include "framebuffer.h"

bool getTexture(Material* mtl,glm::vec3& texCoord,glm::vec3& ambient_c,glm::vec3& diffuse_c,glm::vec3& specular_c, int filterMode, float LOD);