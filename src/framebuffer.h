#ifndef _FRAMEBUFFER_H_
#define _FRAMEBUFFER_H_

#include <iostream>
#include <fstream>
#include <vector>
#include "material.h"
#include "lighting.h"
#include "texture.h"
#include "vec3.h"
using namespace std;

#define DEPTH_INF -1e20
extern Lighting light;
extern glm::vec3 ka;
extern glm::vec3 kd;
extern glm::vec3 ks;
extern int ns;

class Framebuffer {
public:
	Framebuffer(int w, int h);
	~Framebuffer();
	void clear() const;
	void setClearColor(const vec3 color);
	void draw(int ix, int iy, float depth, vec3 color, LightColor KaKdKs, vec3 texCoord, Material* mtlptr) const;
	const vec3* getPixels() const;
	void writePPM(string fileName) const;
	// You can add new member functions here.
	bool celShading(int ix,int iy);
	bool texturing(int ix,int iy);

private:
	int width;
	int height;
	vec3 clearColor;
	vec3* colorBuffer;
	float* depthBuffer;
	LightColor* KaKdKsBuffer;
	vec3* texCoordBuffer;
	Material** mtlBuffer;
};

float dotProduct(const vec3& v1,const vec3& v2);
vec3 crossProduct(const vec3& v1,const vec3& v2);
void normalize(vec3& v);
vec3 glm2vec3(const glm::vec3& v);

#endif
