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
		float key = triVertices[vYSort[i]].y;
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

void drawLine(const glm::vec3& p1,const glm::vec3& p2,const vec3& c)
{
	float m,B;
	//for (int j=0; j<3; j++) {
		//int k = j+1;
		//if (k==3) k = 0;
		if (abs(p2.y-p1.y) <= abs(p2.x-p1.x)) {	//use y=mx+B
			m = float(p2.y-p1.y)/float(p2.x-p1.x);
			B = p1.y - m * p1.x;
			if (p1.x<p2.x) {
				for (int x_=p1.x; x_<=p2.x; x_++) {
					int y_ = x_*m+B;
					float z_ = p1.z + (p2.z-p1.z)/(p2.x-p1.x)*(x_-p1.x);
					framebuffer.draw(x_,y_,z_,c);
				}
			} else {
				for (int x_=p2.x; x_<=p1.x; x_++) {
					int y_ = x_*m+B;
					float z_ = p2.z + (p1.z-p2.z)/(p1.x-p2.x)*(x_-p2.x);
					framebuffer.draw(x_,y_,z_,c);
				}
			}
		} else {									//use x=my+B
			m = float(p2.x-p1.x)/float(p2.y-p1.y);
			B = p1.x-m*p1.y;
			if (p1.y<p2.y) {
				for (int y_=p1.y; y_<=p2.y; y_++) {
					int x_ = y_*m+B;
					float z_ = p1.z + (p2.z-p1.z)/(p2.y-p1.y)*(y_-p1.y);
					framebuffer.draw(x_,y_,z_,c);
				}
			} else {
				for (int y_=p2.y; y_<=p1.y; y_++) {
					int x_ = y_*m+B;
					float z_ = p2.z + (p1.z-p2.z)/(p1.y-p2.y)*(y_-p2.y);
					framebuffer.draw(x_,y_,z_,c);
				}
			}
		}
	//}
}

void rasterStandingTriangle(Primitive MVP_vertex,vector<Primitive>& v_MV_value,vec3 c)
{
	//Primitive MV_value(v_MV_value[i]);
	glm::vec3 p1 = MVP_vertex[0];
	glm::vec3 p2 = MVP_vertex[1];
	glm::vec3 p3 = MVP_vertex[2];
	//glm::vec3 n1 = MV_value[0];
	int x_,y_=p1.y;
	//float x1,x2,z1,z2;
	float z_;
	float nx_,ny_,nz_;
	/*vector<float> nx1(v_MV_value.size());
	vector<float> nx2(v_MV_value.size());
	vector<float> ny1(v_MV_value.size());
	vector<float> ny2(v_MV_value.size());
	vector<float> nz1(v_MV_value.size());
	vector<float> nz2(v_MV_value.size());*/
	glm::vec3 n_;
	glm::vec3 p_left;
	glm::vec3 p_right;
	vector<glm::vec3> n_left(v_MV_value.size());
	vector<glm::vec3> n_right(v_MV_value.size());
	vector<glm::vec3*> result_vertex;
	vector<glm::vec3*> result_value;
	while (y_ >= p3.y) {
		c = vec3(1.f,1.f,1.f);
		if (p1.y == p2.y) {
			if (p1.x<p2.x) {
				//int idx[3] = {0,1,2};
				/*if (p2.x <= p1.x) {
					idx[0] = 1;
					idx[1] = 0;
					c = vec3(1.f,0.f,0.f);
				}
				p1 = MVP_vertex[idx[0]];
				p2 = MVP_vertex[idx[1]];*/
				float b1 = y_-p3.y, b2 = y_-p3.y;
				float a1 = p1.y-p3.y-b1, a2 = p2.y-p3.y-b2;
				p_left.x = b1/(a1+b1)*p1.x + a1/(a1+b1)*p3.x;
				p_left.y = y_;
				p_left.z = b1/(a1+b1)*p1.z + a1/(a1+b1)*p3.z;
				p_right.x = b2/(a2+b2)*p2.x + a2/(a2+b2)*p3.x;
				p_right.y = y_;
				p_right.z = b2/(a2+b2)*p2.z + a2/(a2+b2)*p3.z;
				//x1 = p1.x + (p3.x-p1.x)/(p3.y-p1.y)*(y_-p1.y);
				//z1 = p1.z + (p3.z-p1.z)/(p3.y-p1.y)*(y_-p1.y);
				//x2 = p2.x + (p3.x-p2.x)/(p3.y-p2.y)*(y_-p2.y);
				//z2 = p2.z + (p3.z-p2.z)/(p3.y-p2.y)*(y_-p2.y);
				for (size_t i=0; i<v_MV_value.size(); i++) {
					Primitive MV_value(v_MV_value[i]);
					glm::vec3 n1 = MV_value[0];
					glm::vec3 n2 = MV_value[1];
					glm::vec3 n3 = MV_value[2];
					if (projection==0) {
						n_left[i] = b1/(a1+b1)*n1 + a1/(a1+b1)*n3;
						n_right[i] = b2/(a2+b2)*n2 + a2/(a2+b2)*n3;
						//nx1[i] = n1.x + (n3.x-n1.x)/(p3.y-p1.y)*(y_-p1.y);
						//ny1[i] = n1.y + (n3.y-n1.y)/(p3.y-p1.y)*(y_-p1.y);
						//nz1[i] = n1.z + (n3.z-n1.z)/(p3.y-p1.y)*(y_-p1.y);
						//nx2[i] = n2.x + (n3.x-n2.x)/(p3.y-p2.y)*(y_-p2.y);
						//ny2[i] = n2.y + (n3.y-n2.y)/(p3.y-p2.y)*(y_-p2.y);
						//nz2[i] = n2.z + (n3.z-n2.z)/(p3.y-p2.y)*(y_-p2.y);
					} else {
						n_left[i].z = 1 / (b1/(a1+b1)*(1/n1.z) + a1/(a1+b1)*(1/n3.z));
						n_left[i].x = (b1/(a1+b1)*(n1.x/n1.z) + a1/(a1+b1)*(n3.x/n3.z)) * n_left[i].z;
						n_left[i].y = (b1/(a1+b1)*(n1.y/n1.z) + a1/(a1+b1)*(n3.y/n3.z)) * n_left[i].z;
						n_right[i].z = 1 / (b2/(a2+b2)*(1/n2.z) + a2/(a2+b2)*(1/n3.z));
						n_right[i].x = (b2/(a2+b2)*(n2.x/n2.z) + a2/(a2+b2)*(n3.x/n3.z)) * n_right[i].z;
						n_right[i].y = (b2/(a2+b2)*(n2.y/n2.z) + a2/(a2+b2)*(n3.y/n3.z)) * n_right[i].z;
					}
				}
			} else {
				c=vec3(0.f,1.f,0.f);
				int idx[3] = {0,1,2};
				float b1 = y_-p3.y, b2 = y_-p3.y;
				float a1 = p2.y-p3.y-b1, a2 = p1.y-p3.y-b2;
				p_left.x = b1/(a1+b1)*p2.x + a1/(a1+b1)*p3.x;
				p_left.y = y_;
				p_left.z = b1/(a1+b1)*p2.z + a1/(a1+b1)*p3.z;
				p_right.x = b2/(a2+b2)*p1.x + a2/(a2+b2)*p3.x;
				p_right.y = y_;
				p_right.z = b2/(a2+b2)*p1.z + a2/(a2+b2)*p3.z;
				//x1 = p2.x + (p3.x-p2.x)/(p3.y-p2.y)*(y_-p2.y);
				//z1 = p2.z + (p3.z-p2.z)/(p3.y-p2.y)*(y_-p2.y);
				//x2 = p1.x + (p3.x-p1.x)/(p3.y-p1.y)*(y_-p1.y);
				//z2 = p1.z + (p3.z-p1.z)/(p3.y-p1.y)*(y_-p1.y);
				for (size_t i=0; i<v_MV_value.size(); i++) {
					Primitive MV_value(v_MV_value[i]);
					glm::vec3 n1 = MV_value[0];
					glm::vec3 n2 = MV_value[1];
					glm::vec3 n3 = MV_value[2];
					if (projection==0) {
						n_right[i] = b1/(a1+b1)*n1 + a1/(a1+b1)*n3;
						n_left[i] = b2/(a2+b2)*n2 + a2/(a2+b2)*n3;
						//nx2[i] = n1.x + (n3.x-n1.x)/(p3.y-p1.y)*(y_-p1.y);
						//ny2[i] = n1.y + (n3.y-n1.y)/(p3.y-p1.y)*(y_-p1.y);
						//nz2[i] = n1.z + (n3.z-n1.z)/(p3.y-p1.y)*(y_-p1.y);
						//nx1[i] = n2.x + (n3.x-n2.x)/(p3.y-p2.y)*(y_-p2.y);
						//ny1[i] = n2.y + (n3.y-n2.y)/(p3.y-p2.y)*(y_-p2.y);
						//nz1[i] = n2.z + (n3.z-n2.z)/(p3.y-p2.y)*(y_-p2.y);
					} else {
						n_right[i].z = 1 / (b1/(a1+b1)*(1/n1.z) + a1/(a1+b1)*(1/n3.z));
						n_right[i].x = (b1/(a1+b1)*(n1.x/n1.z) + a1/(a1+b1)*(n3.x/n3.z)) * n_right[i].z;
						n_right[i].y = (b1/(a1+b1)*(n1.y/n1.z) + a1/(a1+b1)*(n3.y/n3.z)) * n_right[i].z;
						n_left[i].z = 1 / (b2/(a2+b2)*(1/n2.z) + a2/(a2+b2)*(1/n3.z));
						n_left[i].x = (b2/(a2+b2)*(n2.x/n2.z) + a2/(a2+b2)*(n3.x/n3.z)) * n_left[i].z;
						n_left[i].y = (b2/(a2+b2)*(n2.y/n2.z) + a2/(a2+b2)*(n3.y/n3.z)) * n_left[i].z;
					}
				}
			}
		} else if (p2.y == p3.y){
			if (p2.x<p3.x) {
				/*int idx[3] = {0,1,2};
				if (p3.x < p2.x) {
					idx[1] = 2;
					idx[2] = 1;

					c = vec3(1.f,0.f,0.f);
				}
				p2 = MVP_vertex[idx[1]];
				p3 = MVP_vertex[idx[2]];*/
				float b1 = y_-p2.y, b2 = y_-p3.y;
				float a1 = p1.y-p2.y-b1, a2 = p1.y-p3.y-b2;
				//glm::vec3 p1to2,p1to3;
				p_left.x = b1/(a1+b1)*p1.x + a1/(a1+b1)*p2.x;
				p_left.y = y_;
				p_left.z = b1/(a1+b1)*p1.z + a1/(a1+b1)*p2.z;
				p_right.x = b2/(a2+b2)*p1.x + a2/(a2+b2)*p3.x;
				p_right.y = y_;
				p_right.z = b2/(a2+b2)*p1.z + a2/(a2+b2)*p3.z; 
				//x1 = p1.x + (p2.x-p1.x)/(p2.y-p1.y)*(y_-p1.y);
				//z1 = p1.z + (p2.z-p1.z)/(p2.y-p1.y)*(y_-p1.y);
				//x2 = p1.x + (p3.x-p1.x)/(p3.y-p1.y)*(y_-p1.y);
				//z2 = p1.z + (p3.z-p1.z)/(p3.y-p1.y)*(y_-p1.y);
				for (size_t i=0; i<v_MV_value.size(); i++) {
					Primitive MV_value(v_MV_value[i]);
					glm::vec3 n1 = MV_value[0];
					glm::vec3 n2 = MV_value[1];
					glm::vec3 n3 = MV_value[2];
					if (projection==0) {
						n_left[i] = b1/(a1+b1)*n1 + a1/(a1+b1)*n2;
						n_right[i] = b2/(a2+b2)*n1 + a2/(a2+b2)*n3;
						//nx1[i] = n1.x + (n2.x-n1.x)/(p2.y-p1.y)*(y_-p1.y);
						//ny1[i] = n1.y + (n2.y-n1.y)/(p2.y-p1.y)*(y_-p1.y);
						//nz1[i] = n1.z + (n2.z-n1.z)/(p2.y-p1.y)*(y_-p1.y);
						//nx2[i] = n1.x + (n3.x-n1.x)/(p3.y-p1.y)*(y_-p1.y);
						//ny2[i] = n1.y + (n3.y-n1.y)/(p3.y-p1.y)*(y_-p1.y);
						//nz2[i] = n1.z + (n3.z-n1.z)/(p3.y-p1.y)*(y_-p1.y);
					} else {
						n_left[i].z = 1 / (b1/(a1+b1)*(1/n1.z) + a1/(a1+b1)*(1/n2.z));
						n_left[i].x = (b1/(a1+b1)*(n1.x/n1.z) + a1/(a1+b1)*(n2.x/n2.z)) * n_left[i].z;
						n_left[i].y = (b1/(a1+b1)*(n1.y/n1.z) + a1/(a1+b1)*(n2.y/n2.z)) * n_left[i].z;
						n_right[i].z = 1 / (b2/(a2+b2)*(1/n1.z) + a2/(a2+b2)*(1/n3.z));
						n_right[i].x = (b2/(a2+b2)*(n1.x/n1.z) + a2/(a2+b2)*(n3.x/n3.z)) * n_right[i].z;
						n_right[i].y = (b2/(a2+b2)*(n1.y/n1.z) + a2/(a2+b2)*(n3.y/n3.z)) * n_right[i].z;
					}
				}
			} else {
				float b1 = y_-p2.y, b2 = y_-p3.y;
				float a1 = p1.y-p2.y-b1, a2 = p1.y-p3.y-b2;
				//glm::vec3 p1to2,p1to3;
				p_right.x = b1/(a1+b1)*p1.x + a1/(a1+b1)*p2.x;
				p_right.y = y_;
				p_right.z = b1/(a1+b1)*p1.z + a1/(a1+b1)*p2.z;
				p_left.x = b2/(a2+b2)*p1.x + a2/(a2+b2)*p3.x;
				p_left.y = y_;
				p_left.z = b2/(a2+b2)*p1.z + a2/(a2+b2)*p3.z; 
				//x1 = p1.x + (p3.x-p1.x)/(p3.y-p1.y)*(y_-p1.y);
				//z1 = p1.z + (p3.z-p1.z)/(p3.y-p1.y)*(y_-p1.y);
				//x2 = p1.x + (p2.x-p1.x)/(p2.y-p1.y)*(y_-p1.y);
				//z2 = p1.z + (p2.z-p1.z)/(p2.y-p1.y)*(y_-p1.y);
				for (size_t i=0; i<v_MV_value.size(); i++) {
					Primitive MV_value(v_MV_value[i]);
					glm::vec3 n1 = MV_value[0];
					glm::vec3 n2 = MV_value[1];
					glm::vec3 n3 = MV_value[2];
					if (projection==0) {
						n_right[i] = b1/(a1+b1)*n1 + a1/(a1+b1)*n3;
						n_left[i] = b2/(a2+b2)*n2 + a2/(a2+b2)*n3;
						//nx1[i] = n1.x + (n3.x-n1.x)/(p3.y-p1.y)*(y_-p1.y);
						//ny1[i] = n1.y + (n3.y-n1.y)/(p3.y-p1.y)*(y_-p1.y);
						//nz1[i] = n1.z + (n3.z-n1.z)/(p3.y-p1.y)*(y_-p1.y);
						//nx2[i] = n1.x + (n2.x-n1.x)/(p2.y-p1.y)*(y_-p1.y);
						//ny2[i] = n1.y + (n2.y-n1.y)/(p2.y-p1.y)*(y_-p1.y);
						//nz2[i] = n1.z + (n2.z-n1.z)/(p2.y-p1.y)*(y_-p1.y);
					} else {
						n_right[i].z = 1 / (b1/(a1+b1)*(1/n1.z) + a1/(a1+b1)*(1/n2.z));
						n_right[i].x = (b1/(a1+b1)*(n1.x/n1.z) + a1/(a1+b1)*(n2.x/n2.z)) * n_right[i].z;
						n_right[i].y = (b1/(a1+b1)*(n1.y/n1.z) + a1/(a1+b1)*(n2.y/n2.z)) * n_right[i].z;
						n_left[i].z = 1 / (b2/(a2+b2)*(1/n1.z) + a2/(a2+b2)*(1/n3.z));
						n_left[i].x = (b2/(a2+b2)*(n1.x/n1.z) + a2/(a2+b2)*(n3.x/n3.z)) * n_left[i].z;
						n_left[i].y = (b2/(a2+b2)*(n1.y/n1.z) + a2/(a2+b2)*(n3.y/n3.z)) * n_left[i].z;
					}
				}
			}
		}
		for (x_=(int(p_left.x)==p_left.x)?p_left.x:int(p_left.x)+1; x_<=p_right.x; x_++) {
			z_ = p_left.z + (p_right.z-p_left.z)/(p_right.x-p_left.x)*(x_-p_left.x);
			//Primitive result = new glm::vec3[v_MV_value.size()];
			float a = (x_-p_left.x);
			float b = (p_right.x-p_left.x)-b;
			for (size_t i=0; i<v_MV_value.size(); i++) {
				if (projection==0) {
					n_.z = b/(a+b)*n_left[i].z + a/(a+b)*n_right[i].z;
					n_.x = b/(a+b)*n_left[i].x + a/(a+b)*n_right[i].x;
					n_.y = b/(a+b)*n_left[i].y + a/(a+b)*n_right[i].y;
					//nz_ = nz1[i] + (nz2[i]-nz1[i])/(x2-x1)*(x_-x1);
					//nx_ = nx1[i] + (nx2[i]-nx1[i])/(x2-x1)*(x_-x1);
					//ny_ = ny1[i] + (ny2[i]-ny1[i])/(x2-x1)*(x_-x1);
					//result[i] = glm::vec3(nx_,ny_,nz_);
				} else {
					n_.z = b/(a+b)*(1/n_left[i].z) + a/(a+b)*(1/n_right[i].z);
					n_.x = (b/(a+b)*(n_left[i].x/n_left[i].z) + a/(a+b)*(n_right[i].x/n_right[i].z)) * n_.z;
					n_.y = (b/(a+b)*(n_left[i].y/n_left[i].z) + a/(a+b)*(n_right[i].y/n_right[i].z)) * n_.z;
				}
			}
			//result_vertex.push_back(new glm::vec3(x_,y_,z_));
			//result_value.push_back(result);
			if (shading==2) c = lighting(vec3(n_.x,n_.y,n_.z));
			framebuffer.draw(x_,y_,z_,c);
		}
	
		y_--;
	}
}

void rasterTriangle(Primitive MVP_vertex,vector<Primitive>& v_MV_value,vec3 c) 
{
	//use insertion sort to sort 3 Vertices in w_vert with Y order
	int vYSort[3];
	for (int i=0; i<3; i++)
		vYSort[i] = i;
	for (int i=1; i<3; i++) {
		float key = MVP_vertex[vYSort[i]].y;
		int temp = vYSort[i];
		int j = i-1;
		while (j>=0 && MVP_vertex[vYSort[j]].y>key) {
			vYSort[j+1] = vYSort[j];
			j--;
		}
		vYSort[j+1] = temp;
	}
	//now MVP_vertex[vYSort[0]].y <= MVP_vertex[vYSort[1]].y <= MVP_vertex[vYSort[2]].y

	glm::vec3 temp;
	float temp_x,temp_y,temp_z,a,b;
	if ((MVP_vertex[vYSort[0]].y != MVP_vertex[vYSort[1]].y) && 
		(MVP_vertex[vYSort[1]].y != MVP_vertex[vYSort[2]].y) && 
		(MVP_vertex[vYSort[2]].y != MVP_vertex[vYSort[0]].y)) {
		//interpolating the 4th point on the triangle(same y as point No. 2)

		b = MVP_vertex[vYSort[1]].y-MVP_vertex[vYSort[0]].y;
		a = MVP_vertex[vYSort[2]].y-MVP_vertex[vYSort[0]].y - b;
		temp = b / (a+b) * MVP_vertex[vYSort[2]] + a / (a+b) * MVP_vertex[vYSort[0]];
		/*temp_x = //b / (a+b) * MVP_vertex[vYSort[0]].x + a / (a+b) * MVP_vertex[vYSort[2]].x;
				 MVP_vertex[vYSort[0]].x + (MVP_vertex[vYSort[2]].x-MVP_vertex[vYSort[0]].x) / 
			     (MVP_vertex[vYSort[2]].y-MVP_vertex[vYSort[0]].y) * (MVP_vertex[vYSort[1]].y-MVP_vertex[vYSort[0]].y);
		temp_z = //b / (a+b) * MVP_vertex[vYSort[0]].z + a / (a+b) * MVP_vertex[vYSort[2]].z;
				 MVP_vertex[vYSort[0]].z + (MVP_vertex[vYSort[2]].z-MVP_vertex[vYSort[0]].z) / 
			     (MVP_vertex[vYSort[2]].y-MVP_vertex[vYSort[0]].y) * (MVP_vertex[vYSort[1]].y-MVP_vertex[vYSort[0]].y);*/
		//glm::vec3 s_MVP_v1(MVP_vertex[vYSort[2]].x,MVP_vertex[vYSort[2]].y,MVP_vertex[vYSort[2]].z);
		//glm::vec3 s_MVP_v2(MVP_vertex[vYSort[1]].x,MVP_vertex[vYSort[1]].y,MVP_vertex[vYSort[1]].z);
		//glm::vec3 s_MVP_v3(temp.x,MVP_vertex[vYSort[1]].y,temp.z);
		//glm::vec3 s_MVP_v4(MVP_vertex[vYSort[0]].x,MVP_vertex[vYSort[0]].y,MVP_vertex[vYSort[0]].z);
		Primitive s1_MVP_vertex = new glm::vec3[3];
		s1_MVP_vertex[0] = glm::vec3(MVP_vertex[vYSort[2]]);
		s1_MVP_vertex[1] = glm::vec3(MVP_vertex[vYSort[1]]);
		s1_MVP_vertex[2] = glm::vec3(temp.x,MVP_vertex[vYSort[1]].y,temp.z);
		Primitive s2_MVP_vertex = new glm::vec3[3];
		s2_MVP_vertex[0] = glm::vec3(MVP_vertex[vYSort[1]]);
		s2_MVP_vertex[1] = glm::vec3(temp.x,MVP_vertex[vYSort[1]].y,temp.z);
		s2_MVP_vertex[2] = glm::vec3(MVP_vertex[vYSort[0]]);

		//interpolating for MV_value
		vector<Primitive> s1_v_MV_value,s2_v_MV_value; //v_MV_value for standing triangle 1&2
		//glm::vec3 s_MV_v1,s_MV_v2,s_MV_v3,s_MV_v4;
		if (projection==0) {
			for (size_t i=0; i<v_MV_value.size(); i++) {
				Primitive MV_value(v_MV_value[i]);
				b = MVP_vertex[vYSort[1]].y-MVP_vertex[vYSort[0]].y;
				a = MVP_vertex[vYSort[2]].y-MVP_vertex[vYSort[0]].y - b;
				temp = b / (a+b) * MV_value[vYSort[2]] + a / (a+b) * MV_value[vYSort[0]];
				//temp_x = b / (a+b) * MV_value[vYSort[2]].x + a / (a+b) * MV_value[vYSort[0]].x;
				//temp_y = b / (a+b) * MV_value[vYSort[2]].y + a / (a+b) * MV_value[vYSort[0]].y;
				//temp_z = b / (a+b) * MV_value[vYSort[2]].z + a / (a+b) * MV_value[vYSort[0]].z;
				/*temp_x = MV_value[vYSort[0]].x + (MV_value[vYSort[2]].x-MV_value[vYSort[0]].x) / 
						 (MVP_vertex[vYSort[2]].y-MVP_vertex[vYSort[0]].y) * (MVP_vertex[vYSort[1]].y-MVP_vertex[vYSort[0]].y);
				temp_y = MV_value[vYSort[0]].y + (MV_value[vYSort[2]].y-MV_value[vYSort[0]].y) / 
						 (MVP_vertex[vYSort[2]].y-MVP_vertex[vYSort[0]].y) * (MVP_vertex[vYSort[1]].y-MVP_vertex[vYSort[0]].y);
				temp_z = MV_value[vYSort[0]].z + (MV_value[vYSort[2]].z-MV_value[vYSort[0]].z) / 
						 (MVP_vertex[vYSort[2]].y-MVP_vertex[vYSort[0]].y) * (MVP_vertex[vYSort[1]].y-MVP_vertex[vYSort[0]].y);*/
				//glm::vec3 s_MV_v1(MV_value[vYSort[2]].x,MV_value[vYSort[2]].y,MV_value[vYSort[2]].z);
				//glm::vec3 s_MV_v2(MV_value[vYSort[1]].x,MV_value[vYSort[1]].y,MV_value[vYSort[1]].z);
				//glm::vec3 s_MV_v3(temp);
				//glm::vec3 s_MV_v4(MV_value[vYSort[0]].x,MV_value[vYSort[0]].y,MV_value[vYSort[0]].z);
				Primitive s1 = new glm::vec3[3];
				s1[0] = glm::vec3(MV_value[vYSort[2]]);
				s1[1] = glm::vec3(MV_value[vYSort[1]]);
				s1[2] = glm::vec3(temp);
				Primitive s2 = new glm::vec3[3];
				s2[0] = glm::vec3(MV_value[vYSort[1]]);
				s2[1] = glm::vec3(temp);
				s2[2] = glm::vec3(MV_value[vYSort[0]]);
				s1_v_MV_value.push_back(s1);
				s2_v_MV_value.push_back(s2);
			}
		} else {
			for (size_t i=0; i<v_MV_value.size(); i++) {
				Primitive MV_value(v_MV_value[i]);
				b = MVP_vertex[vYSort[1]].y-MVP_vertex[vYSort[0]].y;
				a = MVP_vertex[vYSort[2]].y-MVP_vertex[vYSort[0]].y - b;
				temp.z = 1 / (b/(a+b)*(1/MV_value[vYSort[2]].z) + a/(a+b)*(1/MV_value[vYSort[0]].z));
				temp.x = (b/(a+b)*(MV_value[vYSort[2]].x/MV_value[vYSort[2]].z) + a/(a+b)*(MV_value[vYSort[0]].x/MV_value[vYSort[0]].z))
							* temp.z;
				temp.y = (b/(a+b)*(MV_value[vYSort[2]].y/MV_value[vYSort[2]].y) + a/(a+b)*(MV_value[vYSort[0]].y/MV_value[vYSort[0]].y))
							* temp.z;
				//temp = b / (a+b) * MV_value[vYSort[2]] + a / (a+b) * MV_value[vYSort[0]];
				//temp_x = MV_value[vYSort[0]].x + (MV_value[vYSort[2]].x-MV_value[vYSort[0]].x) / 
				//		 (MVP_vertex[vYSort[2]].y-MVP_vertex[vYSort[0]].y) * (MVP_vertex[vYSort[1]].y-MVP_vertex[vYSort[0]].y);
				//temp_y = MV_value[vYSort[0]].y + (MV_value[vYSort[2]].y-MV_value[vYSort[0]].y) / 
				//		 (MVP_vertex[vYSort[2]].y-MVP_vertex[vYSort[0]].y) * (MVP_vertex[vYSort[1]].y-MVP_vertex[vYSort[0]].y);
				//temp_z = MV_value[vYSort[0]].z + (MV_value[vYSort[2]].z-MV_value[vYSort[0]].z) / 
				//		 (MVP_vertex[vYSort[2]].y-MVP_vertex[vYSort[0]].y) * (MVP_vertex[vYSort[1]].y-MVP_vertex[vYSort[0]].y);
				//glm::vec3 s_MV_v1(MV_value[vYSort[2]].x,MV_value[vYSort[2]].y,MV_value[vYSort[2]].z);
				//glm::vec3 s_MV_v2(MV_value[vYSort[1]].x,MV_value[vYSort[1]].y,MV_value[vYSort[1]].z);
				//glm::vec3 s_MV_v3(temp_x,temp_y,temp_z);
				//glm::vec3 s_MV_v4(MV_value[vYSort[0]].x,MV_value[vYSort[0]].y,MV_value[vYSort[0]].z);
				Primitive s1 = new glm::vec3[3];
				s1[0] = glm::vec3(MV_value[vYSort[2]]);
				s1[1] = glm::vec3(MV_value[vYSort[1]]);
				s1[2] = glm::vec3(temp);
				Primitive s2 = new glm::vec3[3];
				s2[0] = glm::vec3(MV_value[vYSort[1]]);
				s2[1] = glm::vec3(temp);
				s2[2] = glm::vec3(MV_value[vYSort[0]]);
				s1_v_MV_value.push_back(s1);
				s2_v_MV_value.push_back(s2);
			}
		}
		rasterStandingTriangle(s1_MVP_vertex,s1_v_MV_value,c);
		rasterStandingTriangle(s2_MVP_vertex,s2_v_MV_value,c);
		delete [] s1_MVP_vertex;
		delete [] s2_MVP_vertex;
		for (size_t i=0; i<s1_v_MV_value.size(); i++) delete [] s1_v_MV_value[i];
		for (size_t i=0; i<s2_v_MV_value.size(); i++) delete [] s2_v_MV_value[i];
	} else if ((MVP_vertex[vYSort[0]].y==MVP_vertex[vYSort[1]].y) && (MVP_vertex[vYSort[1]].y==MVP_vertex[vYSort[2]].y)) {
	} else {
		Primitive s_MVP_vertex = new glm::vec3[3];
		s_MVP_vertex[0] = glm::vec3(MVP_vertex[vYSort[2]]);
		s_MVP_vertex[1] = glm::vec3(MVP_vertex[vYSort[1]]);
		s_MVP_vertex[2] = glm::vec3(MVP_vertex[vYSort[0]]);
		vector<Primitive> s_v_MV_value;
		for (size_t i=0; i<v_MV_value.size(); i++) {
			Primitive s_MV_value = new glm::vec3[3];
			s_MV_value[0] = glm::vec3(v_MV_value[i][vYSort[2]]);
			s_MV_value[1] = glm::vec3(v_MV_value[i][vYSort[1]]);
			s_MV_value[2] = glm::vec3(v_MV_value[i][vYSort[0]]);
			s_v_MV_value.push_back(s_MV_value);
		}
		rasterStandingTriangle(s_MVP_vertex,s_v_MV_value,c);
		delete [] s_MVP_vertex;
		for (size_t i=0; i<s_v_MV_value.size(); i++) delete [] s_v_MV_value[i];
	}
}


