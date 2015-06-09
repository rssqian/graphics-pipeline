#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <string>
#include <glm/vec3.hpp>
using namespace std;

struct RGB
{
	unsigned char r,g,b;
};

class RGBImage
{
public:
	RGBImage(): w(0), h(0), bits(0), data(nullptr) {}
	~RGBImage() {
		if(data) delete [] data;
	}
	void writePPM(const string& filename) const;
	void readPPM(const string& filename);

	int w;
	int h;
	int bits;
	RGB* data;
};

class Material
{
public:
	Material(string fileName):map_Ka(nullptr),map_Kd(nullptr),map_Ks(nullptr),map_d(nullptr) {
		mtlName = fileName;
	}
	~Material() {}

	glm::vec3 Ka; //ambient color(R,G,B), value between 0-1
	glm::vec3 Kd; //diffuse color(R,G,B), value between 0-1
	glm::vec3 Ks; //specular color(R,G,B), value between 0-1
	float Ns;     //specular exponent, value between 0-1000
	float d;
	//float Tr;
	int illuModel;
	RGBImage* map_Ka;
	RGBImage* map_Kd;
	RGBImage* map_Ks;
	RGBImage* map_Ns;
	RGBImage* map_d;
	RGBImage* map_bump;
	string mtlName;

};

#endif