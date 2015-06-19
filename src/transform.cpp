#include "framebuffer.h"
#include "transform.h"
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

extern double thetaX;
extern double thetaY;

//extern double deltaSize;

//extern double deltaX;
//extern double deltaY;
//extern double deltaZ;

extern int screenWidth;
extern int screenHeight;
extern int screenWidth_half;
extern int screenHeight_half;

extern bool projection;

/*
void model2view_rotation(vec3& prev)
{
	float curX,curY,curZ;
	// rotate along x-axis
	curY = (prev.y*cos(thetaX)-prev.z*sin(thetaX))*(1+deltaSize)+deltaY;
	curZ = prev.y*sin(thetaX)+prev.z*cos(thetaX);
	// prevY = curY;
	prev.z = curZ;
	// rotate along y-axis
	curX = (prev.z*sin(thetaY)+prev.x*cos(thetaY))*(1+deltaSize)+deltaX;
	curZ = (prev.z*cos(thetaY)-prev.x*sin(thetaY))*(1+deltaSize)+deltaZ;
	prev.x = curX;
	prev.y = curY;
	prev.z = curZ;
}
*/
/*
glm::mat4 modelMatrix(glm::vec3 translation,glm::vec3 rotation,double scale) {
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f),rotation.x,glm::vec3(1.0f,0.0f,0.0f));
			  rotationMatrix = glm::rotate(rotationMatrix,rotation.y,glm::vec3(0.0f,1.0f,0.0f));
			  rotationMatrix = glm::rotate(rotationMatrix,rotation.z,glm::vec3(0.0f,0.0f,1.0f));
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f),glm::vec3(scale));
	glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f),translation);
	return translateMatrix * scaleMatrix * rotationMatrix;
}
*/

glm::mat4 model_translation(glm::vec3 translation) {
	glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f),translation);
	return translateMatrix;
}

glm::mat4 model_scale(glm::vec3 scale) {
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f),scale);
	return scaleMatrix;
}

glm::mat4 model_rotation(glm::vec3 rotation) {
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f),rotation.x,glm::vec3(1.0f,0.0f,0.0f));
			  rotationMatrix = glm::rotate(rotationMatrix,rotation.y,glm::vec3(0.0f,1.0f,0.0f));
			  rotationMatrix = glm::rotate(rotationMatrix,rotation.z,glm::vec3(0.0f,0.0f,1.0f));
	return rotationMatrix;
}
/*
glm::mat4 viewMatrix(glm::vec3 cameraPos,glm::vec3 cameraTarget,glm::vec3 upVector) {
	glm::mat4 cameraMatrix = glm::lookAt(cameraPos,cameraTarget,upVector);
	return cameraMatrix;
}
glm::mat4 projectionMatrix(float FoV) {
	glm::mat4 projectionMatrix(1.0f);
	if (projection==0) {
		 projectionMatrix = glm::perspective(FoV,1.0f/1.0f,0.1f,100.0f);
	} else {
		projectionMatrix = glm::ortho(10.0f,10.0f,10.0f,10.0f,0.1f,100.0f);
	}
	return projectionMatrix;
}
*/
bool backFaceCulling(glm::vec3 faceNormals, glm::vec3 modelVertice)   //input 3 vertex of the triangle
{
	glm::vec3 front(0.f,0.f,1.f);
	if (projection) {
		if ( glm::dot(faceNormals, modelVertice) > 0) return true;
	} else {
		if ( glm::dot(faceNormals, front) < 0) return true;
	}
	return false;
}
/*
void toScreenSpace(vec3& v,int& ix,int& iy,float& iz)
{
	int screenSide = min(screenWidth, screenHeight);
	float margin = 0.1f;
	v.z += 1;
	if (projection==0) {
		// Orthogonal Projection
		ix = int(((1.f-margin)*v.x)*screenSide) + screenWidth_half - 1;
		iy = int(((1.f-margin)*v.y)*screenSide) + screenHeight_half - 1;
		iz = v.z;
	} else {
		//Perspective Projection
		ix = (((1.f-margin)*v.x/v.z*0.5)*screenSide) + screenWidth_half - 1;
		iy = (((1.f-margin)*v.y/v.z*0.5)*screenSide) + screenHeight_half - 1;
		iz = v.z;
	}
}
*/
