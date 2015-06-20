#ifndef _FRAMEBUFFER_H_
#define _FRAMEBUFFER_H_

#include <iostream>
#include <fstream>
#include <vector>
#include "material.h"
using namespace std;

#define DEPTH_INF -1e20

class vec3 {
public:
	vec3(): x(0), y(0), z(0) {}
	vec3(float v): x(v), y(v), z(v) {}
	vec3(float x0, float y0, float z0): x(x0), y(y0), z(z0) {}
	~vec3() {}
	float x;
	float y;
	float z;
};

class Framebuffer {
public:
	Framebuffer(int w, int h);
	~Framebuffer();
	void clear() const;
	void setClearColor(const vec3 color);
	void draw(int ix, int iy, float depth, vec3 color) const;
	const vec3* getPixels() const;
	void writePPM(string fileName) const;
	// You can add new member functions here.

private:
	int width;
	int height;
	vec3 clearColor;
	vec3* colorBuffer;
	float* depthBuffer;
	vector<Material*> mtlBuffer;
	//Pixel* pixelBuffer;
};

float dotProduct(const vec3& v1,const vec3& v2);
vec3 crossProduct(const vec3& v1,const vec3& v2);
void normalize(vec3& v);

#endif
