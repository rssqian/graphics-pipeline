#include "rasterize.h"
#include "texture.h"
#include <iostream>
using namespace std;

extern int screenWidth;
extern int screenHeight;

void drawLine(const glm::vec4& p1,const glm::vec4& p2,const vec3& c)
{
	float m,B;
		if (abs(p2.y-p1.y) <= abs(p2.x-p1.x)) {	//use y=mx+B
			m = float(p2.y-p1.y)/float(p2.x-p1.x);
			B = p1.y - m * p1.x;
			if (p1.x<p2.x) {
				for (int x_=p1.x; x_<=p2.x; x_++) {
					int y_ = x_*m+B;
					float z_ = p1.z + (p2.z-p1.z)/(p2.x-p1.x)*(x_-p1.x);
					framebuffer.draw(x_,y_,z_,c,LightColor(),vec3(0.f),nullptr);
				}
			} else {
				for (int x_=p2.x; x_<=p1.x; x_++) {
					int y_ = x_*m+B;
					float z_ = p2.z + (p1.z-p2.z)/(p1.x-p2.x)*(x_-p2.x);
					framebuffer.draw(x_,y_,z_,c,LightColor(),vec3(0.f),nullptr);
				}
			}
		} else {									//use x=my+B
			m = float(p2.x-p1.x)/float(p2.y-p1.y);
			B = p1.x-m*p1.y;
			if (p1.y<p2.y) {
				for (int y_=p1.y; y_<=p2.y; y_++) {
					int x_ = y_*m+B;
					float z_ = p1.z + (p2.z-p1.z)/(p2.y-p1.y)*(y_-p1.y);
					framebuffer.draw(x_,y_,z_,c,LightColor(),vec3(0.f),nullptr);
				}
			} else {
				for (int y_=p2.y; y_<=p1.y; y_++) {
					int x_ = y_*m+B;
					float z_ = p2.z + (p1.z-p2.z)/(p1.y-p2.y)*(y_-p2.y);
					framebuffer.draw(x_,y_,z_,c,LightColor(),vec3(0.f),nullptr);
				}
			}
		}
}

void rasterStandingTriangle(Primitive MVP_vertex,vector<Primitive>& v_MV_value,Material* mtl,LightColor c_in)
{
	glm::vec3 p1 = MVP_vertex[0];
	glm::vec3 p2 = MVP_vertex[1];
	glm::vec3 p3 = MVP_vertex[2];
	int x_,y_=p1.y;
	float z_;
	float nx_,ny_,nz_;
	glm::vec3 n_;
	glm::vec3 p_left;
	glm::vec3 p_right;
	vector<glm::vec3> n_left(v_MV_value.size());
	vector<glm::vec3> n_right(v_MV_value.size());
	vector<glm::vec3*> result_vertex;
	vector<glm::vec3*> result_value;
	vec3 debug_c(1.f,1.f,1.f);
	vector<glm::vec3> mv_result;
	mv_result.resize(v_MV_value.size());
	LightColor c;
	float temp_barycentric;
	//LightColor RGBIntensity();
	//glm::vec3 ambient_c(c.x,c.y,c.z);
	//glm::vec3 diffuse_c(c.x,c.y,c.z);
	//glm::vec3 specular_c(c.x,c.y,c.z);
	float lamda1,lamda2,lamda3;
	while (y_ >= p3.y) {
		if (p1.y == p2.y) {
			if (p1.x<p2.x) {
				float b1 = y_-p3.y, b2 = y_-p3.y;
				float a1 = p1.y-p3.y-b1, a2 = p2.y-p3.y-b2;
				p_left.x = b1/(a1+b1)*p1.x + a1/(a1+b1)*p3.x;
				p_left.y = y_;
				p_left.z = b1/(a1+b1)*p1.z + a1/(a1+b1)*p3.z;
				p_right.x = b2/(a2+b2)*p2.x + a2/(a2+b2)*p3.x;
				p_right.y = y_;
				p_right.z = b2/(a2+b2)*p2.z + a2/(a2+b2)*p3.z;
			} else {
				int idx[3] = {0,1,2};
				float b1 = y_-p3.y, b2 = y_-p3.y;
				float a1 = p2.y-p3.y-b1, a2 = p1.y-p3.y-b2;
				p_right.x = b1/(a1+b1)*p1.x + a1/(a1+b1)*p3.x;
				p_right.y = y_;
				p_right.z = b1/(a1+b1)*p1.z + a1/(a1+b1)*p3.z;
				p_left.x = b2/(a2+b2)*p2.x + a2/(a2+b2)*p3.x;
				p_left.y = y_;
				p_left.z = b2/(a2+b2)*p2.z + a2/(a2+b2)*p3.z;
			}
		} else if (p2.y == p3.y){
			if (p2.x<p3.x) {
				float b1 = y_-p2.y, b2 = y_-p3.y;
				float a1 = p1.y-p2.y-b1, a2 = p1.y-p3.y-b2;
				p_left.x = b1/(a1+b1)*p1.x + a1/(a1+b1)*p2.x;
				p_left.y = y_;
				p_left.z = b1/(a1+b1)*p1.z + a1/(a1+b1)*p2.z;
				p_right.x = b2/(a2+b2)*p1.x + a2/(a2+b2)*p3.x;
				p_right.y = y_;
				p_right.z = b2/(a2+b2)*p1.z + a2/(a2+b2)*p3.z; 
			} else {
				float b1 = y_-p2.y, b2 = y_-p3.y;
				float a1 = p1.y-p2.y-b1, a2 = p1.y-p3.y-b2;
				p_right.x = b1/(a1+b1)*p1.x + a1/(a1+b1)*p2.x;
				p_right.y = y_;
				p_right.z = b1/(a1+b1)*p1.z + a1/(a1+b1)*p2.z;
				p_left.x = b2/(a2+b2)*p1.x + a2/(a2+b2)*p3.x;
				p_left.y = y_;
				p_left.z = b2/(a2+b2)*p1.z + a2/(a2+b2)*p3.z; 
			}
		}

		for (x_=(int(p_left.x)==p_left.x)?p_left.x:int(p_left.x)+1; x_<=p_right.x; x_++) {
			c = c_in;
			z_ = p_left.z + (p_right.z-p_left.z)/(p_right.x-p_left.x)*(x_-p_left.x);
			mv_result.clear();
			lamda1 = ((p2.y-p3.y)*(x_-p3.x) + (p3.x-p2.x)*(y_-p3.y)) / ((p2.y-p3.y)*(p1.x-p3.x) + (p3.x-p2.x)*(p1.y-p3.y));
			lamda2 = ((p3.y-p1.y)*(x_-p3.x) + (p1.x-p3.x)*(y_-p3.y)) / ((p2.y-p3.y)*(p1.x-p3.x) + (p3.x-p2.x)*(p1.y-p3.y));
			lamda3 = 1 - lamda1 - lamda2;
			for (size_t i=0; i<v_MV_value.size(); i++) {
				if (projection==0) {
					mv_result[i].x = lamda1*v_MV_value[i][0].x + lamda2*v_MV_value[i][1].x + lamda3*v_MV_value[i][2].x;
					mv_result[i].y = lamda1*v_MV_value[i][0].y + lamda2*v_MV_value[i][1].y + lamda3*v_MV_value[i][2].y;
					mv_result[i].z = lamda1*v_MV_value[i][0].z + lamda2*v_MV_value[i][1].z + lamda3*v_MV_value[i][2].z;
				} else {
					temp_barycentric = lamda1*(1/v_MV_value[1][0].z) + lamda2*(1/v_MV_value[1][1].z) + lamda3*(1/v_MV_value[1][2].z);
					mv_result[i].z = lamda1*(v_MV_value[i][0].z/v_MV_value[1][0].z) + lamda2*(v_MV_value[i][1].z/v_MV_value[1][1].z) + lamda3*(v_MV_value[i][2].z/v_MV_value[1][2].z);
					mv_result[i].y = lamda1*(v_MV_value[i][0].y/v_MV_value[1][0].z) + lamda2*(v_MV_value[i][1].y/v_MV_value[1][1].z) + lamda3*(v_MV_value[i][2].y/v_MV_value[1][2].z);
					mv_result[i].x = lamda1*(v_MV_value[i][0].x/v_MV_value[1][0].z) + lamda2*(v_MV_value[i][1].x/v_MV_value[1][1].z) + lamda3*(v_MV_value[i][2].x/v_MV_value[1][2].z);
					mv_result[i].z = mv_result[i].z / temp_barycentric;
					mv_result[i].y = mv_result[i].y / temp_barycentric;
					mv_result[i].x = mv_result[i].x / temp_barycentric;
					if (i==1) mv_result[i].z = 1 / temp_barycentric;
				}
			}
			
      if (textureDisplay && mtl!=nullptr) light.setParameter(mtl->Ka,mtl->Kd,mtl->Ks,mtl->Ns);
			else light.setParameter(ka,kd,ks,ns);
      
			if ((shading==2 || shading==3) && modelPtr[curModelIdx]->numNormals!=0) { 
        if (pointLight)
          light.shading(mv_result[1], mv_result[0], c, spotlightAngle); 
        else
          light.directionalShading(mv_result[0], c); 
			}
			/*if (textureDisplay==1 && solid==1 && shading!=0 && shading!=4 && mtl!=nullptr) {
				getTexture(mtl,mv_result[2],c.ambient,c.diffuse,c.specular);
			}*/
			vec3 vec3C = glm2vec3(c.ambient + c.diffuse + c.specular);
			//vec3 vec3C(	(c.ambient.x + c.diffuse.x + c.specular.x),
			//			(c.ambient.y + c.diffuse.y + c.specular.y),
			//			(c.ambient.z + c.diffuse.z + c.specular.z));
			if (shading==4 && modelPtr[curModelIdx]->numNormals!=0) {
				mv_result[0] = glm::normalize(mv_result[0]);
				vec3C.x = (glm::dot(mv_result[0],glm::vec3(1.f,0.f,0.f)) + 1.f) / 2.f;
				vec3C.y = (glm::dot(mv_result[0],glm::vec3(0.f,1.f,0.f)) + 1.f) / 2.f;
				vec3C.z = (glm::dot(mv_result[0],glm::vec3(0.f,0.f,1.f)) + 1.f) / 2.f;
			}
			/*if (shading==3) {
				vec3C.x = int(vec3C.x/0.2) * 0.2;
				vec3C.y = int(vec3C.y/0.2) * 0.2;
				vec3C.z = int(vec3C.z/0.2) * 0.2;
			}*/
      framebuffer.draw(x_,y_,z_,vec3C,c,glm2vec3(mv_result[2]),mtl);
		}
		y_--;
	}
}

void rasterTriangle(Primitive MVP_vertex,vector<Primitive>& v_MV_value,Material* mtl,LightColor c) 
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
		Primitive s1_MVP_vertex = new glm::vec3[3];
		s1_MVP_vertex[0] = glm::vec3(MVP_vertex[vYSort[2]]);
		s1_MVP_vertex[1] = glm::vec3(MVP_vertex[vYSort[1]]);
		s1_MVP_vertex[2] = glm::vec3(temp.x,MVP_vertex[vYSort[1]].y,temp.z);
		Primitive s2_MVP_vertex = new glm::vec3[3];
		s2_MVP_vertex[0] = glm::vec3(MVP_vertex[vYSort[1]]);
		s2_MVP_vertex[1] = glm::vec3(temp.x,MVP_vertex[vYSort[1]].y,temp.z);
		s2_MVP_vertex[2] = glm::vec3(MVP_vertex[vYSort[0]]);

		//interpolating for MV_value
		float temp_perspective;
		vector<Primitive> s1_v_MV_value,s2_v_MV_value; 
		Primitive s1;
		Primitive s2;
		b = MVP_vertex[vYSort[1]].y-MVP_vertex[vYSort[0]].y;
		a = MVP_vertex[vYSort[2]].y-MVP_vertex[vYSort[0]].y - b;
		for (size_t i=0; i<v_MV_value.size(); i++) {
			if (projection==0) {
				temp = b / (a+b) * v_MV_value[i][vYSort[2]] + a / (a+b) * v_MV_value[i][vYSort[0]];
			} else {
				temp_perspective = b/(a+b)*(1/v_MV_value[1][vYSort[2]].z) + a/(a+b)*(1/v_MV_value[1][vYSort[0]].z);
				temp.x = (b/(a+b)*(v_MV_value[i][vYSort[2]].x/v_MV_value[1][vYSort[2]].z) + a/(a+b)*(v_MV_value[i][vYSort[0]].x/v_MV_value[1][vYSort[0]].z)) / temp_perspective;
				temp.y = (b/(a+b)*(v_MV_value[i][vYSort[2]].y/v_MV_value[1][vYSort[2]].z) + a/(a+b)*(v_MV_value[i][vYSort[0]].y/v_MV_value[1][vYSort[0]].z)) / temp_perspective;
				temp.z = (b/(a+b)*(v_MV_value[i][vYSort[2]].z/v_MV_value[1][vYSort[2]].z) + a/(a+b)*(v_MV_value[i][vYSort[0]].z/v_MV_value[1][vYSort[0]].z)) / temp_perspective;
				if (i==1) temp.z = 1 / temp_perspective;
			}
			s1 = new glm::vec3[3];
			s1[0] = glm::vec3(v_MV_value[i][vYSort[2]]);
			s1[1] = glm::vec3(v_MV_value[i][vYSort[1]]);
			s1[2] = glm::vec3(temp);
			s2 = new glm::vec3[3];
			s2[0] = glm::vec3(v_MV_value[i][vYSort[1]]);
			s2[1] = glm::vec3(temp);
			s2[2] = glm::vec3(v_MV_value[i][vYSort[0]]);
			s1_v_MV_value.push_back(s1);
			s2_v_MV_value.push_back(s2);
		}
		//c.diffuse.x = 1.f;
		//c.diffuse.y = 0.f;
		//c.diffuse.z = 0.f;
		rasterStandingTriangle(s1_MVP_vertex,s1_v_MV_value,mtl,c);
		//c.diffuse.x = 0.f;
		//c.diffuse.y = 0.f;
		//c.diffuse.z = 1.f;
		rasterStandingTriangle(s2_MVP_vertex,s2_v_MV_value,mtl,c);
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
		//c.diffuse.x = 1.f;
		//c.diffuse.y = 1.f;
		//c.diffuse.z = 1.f;
		rasterStandingTriangle(s_MVP_vertex,s_v_MV_value,mtl,c);
		delete [] s_MVP_vertex;
		for (size_t i=0; i<s_v_MV_value.size(); i++) delete [] s_v_MV_value[i];
	}
	/*if (v_MV_value.size() > 0) {
		glm::vec4 p1(0.f),p2(0.f);
		glm::vec3 normalized_n;
		for (int i=0; i<3; i++) {
			p1.x = MVP_vertex[i].x;
			p1.y = MVP_vertex[i].y;
			p1.z = MVP_vertex[i].z;
			normalized_n = glm::normalize(v_MV_value[0][i])/10.f;
			p2.x = MVP_vertex[i].x + normalized_n.x;
			p2.y = MVP_vertex[i].y + normalized_n.y;
			p2.z = MVP_vertex[i].z + normalized_n.z;
			drawLine(p1,p2,vec3(1.f));
		}
	}*/
}

void drawShadow(const glm::vec3& vA, const glm::vec3& vB, const glm::vec3& vC, const vec3& color)
{
  /* Find the bounded area to scan candidate pixels. */
  float maxX = vA.x;
  float maxY = vA.y;
  float minX = vA.x;
  float minY = vA.y;
  if (vB.x > maxX) maxX = vB.x;
  if (vC.x > maxX) maxX = vC.x;
  if (vB.y > maxY) maxY = vB.y;
  if (vC.y > maxY) maxY = vC.y;
  if (vB.x < minX) minX = vB.x;
  if (vC.x < minX) minX = vC.x;
  if (vB.y < minY) minY = vB.y;
  if (vC.y < minY) minY = vC.y;
  
  /* Check if the pixel is in the triangle. If true, draw it. */
  float k1, k2, k3, z, c;
  for (int x = minX; x <= maxX; ++x) {
    for (int y = minY; y <= maxY; ++y) {
      k1 = (x - vA.x) * (vB.y - vA.y) - (y - vA.y) * (vB.x - vA.x);
      k2 = (x - vB.x) * (vC.y - vB.y) - (y - vB.y) * (vC.x - vB.x);
      k3 = (x - vC.x) * (vA.y - vC.y) - (y - vC.y) * (vA.x - vC.x);
      if ( (k1>=0 && k2>=0 && k3>=0) || (k1<=0 && k2<=0 && k3<=0) ) {
        z = -10.f;
        framebuffer.draw(x, y, z, color, LightColor(), vec3(0), nullptr);
      }
    }
  }
}
