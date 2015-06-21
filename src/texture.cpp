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

void texFiltering(float LOD, int filterMode, glm::vec3 &afterColor,glm::vec3& texCoord, vector<RGBImage*>& texMap)
{
    float imgCoordX, imgCoordY;
    int CoordX, CoordY;
    int x_y0, x_y1, x_y2, x_y3;

    if (filterMode==1) // 1:Nearest
    {
        imgCoordX = texCoord.x * (texMap[0]->w - 1);
        imgCoordY = (1.f-texCoord.y) * (texMap[0]->h - 1);
        CoordX = int(imgCoordX);
        CoordY = int(imgCoordY);
        x_y0 = CoordX * texMap[0]->w + CoordY;
        afterColor.x = texMap[0]->data[x_y0].r;
        afterColor.y = texMap[0]->data[x_y0].g;
        afterColor.z = texMap[0]->data[x_y0].b;          
    }

    else if (filterMode==2) // 2:Linear
    {
        imgCoordX = texCoord.x * (texMap[0]->w - 1);
        imgCoordY = (1.f-texCoord.y) * (texMap[0]->h - 1);
        CoordX = int(imgCoordX);
        CoordY = int(imgCoordY);
        x_y0 = CoordX * texMap[0]->w + CoordY;
        x_y1 = (CoordX+1) * texMap[0]->w + CoordY;
        x_y2 = CoordX * texMap[0]->w + CoordY + 1;
        x_y3 = (CoordX+1) * texMap[0]->w + CoordY + 1;
        afterColor.x = texMap[0]->data[x_y0].r * (CoordX + 1 - imgCoordX)
                     + texMap[0]->data[x_y1].r * (imgCoordX - CoordX)
                     + texMap[0]->data[x_y2].r * (CoordY + 1 - imgCoordY)
                     + texMap[0]->data[x_y3].r * (imgCoordY - CoordY);
        afterColor.y = texMap[0]->data[x_y0].g * (CoordX + 1 - imgCoordX)
                     + texMap[0]->data[x_y1].g * (imgCoordX - CoordX)
                     + texMap[0]->data[x_y2].g * (CoordY + 1 - imgCoordY)
                     + texMap[0]->data[x_y3].g * (imgCoordY - CoordY);
        afterColor.z = texMap[0]->data[x_y0].b * (CoordX + 1 - imgCoordX)
                     + texMap[0]->data[x_y1].b * (imgCoordX - CoordX)
                     + texMap[0]->data[x_y2].b * (CoordY + 1 - imgCoordY)
                     + texMap[0]->data[x_y3].b * (imgCoordY - CoordY);
    }

    else if (filterMode==3) // 3:Nearest-Mipmap-Nearest
    {
		//cout << "f3 = " << LOD << endl;
		//cout << texMap.size() << endl;
        imgCoordX = texCoord.x * (texMap[int(LOD)]->w - 1);
        imgCoordY = (1.f-texCoord.y) * (texMap[int(LOD)]->h - 1);
        CoordX = int(imgCoordX);
        CoordY = int(imgCoordY);
        x_y0 = CoordX * texMap[int(LOD)]->w + CoordY;
        afterColor.x = texMap[int(LOD)]->data[x_y0].r;
        afterColor.y = texMap[int(LOD)]->data[x_y0].g;
        afterColor.z = texMap[int(LOD)]->data[x_y0].b;          
    }

    else if (filterMode==4) // 4:Linear-Mipmap-Nearest
    {
        imgCoordX = texCoord.x * (texMap[int(LOD)]->w - 1);
        imgCoordY = (1.f-texCoord.y) * (texMap[int(LOD)]->h - 1);
        CoordX = int(imgCoordX);
        CoordY = int(imgCoordY);
        x_y0 = CoordX * texMap[int(LOD)]->w + CoordY;
        x_y1 = (CoordX+1) * texMap[int(LOD)]->w + CoordY;
        x_y2 = CoordX * texMap[int(LOD)]->w + CoordY + 1;
        x_y3 = (CoordX+1) * texMap[int(LOD)]->w + CoordY + 1;
        afterColor.x = texMap[int(LOD)]->data[x_y0].r * (CoordX + 1 - imgCoordX)
                     + texMap[int(LOD)]->data[x_y1].r * (imgCoordX - CoordX)
                     + texMap[int(LOD)]->data[x_y2].r * (CoordY + 1 - imgCoordY)
                     + texMap[int(LOD)]->data[x_y3].r * (imgCoordY - CoordY);
        afterColor.y = texMap[int(LOD)]->data[x_y0].g * (CoordX + 1 - imgCoordX)
                     + texMap[int(LOD)]->data[x_y1].g * (imgCoordX - CoordX)
                     + texMap[int(LOD)]->data[x_y2].g * (CoordY + 1 - imgCoordY)
                     + texMap[int(LOD)]->data[x_y3].g * (imgCoordY - CoordY);
        afterColor.z = texMap[int(LOD)]->data[x_y0].b * (CoordX + 1 - imgCoordX)
                     + texMap[int(LOD)]->data[x_y1].b * (imgCoordX - CoordX)
                     + texMap[int(LOD)]->data[x_y2].b * (CoordY + 1 - imgCoordY)
                     + texMap[int(LOD)]->data[x_y3].b * (imgCoordY - CoordY);
    }

    else if (filterMode==5) // 5:Nearest-Mipmap-Linear
    {
        imgCoordX = texCoord.x * (texMap[int(LOD)]->w - 1);
        imgCoordY = (1.f-texCoord.y) * (texMap[int(LOD)]->h - 1);
        CoordX = int(imgCoordX);
        CoordY = int(imgCoordY);
        x_y0 = (CoordX) * texMap[int(LOD)]->w + CoordY;
        afterColor.x = texMap[int(LOD)]->data[x_y0].r * (int(LOD)+1-LOD);
        afterColor.y = texMap[int(LOD)]->data[x_y0].g * (int(LOD)+1-LOD);
        afterColor.z = texMap[int(LOD)]->data[x_y0].b * (int(LOD)+1-LOD);
        imgCoordX = texCoord.x * (texMap[int(LOD)+1]->w - 1);
        imgCoordY = (1.f-texCoord.y) * (texMap[int(LOD)+1]->h - 1);
        CoordX = int(imgCoordX);
        CoordY = int(imgCoordY);
        x_y0 = CoordX * texMap[int(LOD)+1]->w + CoordY;
        afterColor.x += texMap[int(LOD)+1]->data[x_y0].r * (LOD -int(LOD));
        afterColor.y += texMap[int(LOD)+1]->data[x_y0].g * (LOD -int(LOD));
        afterColor.z += texMap[int(LOD)+1]->data[x_y0].b * (LOD -int(LOD));
    }

    else if (filterMode==6) // 6:Linear-Mipmap-Linear
    {
        imgCoordX = texCoord.x * (texMap[int(LOD)]->w - 1);
        imgCoordY = (1.f-texCoord.y) * (texMap[int(LOD)]->h - 1);
        CoordX = int(imgCoordX);
        CoordY = int(imgCoordY);
        x_y0 = CoordX * texMap[int(LOD)]->w + CoordY;
        x_y1 = (CoordX+1) * texMap[int(LOD)]->w + CoordY;
        x_y2 = CoordX * texMap[int(LOD)]->w + CoordY + 1;
        x_y3 = (CoordX+1) * texMap[int(LOD)]->w + CoordY + 1;
        afterColor.x =(texMap[int(LOD)]->data[x_y0].r * (CoordX + 1 - imgCoordX)
                     + texMap[int(LOD)]->data[x_y1].r * (imgCoordX - CoordX)
                     + texMap[int(LOD)]->data[x_y2].r * (CoordY + 1 - imgCoordY)
                     + texMap[int(LOD)]->data[x_y3].r * (imgCoordY - CoordY) ) * (int(LOD)+1-LOD);
        afterColor.y =(texMap[int(LOD)]->data[x_y0].g * (CoordX + 1 - imgCoordX)
                     + texMap[int(LOD)]->data[x_y1].g * (imgCoordX - CoordX)
                     + texMap[int(LOD)]->data[x_y2].g * (CoordY + 1 - imgCoordY)
                     + texMap[int(LOD)]->data[x_y3].g * (imgCoordY - CoordY) ) * (int(LOD)+1-LOD);
        afterColor.z =(texMap[int(LOD)]->data[x_y0].b * (CoordX + 1 - imgCoordX)
                     + texMap[int(LOD)]->data[x_y1].b * (imgCoordX - CoordX)
                     + texMap[int(LOD)]->data[x_y2].b * (CoordY + 1 - imgCoordY)
                     + texMap[int(LOD)]->data[x_y3].b * (imgCoordY - CoordY) ) * (int(LOD)+1-LOD);

        imgCoordX = texCoord.x * (texMap[int(LOD)+1]->w - 1);
        imgCoordY = (1.f-texCoord.y) * (texMap[int(LOD)+1]->h - 1);
        CoordX = int(imgCoordX);
        CoordY = int(imgCoordY);
        x_y0 = CoordX * texMap[int(LOD)+1]->w + CoordY;
        x_y1 = (CoordX+1) * texMap[int(LOD)+1]->w + CoordY;
        x_y2 = CoordX * texMap[int(LOD)+1]->w + CoordY + 1;
        x_y3 = (CoordX+1) * texMap[int(LOD)+1]->w + CoordY + 1;
        afterColor.x +=(texMap[int(LOD)+1]->data[x_y0].r * (CoordX + 1 - imgCoordX)
                      + texMap[int(LOD)+1]->data[x_y1].r * (imgCoordX - CoordX)
                      + texMap[int(LOD)+1]->data[x_y2].r * (CoordY + 1 - imgCoordY)
                      + texMap[int(LOD)+1]->data[x_y3].r * (imgCoordY - CoordY) ) * (LOD -int(LOD));
        afterColor.y +=(texMap[int(LOD)+1]->data[x_y0].g * (CoordX + 1 - imgCoordX)
                      + texMap[int(LOD)+1]->data[x_y1].g * (imgCoordX - CoordX)
                      + texMap[int(LOD)+1]->data[x_y2].g * (CoordY + 1 - imgCoordY)
                      + texMap[int(LOD)+1]->data[x_y3].g * (imgCoordY - CoordY) ) * (LOD -int(LOD));
        afterColor.z +=(texMap[int(LOD)+1]->data[x_y0].b * (CoordX + 1 - imgCoordX)
                      + texMap[int(LOD)+1]->data[x_y1].b * (imgCoordX - CoordX)
                      + texMap[int(LOD)+1]->data[x_y2].b * (CoordY + 1 - imgCoordY)
                      + texMap[int(LOD)+1]->data[x_y3].b * (imgCoordY - CoordY) ) * (LOD -int(LOD));
    }
	afterColor.x /= float(texMap[0]->bits);
	afterColor.y /= float(texMap[0]->bits);
	afterColor.z /= float(texMap[0]->bits);
}

bool getTexture(Material* mtl, glm::vec3& texCoord,
				glm::vec3& ambient_c, glm::vec3& diffuse_c, glm::vec3& specular_c,
				int& filterMode, float& LODu, float& LODv) {
	RGBImage* map;
	vector<RGBImage*> texMap;
	size_t actualCoord;
	float LOD;

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
	if (mtl->map_Ka.size()) {
		/*map = mtl->map_Ka[0];
		actualCoord = texCoord2imgCoord(texCoord,map->w,map->h);
		//imgCoord.x = unsigned int(texCoord.x * (map->w-1));
		//imgCoord.y = unsigned int((1.f-texCoord.y) * (map->h-1));
		//actualCoord = (map->w)*imgCoord.y + imgCoord.x;
		if (actualCoord < map->w*map->h) {
			ambient_c = glm::vec3(map->data[actualCoord].r / float(map->bits) * ambient_c.x,
								  map->data[actualCoord].g / float(map->bits) * ambient_c.y,
								  map->data[actualCoord].b / float(map->bits) * ambient_c.z);
		}*/
		//LOD=LOD+;
		texMap = mtl->map_Ka;
		LOD = (LODu*texMap[0]->w > LODv*texMap[0]->h) ? LODu*texMap[0]->w : LODv*texMap[0]->h;
		LOD = log10(LOD)/log10(2.0)/2;
		texFiltering(LOD, filterMode, ambient_c, texCoord, texMap);
	}
	/* diffuse texture */
	if (mtl->map_Kd.size()) {
		/*map = mtl->map_Kd[0];
		//cout << texCoord.x << "," << texCoord.y << endl;
		actualCoord = texCoord2imgCoord(texCoord,map->w,map->h);
		
		if (actualCoord < map->w*map->h) {
			diffuse_c = glm::vec3(map->data[actualCoord].r / float(map->bits) * diffuse_c.x,
								  map->data[actualCoord].g / float(map->bits) * diffuse_c.y,
								  map->data[actualCoord].b / float(map->bits) * diffuse_c.z);
		}*/
		//imgCoord.x = unsigned int(texCoord.x * (map->w-1));
		//imgCoord.y = unsigned int((1.f-texCoord.y) * (map->h-1));
		//actualCoord = (map->w)*imgCoord.y + imgCoord.x;

		texMap = mtl->map_Kd;
		LOD = (LODu*texMap[0]->w > LODv*texMap[0]->h) ? LODu*texMap[0]->w : LODv*texMap[0]->h;
		LOD = log10(LOD)/log10(2.0)/2;
		texFiltering(LOD, filterMode, diffuse_c, texCoord, texMap);

		//cout << "===Texture Mapping===" << endl;
		//cout << "texCoord   = (" << texCoord.x << "," << texCoord.y << ")" << endl;
		//cout << "imageCoord = (" << imgCoord.x << "," << imgCoord.y << ")" << endl;
		//cout << "data[]     = (" << diffuse_c.x << "," << diffuse_c.y
		//	 << "," << diffuse_c.z << ")" << endl;
	}
	/* specular texture */
	if (mtl->map_Ks.size()) {
		/*map = mtl->map_Ks[0];
		actualCoord = texCoord2imgCoord(texCoord,map->w,map->h);
		//imgCoord.x = unsigned int(texCoord.x * (map->w-1));
		//imgCoord.y = unsigned int((1.f-texCoord.y) * (map->h-1));
		//actualCoord = (map->w)*imgCoord.y + imgCoord.x;
		if (actualCoord < map->w*map->h) {
			specular_c = glm::vec3(map->data[actualCoord].r / float(map->bits) * specular_c.x,
								   map->data[actualCoord].g / float(map->bits) * specular_c.y,
								   map->data[actualCoord].b / float(map->bits) * specular_c.z);
		}*/

		texMap = mtl->map_Ks;
		LOD = (LODu*texMap[0]->w > LODv*texMap[0]->h) ? LODu*texMap[0]->w : LODv*texMap[0]->h;
		LOD = log10(LOD)/log10(2.0)/2;
		texFiltering(LOD, filterMode, specular_c, texCoord, texMap);
	}
	return true;
}
