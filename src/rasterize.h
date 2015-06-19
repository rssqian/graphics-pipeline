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
extern bool cell;
extern bool projection;
extern int curModelIdx;
extern bool textureDisplay;
extern bool wireframe;
extern bool solid;
extern Lighting light;
extern glm::vec3 ka;
extern glm::vec3 kd;
extern glm::vec3 ks;

void drawEdge(int* ix,int* iy,float* iz,vec3 c);  //ix,iy,iz must have 3 element

typedef glm::vec3* Primitive;

void drawLine(const glm::vec4& p1,const glm::vec4& p2,const vec3& c);
void rasterStandingTriangle(Primitive MVP_vertex,vector<Primitive>& v_MV_value,Material* mtl,LightColor c);
void rasterTriangle(Primitive MVP_vertex,vector<Primitive>& v_MV_value,Material* mtl,LightColor c);
//(2D screen coord,3D camera coord,color for flat lighting)


#endif
