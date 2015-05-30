#include "rasterize.h"
#include <iostream>
using namespace std;

void drawStandingTriangle(const vec3& p1,const vec3& p2,const vec3& p3,
						  const vec3& n1,const vec3& n2,const vec3& n3,vec3 c) //p1.y >= p2.y >= p3.y
{
	int x_,y_=p1.y;
	float x1,x2,z1,z2;
	float z_;
	float nx_,ny_,nz_,nx1,nx2,ny1,ny2,nz1,nz2;
	while (y_ >= p3.y) {
		if (p1.y == p2.y) {
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
			if (shading==2) c = lighting(glm::vec3(nx_,ny_,nz_));
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