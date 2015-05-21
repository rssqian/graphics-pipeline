#include <GL/glut.h>
#include <iostream>
#include <ctime>
#include <cmath>
#include "model.h"
#include "framebuffer.h"
using namespace std;

#define PI 3.14159265

Model** modelPtr;

/* frame size */
int screenWidth = 800;
int screenHeight = 600;
int screenWidth_half = 400;
int screenHeight_half = 300;

/* theta */
double rotateSpeed = 0.05;
double thetaX = 0;
double thetaY = 0;

/*mode*/
int wireframe_filled = 0; //0-wireframe, 1-filled surface
int shading = 0; //0-no shading, 1-flat shading, 2-smooth shading

int curModelIdx;
bool culling;
Framebuffer framebuffer(screenWidth, screenHeight);
vec3 color(1.f);

/* model names */
char* modelNames[] = {
	"model/quad.obj",
	"model/couch.obj",
	"model/blaze.obj",
	"model/ateneal.obj",
	"model/venusm.obj",
	"model/bunnyC.obj",
	"model/duck4KN.obj",
	"model/happy10KN.obj",
	"model/dragon10KN.obj",
	"model/elephant16KN.obj",
	"model/Statue_of_Liberty.obj",
	"model/Nissan_Pathfinder.obj"
};
const int numModels = sizeof(modelNames) / sizeof(char*);

void printHelp() 
{
	printf("===========================================\n");
	printf("  H/h: Show help menu                      \n");
	printf("  M/m: Select model                        \n");
	printf("  UP/DOWN: Rotate along x-axis             \n");
	printf("  LEFT/RIGHT: Rotate along y-axis          \n");
	printf("  C/c: Toggle back-face culling            \n");
	printf("  B/b: Toggle background color             \n");
	printf("  L/l: Toggle lighting mode                \n");
	printf("  W/w: Toggle wireframe mode               \n");
	printf("  S/s: Save image                          \n");
	printf("  Q/q: Quit                                \n");
	printf("===========================================\n\n");
}

void init() 
{
	modelPtr = new Model*[numModels];
	for(int i = 0; i < numModels; ++i) {
		/* load models */
		modelPtr[i] = readObj(modelNames[i]);

		/* normalize coordinates to [-0.5, +0.5] */
		float xmax, xmin, ymax, ymin, zmax, zmin, longest;
		float xmean, ymean, zmean;
		xmax = xmin = modelPtr[i]->vertices[3];
		ymax = ymin = modelPtr[i]->vertices[4];
		zmax = zmin = modelPtr[i]->vertices[5];
		for(int v = 2; v <= modelPtr[i]->numVertices; ++v) {
			xmax = max(xmax, modelPtr[i]->vertices[3*v]);
			xmin = min(xmin, modelPtr[i]->vertices[3*v]);
			ymax = max(ymax, modelPtr[i]->vertices[3*v+1]);
			ymin = min(ymin, modelPtr[i]->vertices[3*v+1]);
			zmax = max(zmax, modelPtr[i]->vertices[3*v+2]);
			zmin = min(zmin, modelPtr[i]->vertices[3*v+2]);
		}
		longest = max(xmax - xmin, ymax - ymin);
		longest = max(longest, zmax - zmin);
		xmean = 0.5f*(xmax + xmin);
		ymean = 0.5f*(ymax + ymin);
		zmean = 0.5f*(zmax + zmin);
		
		for(int v = 1; v <= modelPtr[i]->numVertices; ++v) {
			modelPtr[i]->vertices[3*v  ] = (modelPtr[i]->vertices[3*v  ] - xmean)/longest;
			modelPtr[i]->vertices[3*v+1] = (modelPtr[i]->vertices[3*v+1] - ymean)/longest;
			modelPtr[i]->vertices[3*v+2] = (modelPtr[i]->vertices[3*v+2] - zmean)/longest;
		}
	}

	/* initialize parameters */
	curModelIdx = 0;
	culling = true;
}

vec3 transform(vec3& prev)
{
	float curX,curY,curZ;
	// rotate along x-axis
	curY = prev.y*cos(thetaX)-prev.z*sin(thetaX);
	curZ = prev.y*sin(thetaX)+prev.z*cos(thetaX);
	// prevY = curY;
	prev.z = curZ;
	// rotate along y-axis
	curX = prev.z*sin(thetaY)+prev.x*cos(thetaY);
	curZ = prev.z*cos(thetaY)-prev.x*sin(thetaY);
	return vec3(curX,curY,curZ);
}

void toScreenSpace(vec3& v,int& ix,int& iy,float& iz)
{
	int screenSide = min(screenWidth, screenHeight);
	float margin = 0.1f;
	// to ScreenSpace
	ix = int(((1.f-margin)*v.x)*screenSide) + screenWidth_half - 1;
	iy = int(((1.f-margin)*v.y)*screenSide) + screenHeight_half - 1;
	iz = v.z;
}

bool backFaceCulling(vec3* triangleV)   //input 3 vertex of the triangle
{
	vec3 v1(triangleV[0].x-triangleV[1].x,triangleV[0].y-triangleV[1].y,triangleV[0].z-triangleV[1].z);
	vec3 v2(triangleV[0].x-triangleV[2].x,triangleV[0].y-triangleV[2].y,triangleV[0].z-triangleV[2].z);
	vec3 v3 = crossProduct(v1,v2);
	normalize(v3);
	vec3 v4(0.f,0.f,-1.f);
	//cout << dotProduct(v3,v4) << endl;
	if (dotProduct(v3,v4) < 0) return true;
	else return false;
}

vec3 lighting(vec3 normal)     //input 3 triangle vertex
{
	//ambient
	float ambient_light_intensity =  1;
	float ambient_reflection_coefficient = 0.2;
	float ambient = ambient_light_intensity * ambient_reflection_coefficient;
	//diffuse
	float point_light_attenuation = 1;
	float point_light_intensity = 1;
	float diffuse_reflection_coefficient = 0.8;

	normalize(normal);
	vec3 light_direction(1.f,1.f,-2.f);
	normalize(light_direction);
	float diffuse = point_light_attenuation * point_light_intensity * diffuse_reflection_coefficient * dotProduct(normal,light_direction);
	//specular
	float specular = 0; //sum ()
	float intensity = ambient + diffuse + specular;
	vec3 c = color;
	c.x *= intensity;
	c.y *= intensity;
	c.z *= intensity;
	return c;
}

void drawStandingTriangle(const vec3& p1,const vec3& p2,const vec3& p3,
						  const vec3& n1,const vec3& n2,const vec3& n3,vec3 c) //p1.y >= p2.y >= p3.y
{
	//cout << "n1=" << n1.x << "\t" << n1.y << "\t" << n1.z << endl;
	//cout << "n2=" << n2.x << "\t" << n2.y << "\t" << n2.z << endl;
	//cout << "n3=" << n3.x << "\t" << n3.y << "\t" << n3.z << endl;
	int x_,y_=p1.y;
	float x1,x2,z1,z2;
	float z_;
	float nx_,ny_,nz_,nx1,nx2,ny1,ny2,nz1,nz2;
	while (y_ >= p3.y) {
		if (p1.y == p2.y) {
			//cout << "p1.y == p2.y" << endl;
			if (p1.x < p2.x) {
				x1 = p1.x + (p3.x-p1.x)/(p3.y-p1.y)*(y_-p1.y);
				z1 = p1.z + (p3.z-p1.z)/(p3.y-p1.y)*(y_-p1.y);
				x2 = p2.x + (p3.x-p2.x)/(p3.y-p2.y)*(y_-p2.y);
				z2 = p2.z + (p3.z-p2.z)/(p3.y-p2.y)*(y_-p2.y);
				if (shading==2) {
					nx1 = n1.x + (n3.x-n1.x)/(p3.y-p1.y)*(y_-p1.y);
					ny1 = n1.y + (n3.y-n1.y)/(p3.y-p1.y)*(y_-p1.y);
					nz1 = n1.z + (n3.z-n1.z)/(p3.y-p1.y)*(y_-p1.y);
					nx2 = n2.x + (n3.x-n2.x)/(p3.y-p2.y)*(y_-p2.y);
					ny2 = n2.y + (n3.y-n2.y)/(p3.y-p2.y)*(y_-p2.y);
					nz2 = n2.z + (n3.z-n2.z)/(p3.y-p2.y)*(y_-p2.y);
				}
			} else {
				x1 = p2.x + (p3.x-p2.x)/(p3.y-p2.y)*(y_-p2.y);
				z1 = p2.z + (p3.z-p2.z)/(p3.y-p2.y)*(y_-p2.y);
				x2 = p1.x + (p3.x-p1.x)/(p3.y-p1.y)*(y_-p1.y);
				z2 = p1.z + (p3.z-p1.z)/(p3.y-p1.y)*(y_-p1.y);
				if (shading==2) {
					nx2 = n1.x + (n3.x-n1.x)/(p3.y-p1.y)*(y_-p1.y);
					ny2 = n1.y + (n3.y-n1.y)/(p3.y-p1.y)*(y_-p1.y);
					nz2 = n1.z + (n3.z-n1.z)/(p3.y-p1.y)*(y_-p1.y);
					nx1 = n2.x + (n3.x-n2.x)/(p3.y-p2.y)*(y_-p2.y);
					ny1 = n2.y + (n3.y-n2.y)/(p3.y-p2.y)*(y_-p2.y);
					nz1 = n2.z + (n3.z-n2.z)/(p3.y-p2.y)*(y_-p2.y);
				}
			}
		} else if (p2.y == p3.y){ 
			//cout << "p2.y == p3.y" << endl;
			//x1 = x2 = p1.x;
			if (p2.x < p3.x) {
				x1 = p1.x + (p2.x-p1.x)/(p2.y-p1.y)*(y_-p1.y);
				z1 = p1.z + (p2.z-p1.z)/(p2.y-p1.y)*(y_-p1.y);
				x2 = p1.x + (p3.x-p1.x)/(p3.y-p1.y)*(y_-p1.y);
				z2 = p1.z + (p3.z-p1.z)/(p3.y-p1.y)*(y_-p1.y);
				if (shading==2) {
					nx1 = n1.x + (n2.x-n1.x)/(p2.y-p1.y)*(y_-p1.y);
					ny1 = n1.y + (n2.y-n1.y)/(p2.y-p1.y)*(y_-p1.y);
					nz1 = n1.z + (n2.z-n1.z)/(p2.y-p1.y)*(y_-p1.y);
					nx2 = n1.x + (n3.x-n1.x)/(p3.y-p1.y)*(y_-p1.y);
					ny2 = n1.y + (n3.y-n1.y)/(p3.y-p1.y)*(y_-p1.y);
					nz2 = n1.z + (n3.z-n1.z)/(p3.y-p1.y)*(y_-p1.y);
				}
			} else {
				x1 = p1.x + (p3.x-p1.x)/(p3.y-p1.y)*(y_-p1.y);
				z1 = p1.z + (p3.z-p1.z)/(p3.y-p1.y)*(y_-p1.y);
				x2 = p1.x + (p2.x-p1.x)/(p2.y-p1.y)*(y_-p1.y);
				z2 = p1.z + (p2.z-p1.z)/(p2.y-p1.y)*(y_-p1.y);
				if (shading==2) {
					nx1 = n1.x + (n3.x-n1.x)/(p3.y-p1.y)*(y_-p1.y);
					ny1 = n1.y + (n3.y-n1.y)/(p3.y-p1.y)*(y_-p1.y);
					nz1 = n1.z + (n3.z-n1.z)/(p3.y-p1.y)*(y_-p1.y);
					nx2 = n1.x + (n2.x-n1.x)/(p2.y-p1.y)*(y_-p1.y);
					ny2 = n1.y + (n2.y-n1.y)/(p2.y-p1.y)*(y_-p1.y);
					nz2 = n1.z + (n2.z-n1.z)/(p2.y-p1.y)*(y_-p1.y);
				}
			}
		}
		for (x_=(int(x1)==x1)?x1:int(x1)+1; x_<=x2; x_++) {
			z_ = z1 + (z2-z1)/(x2-x1)*(x_-x1);
			if (shading==2) {
				nz_ = nz1 + (nz2-nz1)/(x2-x1)*(x_-x1);
				nx_ = nx1 + (nx2-nx1)/(x2-x1)*(x_-x1);
				ny_ = ny1 + (ny2-ny1)/(x2-x1)*(x_-x1);
			}
			//cout << "nx_= " << nx_ << "\tny_= " << ny_ << "\tnz_=" << nz_ << endl;
			if (shading==2) c = lighting(vec3(nx_,ny_,nz_));
			framebuffer.draw(x_,y_,z_,c);
		}
		y_--;
	}
}

void drawTriangle(vec3* triVertices,vec3* triNormals,vec3 c)  //triVertices & triNormal must have 3 element
{
	//use insertion sort to sort 3 Vertices with Y order
	int vYSort[3];
	for (int i=0; i<3; i++)
		vYSort[i] = i;
	for (int i=1; i<3; i++) {
		int key = triVertices[vYSort[i]].y;
		int temp = vYSort[i];
		int j = i-1;
		while (j>=0 && triVertices[vYSort[j]].y>key) {
			vYSort[j+1] = vYSort[j];
			j--;
		}
		vYSort[j+1] = temp;
	}
	//cout << "vYSort = " << vYSort[2] << "\t" << vYSort[1] << "\t" << vYSort[0] << endl; 
	//cout << "p1:x= " << ix[vYSort[2]] << "\ty= " << iy[vYSort[2]] << "\tz= " << iz[vYSort[2]] << endl;
	//cout << "p2:x= " << ix[vYSort[1]] << "\ty= " << iy[vYSort[1]] << "\tz= " << iz[vYSort[1]] << endl;
	//cout << "p3:x= " << ix[vYSort[0]] << "\ty= " << iy[vYSort[0]] << "\tz= " << iz[vYSort[0]] << endl;
	//cout << "n1:x= " << triNormals[vYSort[2]].x << "\ty= " << triNormals[vYSort[2]].y << "\tz= " << triNormals[vYSort[2]].z << endl;
	//cout << "n2:x= " << triNormals[vYSort[1]].x << "\ty= " << triNormals[vYSort[1]].y << "\tz= " << triNormals[vYSort[1]].z << endl;
	//cout << "n3:x= " << triNormals[vYSort[0]].x << "\ty= " << triNormals[vYSort[0]].y << "\tz= " << triNormals[vYSort[0]].z << endl;
	if ((triVertices[vYSort[0]].y != triVertices[vYSort[1]].y) && 
		(triVertices[vYSort[1]].y != triVertices[vYSort[2]].y) && 
		(triVertices[vYSort[2]].y != triVertices[vYSort[0]].y)) {
		float temp_x = triVertices[vYSort[0]].x + (triVertices[vYSort[2]].x-triVertices[vYSort[0]].x) / 
					   (triVertices[vYSort[2]].y-triVertices[vYSort[0]].y) * (triVertices[vYSort[1]].y-triVertices[vYSort[0]].y);
		float temp_z = triVertices[vYSort[0]].z + (triVertices[vYSort[2]].z-triVertices[vYSort[0]].z) / 
					   (triVertices[vYSort[2]].y-triVertices[vYSort[0]].y) * (triVertices[vYSort[1]].y-triVertices[vYSort[0]].y);
		vec3 p1(triVertices[vYSort[2]].x,triVertices[vYSort[2]].y,triVertices[vYSort[2]].z);
		vec3 p2(triVertices[vYSort[1]].x,triVertices[vYSort[1]].y,triVertices[vYSort[1]].z);
		vec3 p3(temp_x,triVertices[vYSort[1]].y,temp_z);
		vec3 p4(triVertices[vYSort[0]].x,triVertices[vYSort[0]].y,triVertices[vYSort[0]].z);
		vec3 n1,n2,n3,n4;
		if (shading==2) {
			temp_x = triNormals[vYSort[0]].x + (triNormals[vYSort[2]].x-triNormals[vYSort[0]].x) / 
					 (triVertices[vYSort[2]].y-triVertices[vYSort[0]].y) * (triVertices[vYSort[1]].y-triVertices[vYSort[0]].y);
			float temp_y = triNormals[vYSort[0]].y + (triNormals[vYSort[2]].y-triNormals[vYSort[0]].y) / 
						   (triVertices[vYSort[2]].y-triVertices[vYSort[0]].y) * (triVertices[vYSort[1]].y-triVertices[vYSort[0]].y);
			temp_z = triNormals[vYSort[0]].z + (triNormals[vYSort[2]].z-triNormals[vYSort[0]].z) / 
					 (triVertices[vYSort[2]].y-triVertices[vYSort[0]].y) * (triVertices[vYSort[1]].y-triVertices[vYSort[0]].y);
			n1 = vec3(triNormals[vYSort[2]].x,triNormals[vYSort[2]].y,triNormals[vYSort[2]].z);
			n2 = vec3(triNormals[vYSort[1]].x,triNormals[vYSort[1]].y,triNormals[vYSort[1]].z);
			n3 = vec3(temp_x,temp_y,temp_z);
			n4 = vec3(triNormals[vYSort[0]].x,triNormals[vYSort[0]].y,triNormals[vYSort[0]].z);
		} else {
			n1 = n2 = n3 = n4 = vec3(0.f);
		}
		drawStandingTriangle(p1,p2,p3,n1,n2,n3,c);
		drawStandingTriangle(p2,p3,p4,n2,n3,n4,c);
	} else if ((triVertices[vYSort[0]].y==triVertices[vYSort[1]].y) && (triVertices[vYSort[1]].y==triVertices[vYSort[2]].y)) {
	} else {
		vec3 p1(triVertices[vYSort[2]].x,triVertices[vYSort[2]].y,triVertices[vYSort[2]].z);
		vec3 p2(triVertices[vYSort[1]].x,triVertices[vYSort[1]].y,triVertices[vYSort[1]].z);
		vec3 p3(triVertices[vYSort[0]].x,triVertices[vYSort[0]].y,triVertices[vYSort[0]].z);
		vec3 n1(triNormals[vYSort[2]].x,triNormals[vYSort[2]].y,triNormals[vYSort[2]].z);
		vec3 n2(triNormals[vYSort[1]].x,triNormals[vYSort[1]].y,triNormals[vYSort[1]].z);
		vec3 n3(triNormals[vYSort[0]].x,triNormals[vYSort[0]].y,triNormals[vYSort[0]].z);
		drawStandingTriangle(p1,p2,p3,n1,n2,n3,c);
	}
}

void drawEdge(int* ix,int* iy,float* iz,vec3 c)  //ix,iy,iz must have 3 element
{
	float m[3],B[3];
	for (int j=0; j<3; j++) {
		int k = j+1;
		if (k==3) k = 0;
		if (abs(iy[k]-iy[j]) <= abs(ix[k]-ix[j])) {	//use y=mx+B
			m[j] = float(iy[k]-iy[j])/float(ix[k]-ix[j]);
			B[j] = iy[j]-m[j]*ix[j];
			if (ix[j]<ix[k]) {
				for (int x_=ix[j]; x_<=ix[k]; x_++) {
					int y_ = x_*m[j]+B[j];
					float z_ = iz[j] + (iz[k]-iz[j])/(ix[k]-ix[j])*(x_-ix[j]);
					framebuffer.draw(x_,y_,z_,c);
				}
			} else {
				for (int x_=ix[k]; x_<=ix[j]; x_++) {
					int y_ = x_*m[j]+B[j];
					float z_ = iz[k] + (iz[j]-iz[k])/(ix[j]-ix[k])*(x_-ix[k]);
					framebuffer.draw(x_,y_,z_,c);
				}
			}
		} else {									//use x=my+B
			m[j] = float(ix[k]-ix[j])/float(iy[k]-iy[j]);
			B[j] = ix[j]-m[j]*iy[j];
			if (iy[j]<iy[k]) {
				for (int y_=iy[j]; y_<=iy[k]; y_++) {
					int x_ = y_*m[j]+B[j];
					float z_ = iz[j] + (iz[k]-iz[j])/(iy[k]-iy[j])*(y_-iy[j]);
					framebuffer.draw(x_,y_,z_,c);
				}
			} else {
				for (int y_=iy[k]; y_<=iy[j]; y_++) {
					int x_ = y_*m[j]+B[j];
					float z_ = iz[k] + (iz[j]-iz[k])/(iy[j]-iy[k])*(y_-iy[k]);
					framebuffer.draw(x_,y_,z_,c);
				}
			}
		}
	}
}

void displayFunc() 
{
	framebuffer.clear();

	/* draw point cloud */
	/* TODO: change the following code to do rasterization */
	//int ix, iy;
	//int screenSide = min(screenWidth, screenHeight);
	//float margin = 0.1f;
	//float prevX, prevY, prevZ, curX, curY, curZ;
	//cout << modelPtr[curModelIdx]->numVertices << endl;
	/*for(int i = 1; i <= modelPtr[curModelIdx]->numVertices; ++i) {       //drawing vertices
		prevX = modelPtr[curModelIdx]->vertices[3*i  ];
		prevY = modelPtr[curModelIdx]->vertices[3*i+1];
		prevZ = modelPtr[curModelIdx]->vertices[3*i+2];

		// rotate along x-axis
		curY = prevY*cos(thetaX)-prevZ*sin(thetaX);
		curZ = prevY*sin(thetaX)+prevZ*cos(thetaX);
		// prevY = curY;
		prevZ = curZ;
		// rotate along y-axis
		curX = prevZ*sin(thetaY)+prevX*cos(thetaY);
		curZ = prevZ*cos(thetaY)-prevX*sin(thetaY);
		// draw the framebuffer
		ix = int(((1.f-margin)*curX)*screenSide) + screenWidth_half - 1;
		iy = int(((1.f-margin)*curY)*screenSide) + screenHeight_half - 1;
		cout << "ix = " << ix << endl;
		cout << "iy = " << iy << endl;
		cout << "iz = " << curZ << endl;
		framebuffer.draw(ix, iy, curZ, vec3(1.f));
	}*/
	for (int i=0; i<modelPtr[curModelIdx]->numTriangles; i++) {
		Triangle* triangle = modelPtr[curModelIdx]->triangles;
		float* vertice = modelPtr[curModelIdx]->vertices;
		float* normal = modelPtr[curModelIdx]->normals;
		vec3 triVertices[3];
		vec3 triNormals[3];
		for (int j=0; j<3; j++) {
			triVertices[j].x = vertice[3*(triangle[i].vIndices[j])  ];
			triVertices[j].y = vertice[3*(triangle[i].vIndices[j])+1];
			triVertices[j].z = vertice[3*(triangle[i].vIndices[j])+2];
			if (shading==2) {
				triNormals[j].x = normal[3*(triangle[i].vIndices[j])  ];
				triNormals[j].y = normal[3*(triangle[i].vIndices[j])+1];
				triNormals[j].z = normal[3*(triangle[i].vIndices[j])+2];
			} else {
				triNormals[j].x = 0;
				triNormals[j].y = 0;
				triNormals[j].z = 0;
			}
		}
		//cout << "n1:x= " << triNormals[0].x << "\ty= " << triNormals[0].y << "\tz= " << triNormals[0].z << endl;
		//cout << "n2:x= " << triNormals[1].x << "\ty= " << triNormals[1].y << "\tz= " << triNormals[1].z << endl;
		//cout << "n3:x= " << triNormals[2].x << "\ty= " << triNormals[2].y << "\tz= " << triNormals[2].z << endl;
		//Transform
		triVertices[0] = transform(triVertices[0]);
		triVertices[1] = transform(triVertices[1]);
		triVertices[2] = transform(triVertices[2]);
		if (shading==2) {
			triNormals[0] = transform(triNormals[0]);
			triNormals[1] = transform(triNormals[1]);
			triNormals[2] = transform(triNormals[2]);
		}
		/*int ix[3],iy[3];
		float iz[3];
		toScreenSpace(triVertices[0],ix[0],iy[0],iz[0]);
		toScreenSpace(triVertices[1],ix[1],iy[1],iz[1]);
		toScreenSpace(triVertices[2],ix[2],iy[2],iz[2]);
		drawTriangle(ix,iy,iz);
		drawEdge(ix,iy,iz,vec3(1.f,0.f,0.f));*/
		//Back Face Culling
		if (!backFaceCulling(triVertices) || !culling || wireframe_filled==0) {
			int ix[3],iy[3];
			float iz[3];
			vec3 c;
			if (shading==1) {
				vec3 v1(triVertices[0].x-triVertices[1].x,triVertices[0].y-triVertices[1].y,triVertices[0].z-triVertices[1].z);
				vec3 v2(triVertices[0].x-triVertices[2].x,triVertices[0].y-triVertices[2].y,triVertices[0].z-triVertices[2].z);
				vec3 normal = crossProduct(v1,v2);
				c = lighting(normal);
			} else c = color;
			toScreenSpace(triVertices[0],ix[0],iy[0],iz[0]);
			toScreenSpace(triVertices[1],ix[1],iy[1],iz[1]);
			toScreenSpace(triVertices[2],ix[2],iy[2],iz[2]);
			triVertices[0] = vec3(ix[0],iy[0],iz[0]);
			triVertices[1] = vec3(ix[1],iy[1],iz[1]);
			triVertices[2] = vec3(ix[2],iy[2],iz[2]);
			//drawTriangle(ix,iy,iz,c);
			if (wireframe_filled==1) drawTriangle(triVertices,triNormals,c);
			else drawEdge(ix,iy,iz,vec3(1.f,0.f,0.f));
		}
		//for Debug purpose (will draw back face culling wireframe)
		/*else {
			int ix[3],iy[3];
			float iz[3];
			toScreenSpace(triVertices[0],ix[0],iy[0],iz[0]);
			toScreenSpace(triVertices[1],ix[1],iy[1],iz[1]);
			toScreenSpace(triVertices[2],ix[2],iy[2],iz[2]);
			//drawTriangle(ix,iy,iz);
			if (wireframe_filled==1) drawEdge(ix,iy,iz,vec3(0.f,0.f,0.5f));
		}*/
	}


    /* display */
	glDrawPixels(screenWidth, screenHeight, GL_RGB, GL_FLOAT, (const GLvoid*)framebuffer.getPixels());
	glutSwapBuffers();

	/* FPS counter */
	static clock_t prev = clock();
	static clock_t curr;
	static char title[20];
	static double refreshTime = 0.5;
	static int count = 0;
	++count;
	curr = clock();
	double t = (double)(curr - prev)/(double)CLOCKS_PER_SEC;
	
	if (t > refreshTime) {
		//cout << "curr = " << curr << "\tprev = " << prev <<  "\tt = " << t << endl;
		//cout << "fps = " << 
		sprintf(title, "3DMM HW#1 Rasterization: %.2lf fps",  (double)count/t);
		glutSetWindowTitle(title);
		prev = curr;
		count = 0;
	}
}


void idleFunc() 
{
	glutPostRedisplay();
}

void keyboardFunc(unsigned char key, int x, int y) 
{
	switch (key) {
	// Quit
	case 'q':
	case 'Q':
		exit(0);
		break;
	// Help
	case 'h':
	case 'H':
		printHelp();
		break;
	// Save image
	case 's':
	case 'S':
		static time_t t;
		static char name[80];
		time(&t);
		strftime(name, sizeof(name), "%Y%m%d%H%M%S.ppm", localtime(&t));
		printf("Save framebuffer to %s\n", name);
		framebuffer.writePPM(name);
		break;
	// Select model
	case 'm':
		curModelIdx = (curModelIdx == numModels - 1)? 0 : (curModelIdx + 1);
		printf("Switch to model \"%s\"\n", modelNames[curModelIdx]);
		break;
	case 'M':
		curModelIdx = (curModelIdx == 0)? (numModels - 1) : (curModelIdx - 1);
		printf("Switch to model \"%s\"\n", modelNames[curModelIdx]);
		break;
	// Back-face culling
	case 'c':
	case 'C':
		culling = !culling;
		break;
	//Shading Mode
	case 'l':
	case 'L':
		if (shading == 2) shading = 0;
		else shading++;
		break;
	//Wireframe Mode
	case 'w':
	case 'W':
		if (wireframe_filled == 1) wireframe_filled = 0;
		else wireframe_filled++;
		break;
	// Background color
	case 'b':
	case 'B':
		static bool isBlack = true;
		isBlack = !isBlack;
		framebuffer.setClearColor(isBlack? vec3(0.f) : vec3(1.f));
		break;

	// You can add more functions as you like.
	}
	glutPostRedisplay();
}

// Special keys
void specialFunc(int key, int x, int y) 
{
	switch (key) {
	case GLUT_KEY_RIGHT:
		thetaY = (thetaY > PI*2)? 0 : (thetaY + rotateSpeed);
		break;
	case GLUT_KEY_LEFT:
		thetaY = (thetaY < 0)? (PI*2) : (thetaY - rotateSpeed);
		break;
	case GLUT_KEY_UP:
		thetaX = (thetaX < 0)? (PI*2) : (thetaX - rotateSpeed);
		break;
	case GLUT_KEY_DOWN:
		thetaX = (thetaX > PI*2)? 0 : (thetaX + rotateSpeed);
		break;
	case GLUT_KEY_PAGE_UP:
    
		break;
	case GLUT_KEY_PAGE_DOWN:
    
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(screenWidth, screenHeight);
	glutCreateWindow("3DMM HW#1 Rasterization");

	init();

	glutDisplayFunc(displayFunc);
	glutIdleFunc(idleFunc);
	// glutMouseFunc(mouseFunc);
	glutKeyboardFunc(keyboardFunc);
	glutSpecialFunc(specialFunc);

	glutMainLoop();
	
	for(int i = 0; i < numModels; ++i) {
		if(modelPtr[i]) delete [] modelPtr[i];
	}
	if(modelPtr) delete [] modelPtr;

	return 0;
}