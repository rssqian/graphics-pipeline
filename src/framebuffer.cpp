#include "framebuffer.h"
#include "model.h"
#include <cmath>

extern int shading;
extern vec3 color;

Framebuffer::Framebuffer(int w, int h)
  : width(w), height(h), clearColor(0.f)
{
	int numPixel = w*h;
	colorBuffer = new vec3[numPixel];
	depthBuffer = new float[numPixel];
	clear();
}

Framebuffer::~Framebuffer() 
{
	if(colorBuffer) delete[] colorBuffer;
	if(depthBuffer) delete[] depthBuffer;
}

void Framebuffer::clear() const 
{
	int numPixel = width * height;
	for (int i = 0; i < numPixel; ++i) {
		colorBuffer[i] = clearColor;
		depthBuffer[i] = DEPTH_INF;
	}
}

void Framebuffer::setClearColor(const vec3 color) 
{
	clearColor = color;
}

void Framebuffer::draw(int ix, int iy, float z, vec3 c) const {
	if(ix < 0 || ix >= width || iy < 0 || iy >= height) {
		return;
	}
	int idx = iy * width + ix;
	if (z <= depthBuffer[idx]) {
		if (shading==0) { 
			c = color;
			c.x *= ((-z+500)/1.0)/500;
			c.y *= ((-z+500)/1.0)/500;
			c.z *= ((-z+500)/1.0)/500;
			colorBuffer[idx] = c;
		} else colorBuffer[idx] = c;
		depthBuffer[idx] = z;
	}
}

const vec3* Framebuffer::getPixels() const {
	return colorBuffer;
}

void Framebuffer::writePPM(string filename) const {

	char* buffer = new char[height*width*3];
	for(int i = 0; i < height*width; ++i) {
		buffer[3*i  ] = (char)(colorBuffer[i].x*255.f);
		buffer[3*i+1] = (char)(colorBuffer[i].y*255.f);
		buffer[3*i+2] = (char)(colorBuffer[i].z*255.f);
	}

	ofstream ofs(filename.c_str(), ios::binary);
	ofs << "P6" << endl
		<< width << " " << height << endl
		<< "255" << endl;
	ofs.write(buffer, height*width*3);
	ofs.close();

	delete [] buffer;
}

float dotProduct(const vec3& v1,const vec3& v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

vec3 crossProduct(const vec3& v1,const vec3& v2)
{
	float x = v1.y*v2.z - v2.y*v1.z;
	float y = v1.z*v2.x - v2.z*v1.x;
	float z = v1.x*v2.y - v2.x*v1.y;
	return vec3(x,y,z);
}

void normalize(vec3& v)
{
	float length = sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
	if (length==0) return;
	v.x /= length;
	v.y /= length;
	v.z /= length;
}