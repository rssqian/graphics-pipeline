#ifndef _MODEL_H_
#define _MODEL_H_

#include <iostream>
#include <cstring>
#include <vector>
#include <glm/vec3.hpp>
#include "material.h"
using namespace std;

class ValueTriangle {
public:
	ValueTriangle() {
		vertex = new glm::vec3[3];
		normal = new glm::vec3[3];
	}
	~ValueTriangle() {
		delete vertex;
		delete normal;
	}

	glm::vec3* vertex;
	glm::vec3* normal;
};

class Triangle {
public:
	Triangle() {
		vIndices = new int[3];
		nIndices = new int[3];
		tcIndices = new int[3];
	}
	~Triangle() {
		delete [] vIndices;
		delete [] nIndices;
		delete [] tcIndices;
	}
	int* vIndices;	/* array of triangle vertex indices */
	int* nIndices;	/* array of triangle normal indices */
	int* tcIndices; /* array of traingle texCoord indices */
	Material*  mtlptr; /* materal indice */
};

class Model {
public:
	Model(): numVertices(0), numNormals(0), numTriangles(0), numTexCoords(0),
			 vertices(nullptr), normals(nullptr), texCoords(nullptr), triangles(nullptr) {}
	~Model() { 
		if (vertices)  delete [] vertices;
		if (normals)   delete [] normals;
		if (texCoords) delete [] texCoords;
		if (triangles) delete [] triangles;
		if (materials.size() == 0) {
			for (size_t i=0; i<materials.size(); i++)
				delete materials[i];
		}
	}
	/* data members are declared public for easy access */
	int numVertices;		/* number of vertices in model */
	int numNormals;			/* number of normals in model */
	int numTriangles;		/* number of triangles in model */
	int numTexCoords;		/* number of Texture Coords in model */

	float* vertices;		/* array of vertices */
	float* normals;			/* array of normals */
	float* texCoords;		/* array of texture coords */
	Triangle* triangles;	/* array of triangles */
	vector<Material*> materials;		/* array of materials */
};

void readPPM(const string& filename,RGBImage& img);
Model* readObj(const string& filename);

#endif // _MODEL_H_
