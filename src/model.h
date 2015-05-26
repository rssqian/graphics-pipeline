#ifndef _MODEL_H_
#define _MODEL_H_

#include <iostream>
#include <cstring>
#include <glm/vec3.hpp>
using namespace std;

class ValueTriangle {
public:
	ValueTriangle() {};
	~ValueTriangle() {};

	glm::vec3 vertex[3];
	glm::vec3 normal[3];
};

class Triangle {
public:
	Triangle() {
		vIndices = new int[3];
		nIndices = new int[3];
	}
	~Triangle() {
		delete [] vIndices;
		delete [] nIndices;
	}
	int* vIndices;	/* array of triangle vertex indices */
	int* nIndices;	/* array of triangle normal indices */
};

class Model {
public:
	Model(): numVertices(0), numNormals(0), numTriangles(0), vertices(nullptr), normals(nullptr), triangles(nullptr) {}
	~Model() { 
		if(vertices) delete [] vertices;
		if(normals) delete [] normals;
		if(triangles) delete [] triangles;
	}
	/* data members are declared public for easy access */
	int numVertices;		/* number of vertices in model */
	int numNormals;			/* number of normals in model */
	int numTriangles;		/* number of triangles in model */
	float* vertices;		/* array of vertices */
	float* normals;			/* array of normals */
	Triangle* triangles;	/* array of triangles */
};

Model* readObj(const string filename);

#endif // _MODEL_H_
