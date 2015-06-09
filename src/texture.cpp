#include "texture.h"

#include <iostream>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
using namespace std;

extern int textureAddressing;

size_t texCoord2imgCoord(glm::vec3& texCoord,size_t w,size_t h) {
	float imgCoordX,imgCoordY;
	imgCoordX = unsigned(texCoord.x * (w-1));
	imgCoordY = unsigned((1.f-texCoord.y) * (h-1));
	return w * imgCoordY + imgCoordX;
}

bool getTexture(Material* mtl,glm::vec3& texCoord,glm::vec3& ambient_c,glm::vec3& diffuse_c,glm::vec3& specular_c) {
	RGBImage* map;
	//glm::vec3 imgCoord;
	size_t actualCoord;
	diffuse_c = glm::vec3(1.f);
	//diffuse_c = diffuse_c + glm::vec3(0.5f);
	/*if (texCoord.x<0 || 1<texCoord.x || texCoord.y<0 || 1<texCoord.y) {
		cout << "texCoord (" << texCoord.x << "," << texCoord.y << ") ignored..." << endl;
		diffuse_c = glm::vec3(1.f,1.f,0.f);
		return;
	}*/
	//if (texCoord.x != texCoord.x - size_t(texCoord.x)) cout << "x = " << texCoord.x << "," << texCoord.x - size_t(texCoord.x) << endl;
	//if (texCoord.y != texCoord.y - size_t(texCoord.y)) cout << "y = " << texCoord.y << "," << texCoord.y - size_t(texCoord.y) << endl;
	
	if (textureAddressing == 1) {				/*===mirror mode===*/
		texCoord.x = texCoord.x - size_t(texCoord.x/2)*2;
		texCoord.y = texCoord.y - size_t(texCoord.y/2)*2;
		if (texCoord.x > 1) texCoord.x = 2 - texCoord.x;
		if (texCoord.y > 1) texCoord.y = 2 - texCoord.y;
	} else if (textureAddressing == 2) {		/*===clamp mode===*/
		if (texCoord.x > 1) texCoord.x = 1.f;
		if (texCoord.x < 0) texCoord.x = 0.f;
		if (texCoord.y > 1) texCoord.y = 1.f;
		if (texCoord.y < 0) texCoord.y = 0.f;
	} else {									/*===wrapping mode===*/
		texCoord.x = texCoord.x - size_t(texCoord.x);
		texCoord.y = texCoord.y - size_t(texCoord.y);
	}

	/* ambient texture */
	if (mtl->map_Ka) {
		map = mtl->map_Ka;
		actualCoord = texCoord2imgCoord(texCoord,map->w,map->h);
		//imgCoord.x = unsigned int(texCoord.x * (map->w-1));
		//imgCoord.y = unsigned int((1.f-texCoord.y) * (map->h-1));
		//actualCoord = (map->w)*imgCoord.y + imgCoord.x;
		ambient_c = glm::vec3(map->data[actualCoord].r / float(map->bits) * ambient_c.x,
							  map->data[actualCoord].g / float(map->bits) * ambient_c.y,
							  map->data[actualCoord].b / float(map->bits) * ambient_c.z);
	}
	/* diffuse texture */
	if (mtl->map_Kd) {
		map = mtl->map_Kd;
		//cout << texCoord.x << "," << texCoord.y << endl;
		actualCoord = texCoord2imgCoord(texCoord,map->w,map->h);
		//imgCoord.x = unsigned int(texCoord.x * (map->w-1));
		//imgCoord.y = unsigned int((1.f-texCoord.y) * (map->h-1));
		//actualCoord = (map->w)*imgCoord.y + imgCoord.x;
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
		actualCoord = texCoord2imgCoord(texCoord,map->w,map->h);
		//imgCoord.x = unsigned int(texCoord.x * (map->w-1));
		//imgCoord.y = unsigned int((1.f-texCoord.y) * (map->h-1));
		//actualCoord = (map->w)*imgCoord.y + imgCoord.x;
		specular_c = glm::vec3(map->data[actualCoord].r / float(map->bits) * specular_c.x,
							   map->data[actualCoord].g / float(map->bits) * specular_c.y,
							   map->data[actualCoord].b / float(map->bits) * specular_c.z);
	}
	return true;
}
