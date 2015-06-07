#include "texture.h"

#include <iostream>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
using namespace std;

void getTexture(Material* mtl,glm::vec3& texCoord,glm::vec3& ambient_c,glm::vec3& diffuse_c,glm::vec3& specular_c) {
	RGBImage* map;
	glm::vec3 imgCoord;
	int actualCoord;
	diffuse_c = glm::vec3(1.f);
	//diffuse_c = diffuse_c + glm::vec3(0.5f);
	if (texCoord.x<0 || 1<texCoord.x || texCoord.y<0 || 1<texCoord.y) {
		cout << "texCoord (" << texCoord.x << "," << texCoord.y << ") ignored..." << endl;
		diffuse_c = glm::vec3(1.f,1.f,0.f);
		return;
	}

	/* ambient texture */
	if (mtl->map_Ka) {
		map = mtl->map_Ka;
		
		imgCoord.x = unsigned int(texCoord.x * map->w);
		imgCoord.y = unsigned int((1.f-texCoord.y) * map->h);
		actualCoord = (map->w)*imgCoord.y + imgCoord.x;
		ambient_c = glm::vec3(map->data[actualCoord].r / float(map->bits) * ambient_c.x,
							  map->data[actualCoord].g / float(map->bits) * ambient_c.y,
							  map->data[actualCoord].b / float(map->bits) * ambient_c.z);
	}
	/* diffuse texture */
	if (mtl->map_Kd) {
		map = mtl->map_Kd;
		imgCoord.x = unsigned int(texCoord.x * map->w);
		imgCoord.y = unsigned int((/*1.f-*/texCoord.y) * map->h);
		actualCoord = (map->w)*imgCoord.y + imgCoord.x;
		/*cout << "===Texture Mapping===" << endl;
		cout << "texCoord   = (" << texCoord.x << "," << texCoord.y << ")" << endl;
		cout << "imageCoord = (" << imgCoord.x << "," << imgCoord.y << ")" << endl;
		cout << "data[]     = (" << float(map->data[actualCoord].r) << "," << float(map->data[actualCoord].g) 
			 << "," << float(map->data[actualCoord].b) << ")" << endl;*/
		diffuse_c = glm::vec3(map->data[actualCoord].r / float(map->bits) * diffuse_c.x,
							  map->data[actualCoord].g / float(map->bits) * diffuse_c.y,
							  map->data[actualCoord].b / float(map->bits) * diffuse_c.z);
	}
	/* specular texture */
	if (mtl->map_Ks) {
		map = mtl->map_Ks;
		imgCoord.x = unsigned int(texCoord.x * map->w);
		imgCoord.y = unsigned int((1.f-texCoord.y) * map->h);
		actualCoord = (map->w)*imgCoord.y + imgCoord.x;
		specular_c = glm::vec3(map->data[actualCoord].r / float(map->bits) * specular_c.x,
							   map->data[actualCoord].g / float(map->bits) * specular_c.y,
							   map->data[actualCoord].b / float(map->bits) * specular_c.z);
	}
	
}