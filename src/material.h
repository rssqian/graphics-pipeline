#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <string>
#include <glm/vec3.hpp>
#include <vector>
using namespace std;

struct RGB
{
	unsigned char r,g,b;
};

class RGBImage
{
public:
	RGBImage(): w(0), h(0), bits(0), data(nullptr), type(0) {}
	~RGBImage() {
		if(data) delete [] data;
	}
	void writePPM(const string& filename) const;
	void readPPM(const string& filename);
	void readDevIL(const string& filename, bool alpha);

	int w;
	int h;
	int bits;
	RGB* data;
	bool type; //0-RGB, 1-RGBA
};

class Material
{
public:
	Material(string fileName) {
		mtlName = fileName;
	}
	~Material() {
		if (map_Ka.size()!=0) {
			for (size_t i=0; i<map_Ka.size(); i++) {
				delete map_Ka[i];
			}
		}
		if (map_Kd.size()!=0) {
			for (size_t i=0; i<map_Kd.size(); i++) {
				delete map_Kd[i];
			}
		}
		if (map_Ks.size()!=0) {
			for (size_t i=0; i<map_Ks.size(); i++) {
				delete map_Ks[i];
			}
		}
		if (map_Ns.size()!=0) {
			for (size_t i=0; i<map_Ns.size(); i++) {
				delete map_Ns[i];
			}
		}
		if (map_d.size()!=0) {
			for (size_t i=0; i<map_d.size(); i++) {
				delete map_d[i];
			}
		}
		if (map_bump.size()!=0) {
			for (size_t i=0; i<map_bump.size(); i++) {
				delete map_bump[i];
			}
		}
	}

	glm::vec3 Ka; //ambient color(R,G,B), value between 0-1
	glm::vec3 Kd; //diffuse color(R,G,B), value between 0-1
	glm::vec3 Ks; //specular color(R,G,B), value between 0-1
	float Ns;     //specular exponent, value between 0-1000
	float d;
	//float Tr;
	int illuModel;
	vector<RGBImage*> map_Ka;
	vector<RGBImage*> map_Kd;
	vector<RGBImage*> map_Ks;
	vector<RGBImage*> map_Ns;
	vector<RGBImage*> map_d;
	vector<RGBImage*> map_bump;
	string mtlName;
};

#endif