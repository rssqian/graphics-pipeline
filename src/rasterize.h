#ifndef _RASTERIZE_H_
#define _RASTERIZE_H_

#include "model.h"
#include "framebuffer.h"
#include "lighting.h"
#include <glm/vec3.hpp>
#include <vector>

extern Framebuffer framebuffer;
extern int shading;

void drawStandingTriangle(const vec3& p1,const vec3& p2,const vec3& p3,
						  const vec3& n1,const vec3& n2,const vec3& n3,vec3 c); //p1.y >= p2.y >= p3.y
void drawTriangle(vec3* triVertices,vec3* triNormals,vec3 c);  //triVertices & triNormal must have 3 element
void drawEdge(int* ix,int* iy,float* iz,vec3 c);  //ix,iy,iz must have 3 element

typedef glm::vec3* Primitive;

void rasterStandingTriangle(Primitive MVP_vertex,vector<Primitive>& v_MV_value,vec3 c);
void rasterTriangle(Primitive MVP_vertex,vector<Primitive>& MV_value,vec3 c);


#endif
