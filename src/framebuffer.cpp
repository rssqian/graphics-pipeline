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
	KaKdKsBuffer = new LightColor[numPixel];
	texCoordBuffer = new vec3[numPixel];
	mtlBuffer = new Material*[numPixel];
	clear();
}

Framebuffer::~Framebuffer() 
{
	if(colorBuffer) delete[] colorBuffer;
	if(depthBuffer) delete[] depthBuffer;
	if(KaKdKsBuffer) delete [] KaKdKsBuffer;
	if(texCoordBuffer) delete [] texCoordBuffer;
	if(mtlBuffer) delete [] mtlBuffer;
}

void Framebuffer::clear() const 
{
	int numPixel = width * height;
	for (int i = 0; i < numPixel; ++i) {
		colorBuffer[i] = clearColor;
		depthBuffer[i] = DEPTH_INF;
		KaKdKsBuffer[i] = LightColor();
		//texCoordBuffer[i] = vec3()
		mtlBuffer[i] = nullptr;
	}
}

void Framebuffer::setClearColor(const vec3 color) 
{
	clearColor = color;
}

void Framebuffer::draw(int ix, int iy, float z, vec3 c, LightColor KaKdKs, vec3 texCoord, Material* mtlptr) const {
	if(ix < 0 || ix >= width || iy < 0 || iy >= height) {
		return;
	}
	int idx = iy * width + ix;
	if (z >= depthBuffer[idx]) {
		if (shading==0) { 
			c = color;
			c.x *= ((z+1)/1.0)/1;
			c.y *= ((z+1)/1.0)/1;
			c.z *= ((z+1)/1.0)/1;
			colorBuffer[idx] = c;
		} else colorBuffer[idx] = c;
		depthBuffer[idx] = z;
		KaKdKsBuffer[idx] = KaKdKs;
		texCoordBuffer[idx] = texCoord;
		mtlBuffer[idx] = mtlptr;
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

bool Framebuffer::celShading(int ix,int iy)
{
	int idx = iy * width + ix;
	if (mtlBuffer[idx] != nullptr) {
		float i= (KaKdKsBuffer[idx].diffuse.x + KaKdKsBuffer[idx].diffuse.y + KaKdKsBuffer[idx].diffuse.z)/3.f;

		if (i > 0.3) {
			KaKdKsBuffer[idx].diffuse.x = 0.8;
			KaKdKsBuffer[idx].diffuse.y = 0.8;
			KaKdKsBuffer[idx].diffuse.z = 0.8;
		} else if (i > 0.1) {
			KaKdKsBuffer[idx].diffuse.x = 0.5;
			KaKdKsBuffer[idx].diffuse.y = 0.5;
			KaKdKsBuffer[idx].diffuse.z = 0.5;
		} else {
			KaKdKsBuffer[idx].diffuse.x = 0.3;
			KaKdKsBuffer[idx].diffuse.y = 0.3;
			KaKdKsBuffer[idx].diffuse.z = 0.3;
		}
	}
	return true;
}

bool Framebuffer::texturing(int ix,int iy, int filterMode)
{
	int idx = iy * width + ix;
	if (mtlBuffer[idx]!=nullptr) {
		glm::vec3 texCoord(texCoordBuffer[idx].x,texCoordBuffer[idx].y,texCoordBuffer[idx].z);
		float LODu = 0, LODv = 0, temp = 0;
		if (filterMode>=3) {
			int target;
			target = iy * width + (ix+1);
			if (target>=0 && target<width*height && mtlBuffer[idx] == mtlBuffer[target]) {
				LODu = abs(texCoordBuffer[idx].x-texCoordBuffer[target].x);
				LODv = abs(texCoordBuffer[idx].y-texCoordBuffer[target].y)*(texCoordBuffer[idx].y-texCoordBuffer[target].y);
			}
			target = iy * width + (ix-1);
			if (target>=0 && target<width*height && mtlBuffer[idx] == mtlBuffer[iy * width + (ix-1)]) {
				temp = abs(texCoordBuffer[idx].x-texCoordBuffer[target].x);
				LODu = (LODu>temp) ? LODu : temp;
				temp = abs(texCoordBuffer[idx].y-texCoordBuffer[target].y);
				LODv = (LODv>temp) ? LODv : temp;
			}
			target = (iy+1) * width + ix;
			if (target>=0 && target<width*height && mtlBuffer[idx] == mtlBuffer[(iy+1) * width + ix]) {
				temp = abs(texCoordBuffer[idx].x-texCoordBuffer[target].x); 
				LODu = (LODu>temp) ? LODu : temp;
				temp = abs(texCoordBuffer[idx].y-texCoordBuffer[target].y);
				LODv = (LODv>temp) ? LODv : temp;
			}
			target = (iy-1) * width + ix;
			if (target>=0 && target<width*height && mtlBuffer[idx] == mtlBuffer[(iy-1) * width + ix]) {
				temp = abs(texCoordBuffer[idx].x-texCoordBuffer[target].x);
				LODu = (LODu>temp) ? LODu : temp;
				temp = abs(texCoordBuffer[idx].y-texCoordBuffer[target].y);
				LODv = (LODv>temp) ? LODv : temp;
			}
	//		float LOD = (LOD1>LOD2) ? LOD1 : LOD2;
	//		LOD = (LOD3>LOD) ? LOD3 : LOD;
	//		LOD = (LOD4>LOD) ? LOD4 : LOD;
	//		LOD = log10(LOD)/log10(2.0)/2+10;
			//cout << LOD << endl;
		}
		getTexture(mtlBuffer[idx],texCoord,KaKdKsBuffer[idx].ambient,KaKdKsBuffer[idx].diffuse,KaKdKsBuffer[idx].specular, filterMode, LODu, LODv);
		colorBuffer[idx].x = KaKdKsBuffer[idx].ambient.x + KaKdKsBuffer[idx].diffuse.x + KaKdKsBuffer[idx].specular.x;
		colorBuffer[idx].y = KaKdKsBuffer[idx].ambient.y + KaKdKsBuffer[idx].diffuse.y + KaKdKsBuffer[idx].specular.y;
		colorBuffer[idx].z = KaKdKsBuffer[idx].ambient.z + KaKdKsBuffer[idx].diffuse.z + KaKdKsBuffer[idx].specular.z;
	}
	return true;
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

vec3 glm2vec3(const glm::vec3& v)
{
	return vec3(v.x,v.y,v.z);
}