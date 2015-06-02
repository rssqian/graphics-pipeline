#include "texture.h"

#include <iostream>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
using namespace std;

void getTexture(Material* mtl,glm::vec3 texCoord,glm::vec3& ambient_c,glm::vec3& diffuse_c,glm::vec3& specular_c) {
	RGBImage* map;
	glm::vec3 imgCoord;
	int actualCoord;
	imgCoord.x = unsigned int(texCoord.x * map->w);
	imgCoord.y = unsigned int((1.f-texCoord.y) * map->h);
	actualCoord = (map->w)*imgCoord.y + (map->h)*imgCoord.x;

	/* ambient texture */
	map = mtl->map_Ka;
	ambient_c = glm::vec3(map->data[actualCoord].r,
						  map->data[actualCoord].g,
						  map->data[actualCoord].b);
	/* diffuse texture */
	map = mtl->map_Kd;
	diffuse_c = glm::vec3(map->data[actualCoord].r,
						  map->data[actualCoord].g,
						  map->data[actualCoord].b);
	/* specular texture */
	map = mtl->map_Ks;
	specular_c = glm::vec3(map->data[actualCoord].r,
						   map->data[actualCoord].g,
						   map->data[actualCoord].b);
	
}