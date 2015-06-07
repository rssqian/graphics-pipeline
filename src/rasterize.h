#ifndef _RASTERIZE_H_
#define _RASTERIZE_H_

#include "model.h"
#include "framebuffer.h"
#include "lighting.h"
#include <glm/vec3.hpp>
#include <vector>

extern Model** modelPtr;
extern Framebuffer framebuffer;
extern int shading;
extern bool projection;
extern int curModelIdx;

void drawStandingTriangle(const vec3& p1,const vec3& p2,const vec3& p3,
						  const vec3& n1,const vec3& n2,const vec3& n3,vec3 c); //p1.y >= p2.y >= p3.y
void drawTriangle(vec3* triVertices,vec3* triNormals,vec3 c);  //triVertices & triNormal must have 3 element
void drawEdge(int* ix,int* iy,float* iz,vec3 c);  //ix,iy,iz must have 3 element

typedef glm::vec3* Primitive;

void drawLine(const glm::vec4& p1,const glm::vec4& p2,const vec3& c);
void rasterStandingTriangle(Primitive MVP_vertex,vector<Primitive>& v_MV_value,vec3 c,Material* mtl);
void rasterTriangle(Primitive MVP_vertex,vector<Primitive>& v_MV_value,vec3 c,Material* mtl);
//(2D screen coord,3D camera coord,color for flat lighting)


#endif
