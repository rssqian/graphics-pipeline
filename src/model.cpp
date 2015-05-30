#include "model.h"
#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

void readObjFirstPass(Model* model, ifstream& ifs)
{
	int numVertices = 0;
	int numNormals = 0;
	int numTriangles = 0;
	int numTexCoords = 0;

	char ch;
	char buf[256];

	while(!ifs.eof()) {
		ifs >> ch;
		switch(ch) {
		case '#':				/* comment */
			/* eat up rest of line */
			ifs.getline(buf, 256);
			break;
		case 'v':				/* v, vn, vt */
			/* eat up rest of line */
			ifs.getline(buf, 256);
			switch(buf[0]) {
			case ' ':			/* vertex */
				++numVertices;
				break;
			case 'n':				/* normal */
				++numNormals;
				break;
			case 't':				/* texcoord, ignored now */
				++numTexCoords;
				break;
			default:
				cout << "readObjFirstPass(): Unknown token ignored: " << ch << buf << endl;
				break;
			}
			break;
		case 'm':				/* material lib, ignored now */
		case 'u':				/* use material, ignored now */
		case 'g':				/* group, ignored now */
			/* eat up rest of line */
			ifs.getline(buf, 256);
			break;
		case 'f':				/* face */
			ifs.getline(buf, 256);
			if(buf[0] == ' ') {
				++numTriangles;
			}
			break;
		default:
			/* eat up rest of line */
			ifs.getline(buf, 256);
			break;
		}	// end of switch
	}	// end of while

	/* set the stats in the model structure */
	model->numVertices  = numVertices;
	model->numNormals   = numNormals;
	model->numTriangles = numTriangles;
	model->numTexCoords = numTexCoords;
}

void readObjSecondPass(Model* model, ifstream& ifs)
{
	int vIdx = 1;	/* vertex and normal and texCoord indices start from 1 */
	int nIdx = 1;
	int tcIdx= 1;
	int tIdx = 0;
	int v0, v1, v2, n0, n1, n2, t0, t1, t2;
	float* vertices = model->vertices;
	float* normals  = model->normals;
	float* texCoords = model->texCoords;
	Triangle* triangles = model->triangles;

	char ch;
	char s[2];
	char buf[256];

	while(!ifs.eof()) {
		ifs >> ch;
		switch(ch) {
		case '#':				/* comment */
			/* eat up rest of line */
			ifs.getline(buf, 256);
			break;
		case 'v':				/* v, vn, vt */
			/* eat up rest of line */
			ifs.getline(buf, 256);
			switch(buf[0]) {
			case ' ':			/* vertex */
				sscanf(buf, "%f %f %f", &vertices[3*vIdx], &vertices[3*vIdx+1], &vertices[3*vIdx+2]);
				++vIdx;
				break;
			case 'n':				/* normal */
				sscanf(buf, "%s %f %f %f",s , &normals[3*nIdx], &normals[3*nIdx+1], &normals[3*nIdx+2]);
				++nIdx;
				break;
			case 't':				/* texcoord */
				sscanf(buf, "%s %f %f", s, &texCoords[2*tcIdx], &texCoords[2*tcIdx+1]);
				++tcIdx;
				break;
			default:
				cout << "readObjFirstPass(): Unknown token ignored: " << ch << buf << endl;
				break;
			}
			break;
		case 'm':				/* material lib, ignored now */
		case 'u':				/* use material, ignored now */
		case 'g':				/* group, ignored now */
			/* eat up rest of line */
			ifs.getline(buf, 256);
			break;
		case 'f':				/* face */
			ifs.getline(buf, 256);
			/* can be one of v, v//n, v/t, v/t/n*/
			if(buf[0] == ' ') {
				if(strstr(buf, "//")) {		/* v//n */
					sscanf(buf, "%d//%d %d//%d %d//%d", &v0, &n0, &v1, &n1, &v2, &n2);
					triangles[tIdx].vIndices[0] = v0;
					triangles[tIdx].vIndices[1] = v1;
					triangles[tIdx].vIndices[2] = v2;
					triangles[tIdx].nIndices[0] = n0;
					triangles[tIdx].nIndices[1] = n1;
					triangles[tIdx].nIndices[2] = n2;
					//cout << "writing normal 0:x= " << normals[3*n0] << "\ty= " << normals[3*n0+1] << "\tz= " << normals[3*n0+2] << endl;
					//cout << "writing normal 1:x= " << normals[3*n1] << "\ty= " << normals[3*n1+1] << "\tz= " << normals[3*n1+2] << endl;
					//cout << "writing normal 2:x= " << normals[3*n2] << "\ty= " << normals[3*n2+1] << "\tz= " << normals[3*n2+2] << endl;
				}
				else if(sscanf(buf, "%d/%d/%d", &v0, &t0, &n0) == 3) {	/* v/t/n */
					sscanf(buf, "%d/%d/%d %d/%d/%d %d/%d/%d", &v0, &t0, &n0, &v1, &t1, &n1, &v2, &t2, &n2);
					triangles[tIdx].vIndices[0] = v0;
					triangles[tIdx].vIndices[1] = v1;
					triangles[tIdx].vIndices[2] = v2;
					triangles[tIdx].tcIndices[0] = v0;
					triangles[tIdx].tcIndices[1] = v1;
					triangles[tIdx].tcIndices[2] = v2;
					triangles[tIdx].nIndices[0] = n0;
					triangles[tIdx].nIndices[1] = n1;
					triangles[tIdx].nIndices[2] = n2;
				}
				else if(sscanf(buf, "%d/%d", &v0, &t0) == 2) {	/* v/t */
					sscanf(buf, "%d/%d %d/%d %d/%d", &v0, &t0, &v1, &t1, &v2, &t2);
					triangles[tIdx].vIndices[0] = v0;
					triangles[tIdx].vIndices[1] = v1;
					triangles[tIdx].vIndices[2] = v2;
					triangles[tIdx].tcIndices[0]= t0;
					triangles[tIdx].tcIndices[1]= t1;
					triangles[tIdx].tcIndices[2]= t2;
				}
				else {		/* v */
					sscanf(buf, "%d %d %d", &v0, &v1, &v2);
					triangles[tIdx].vIndices[0] = v0;
					triangles[tIdx].vIndices[1] = v1;
					triangles[tIdx].vIndices[2] = v2;
				}
				++tIdx;
			}
			break;
		default:
			/* eat up rest of line */
			ifs.getline(buf, 256);
			break;
		}	// end of switch
	}	// end of while
}

Model* readObj(const string filename) 
{	
	ifstream ifs(filename.c_str(), ios::in);
	if(!ifs) {
		cerr << "Error opening " << filename.c_str() << endl;
		exit(-1);
	}

	Model* model = new Model;
	
	/* get numVertices, numNormals and numTriangles */
	readObjFirstPass(model, ifs);

	// cout << "numVertices = " << model->numVertices << endl;
	// cout << "numNormals = " << model->numNormals << endl;
	// cout << "numTriangles = " << model->numTriangles << endl;

	/* allocate memory */
	model->vertices = new float[model->numVertices*3+1];
	model->normals = new float[model->numNormals*3+1];
	model->texCoords = new float[model->numTexCoords*2+1];
	model->triangles = new Triangle[model->numTriangles];

	/* go back to the beginning of the stream and read data in the second pass */
	ifs.close();
	ifs.open(filename.c_str(), ios::in);
	// ifs.seekg(ifs.beg);

	readObjSecondPass(model, ifs);
	
	ifs.close();

	cout << filename.c_str() << " loaded..." << endl;

	return model;
}